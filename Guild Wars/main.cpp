/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: lab02
 *  File: main.cpp
 *
 *	Author: Dr. Jeffrey Paone - Fall 2015
 *
 *  Description:
 *      Contains the base code for a basic flight simulator.
 *
 */

#include "gl_includes.hpp"
#include "math_safe.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <map>

#define BUFFER_SIZE 128

// My objects
#include "BezierCurve.hpp"
#include "BezierPatch.hpp"
#include "BezierPatchDrawer.hpp"
#include "Camera.hpp"
#include "Tree.hpp"
#include "Flag.hpp"
#include "Light.hpp"
#include "Transform3D.hpp"
#include "CameraController.hpp"
#include "ArcBallCamera.hpp"
#include "FreeCamera.hpp"
#include "GameClock.hpp"
#include "HeroNameDrawer.hpp"
#include "Hero_tim.hpp"
#include "HeroChris.hpp"
#include "BezierTrack.hpp"
#include "Keyboard.hpp"
#include "HeroTrevor.hpp"

// Included JSONcpp framework
// https://github.com/open-source-parsers/jsoncpp
#include "JSON.hpp"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 1600;
static size_t windowHeight = 900;
static float aspectRatio;

GLint leftMouseButton; 		   	            // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
bool show_first_person = false;
float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
float radius = 10.0;                         // camera ZOOM in spherical coordinates

GLuint environmentDL;                       // display list for the 'world' - static, unmoving objects only

BezierPatchDrawer *bezierDrawer;
BezierPatch *patches;
BezierTrack *track;

HeroChris krandul(Transform3D(Vector3(0, 0, 5)), "Krandul");
HeroNameDrawer krandul_name_drawer(krandul, Color(0, 0, 1));

Hero_tim tim_the_enchanter(Transform3D(Vector3(), Vector3(0.5, 0.5, 0.5)), patches);						//Hero
HeroNameDrawer tim_name_drawer(tim_the_enchanter, Color(1, 0, 0));

HeroTrevor jaegansmann(Transform3D(Vector3(5, 0, 5)), "Jaegansmann");
HeroNameDrawer jaegansmann_name_drawer(jaegansmann, Color(0, 1, 0));

Keyboard keyboard;

ArcBallCamera arcball_camera(90, 45);
FreeCamera free_camera(0, 2, 0);
FreeCamera first_person_camera(krandul.getTransform());
CameraController camera_controller(arcball_camera, 0.5);
CameraController first_person_camera_controller(first_person_camera, 0.005);

GameClock game_clock;

Light light(Transform3D(Vector3(0, 30, 0)), Color(0.55, 0.55, 0.42), Color(0.2, 0.2, 0.2));
Light animated_light(Transform3D(Vector3(0, 10, 0)), Color(1, 0, 0), Color(0, 0, 0));
float lightAngle = 0;						//Angle used to animate light
bool leftCtrlMouse = false;

map<unsigned char, bool> keyboard_state;

using namespace std;

void exitProgram(int exit_val) {
	#ifdef __APPLE__			// if compiling on Mac OS
		_exit(exit_val);
	#else
		exit(0); // Windows thinks that anything other than a zero needs a popup saying "Program didn't shut down correctly". It looks a lot like the program crashed when it was shutting down. Fixed.
	#endif
}

float t_track = 0.0f;
float s_track = 0.0f;

std::vector<Point> tree_points;
std::vector<Point> flag_points;

// global variable to keep track of the window id
int windowId;
void* default_font = GLUT_BITMAP_9_BY_15;
void* default_stroke_font = GLUT_STROKE_ROMAN;

void glutBitmapString(void* font, string to_draw) {
    for (unsigned int i = 0; i < to_draw.size(); ++i) {
        glutBitmapCharacter(font, to_draw[i]);
    }
}

void drawString(string to_draw, int x_position, int y_position) {
    glRasterPos2i(x_position, y_position);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glutBitmapString(default_font, to_draw);
}

// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float getRand() {
   	return rand() / (float)RAND_MAX;
}

std::vector<Point> parseCSVintoVector(char* filename){
	char buffer[20];
    FILE *oFile;
    int pointCount;
    float x, y, z;
    std::vector<Point> control_points;

    oFile = fopen(filename, "r");
    if(fgets(buffer, sizeof(buffer), oFile) != 0){
        if(sscanf(buffer, "%d", &pointCount) == 1){
            for(int i(0); i < pointCount; ++i){
                fgets(buffer, sizeof(buffer), oFile);
                sscanf(buffer, "%f,%f,%f", &x, &y, &z);
				control_points.push_back(Point(x, y, z));
            }
        } else {
            printf("Error: \"%s\" is in the wrong format.\n", filename);
            exitProgram(1);
        }
    } else {
        printf("Error: \"%s\" could not be opened for reading.\n", filename);
        exitProgram(1);
    }

	printf("Read in %d control points from \"%s\"\n", (int)control_points.size(), filename);

	return control_points;
}

void setupBezierPatch(char * filename){
	std::vector<Point> points = parseCSVintoVector(filename);

	patches = new BezierPatch(points);
	bezierDrawer = new BezierPatchDrawer(*patches);
}

bool parseJSON( char* filename ){

	// http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream t(filename);
	std::string json_file((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

	Json::Value root;
	Json::Reader reader;
	bool parseSuccess = reader.parse(json_file, root, false);

	if(!parseSuccess){
		printf("Error parsing json file format.\n");
		exit(1);
	}

	const Json::Value bezier_patch_file = root["BezierPatchFile"];
	string bezier_patch_file_string = bezier_patch_file.asString();
	setupBezierPatch(strdup(bezier_patch_file_string.c_str()));

	const Json::Value bezier_track_file = root["BezierTrackFile"];
	string bezier_track_file_string = bezier_track_file.asString();

	vector<Point> points = parseCSVintoVector(strdup(bezier_track_file_string.c_str()));
    track = new BezierTrack(BezierCurve(points));

	const Json::Value trees_array = root["Trees"];
	for(unsigned int i(0); i < trees_array.size(); i+=3){
		float p1 = std::stof(trees_array[i].asString());
		float p2 = std::stof(trees_array[i + 1].asString());
		float p3 = std::stof(trees_array[i + 2].asString());
		tree_points.push_back(Point(p1, p2, p3));
	}

	const Json::Value flags_array = root["Flags"];
	for(unsigned int i(0); i < flags_array.size(); i+=3){
		float p1 = std::stof(flags_array[i].asString());
		float p2 = std::stof(flags_array[i + 1].asString());
		float p3 = std::stof(flags_array[i + 2].asString());
		flag_points.push_back(Point(p1, p2, p3));
	}

	return true;
}

// generateEnvironmentDL() /////////////////////////////////////////////////////
//
//  This function creates a display list with the code to draw a simple
//      environment for the user to navigate through.
//
//  And yes, it uses a global variable for the display list.
//  I know, I know! Kids: don't try this at home. There's something to be said
//      for object-oriented programming after all.
//
////////////////////////////////////////////////////////////////////////////////
void generateEnvironmentDL() {
    environmentDL = glGenLists(10); // You won't believe what ten things are drawn next!
    glNewList(environmentDL, GL_COMPILE); // Store these things and "compile" them on the GPU
		glPushMatrix();
			for(unsigned int i(0); i < tree_points.size(); ++i){
				Point p = tree_points[i];
				Tree t(p.getX(), p.getY(), p.getZ());
				t.draw();
			}
			for(unsigned int i(0); i < flag_points.size(); ++i){
				Point p = flag_points[i];
				Flag f(p.getX(), p.getY(), p.getZ());
				f.draw();
			}
		glPopMatrix();

    glEndList();
}

// resizeWindow() //////////////////////////////////////////////////////////////
//
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport.
//
////////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}



// mouseCallback() /////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
////////////////////////////////////////////////////////////////////////////////
void mouseCallback(int button, int state, int thisX, int thisY) {
    // update the left mouse button states, if applicable
    if(button == GLUT_LEFT_BUTTON){
        leftMouseButton = state;
        mouseX = thisX;
        mouseY = thisY;
		if( glutGetModifiers() & GLUT_ACTIVE_CTRL )
			leftCtrlMouse = true;
		else
			leftCtrlMouse = false;
	}
}

// mouseMotion() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or
//      cameraRadius based on how much the user has moved the mouse in the
//      X or Y directions (in screen space) and whether they have held down
//      the left or right mouse buttons. If the user hasn't held down any
//      buttons, the function just updates the last seen mouse X and Y coords.
//
////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {
    if(!leftCtrlMouse) {
        int deltaX = x - mouseX;
        int deltaY = y - mouseY;

        mouseX = x;
        mouseY = y;

        camera_controller.handleInput(deltaX, deltaY, 0.0);

    } else if (leftCtrlMouse){
        int deltaY = y - mouseY;

        mouseY = y;

		camera_controller.handleInput(0.0, 0.0, deltaY);

    }
}



// initScene() /////////////////////////////////////////////////////////////////
//
//  A basic scene initialization function; should be called once after the
//      OpenGL context has been created. Doesn't need to be called further.
//
////////////////////////////////////////////////////////////////////////////////
void initScene()  {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
	light.tellOpenGL();

    glShadeModel(GL_SMOOTH);

    srand( time(NULL) );	// seed our random number generator

    generateEnvironmentDL();
}

void handleKeySignals(){
    // Here is where you map signals to actions
    // Example:
    // if(keyboard_state['w']){
    //     something.moveForward();
    // }
    // maps the signal 'w' to the action something.moveForward()

	if(keyboard.isKeyDown('q') || keyboard.isKeyDown('Q') || keyboard.isKeyDown(27)) {

		exitProgram(0);

	}

	Point patchLocal;
	if (keyboard.isKeyDown('w')) {
		tim_the_enchanter.moveForward();
	}
	if (keyboard.isKeyDown('s')) {
		tim_the_enchanter.moveBackward();
	}
	if (keyboard.isKeyDown('a')) {
		tim_the_enchanter.turnLeft();
	}
	if (keyboard.isKeyDown('d')) {
		tim_the_enchanter.turnRight();
	}

}

void setup2DProjectionForHUD() {
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0, windowWidth, 0, windowHeight);
}

void resetProjectionForScene() {
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawFPS() {
	float frame_time = game_clock.getDeltaTime();
	float fps = 1.0f / frame_time;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	drawString("FPS: " + to_string(int(fps)), 10,  windowHeight - 15);
}

void prepareToRenderHUD() {
	setup2DProjectionForHUD();

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
}

void cleanupAfterRenderingHUD() {
	glPopMatrix();
	glEnable(GL_LIGHTING);

	resetProjectionForScene();
}

void renderHUD() {
	prepareToRenderHUD();
	// All drawing code for the HUD goes here.
	drawFPS();

	cleanupAfterRenderingHUD();
}

void renderHeroNames() {
	krandul_name_drawer.draw();
	tim_name_drawer.draw();
	jaegansmann_name_drawer.draw();
}

void moveHeroAlongTrackNonParameterized(HeroBase& hero, BezierTrack& bezier_track) {
	// Non parameterized - chris
	Point p = bezier_track.getPointFromT(t_track);
	Vector3 tangent = bezier_track.getTangentFromT(t_track).unit();
	Vector3 new_position(p.getX(), p.getY(), p.getZ());
	hero.getTransform().setPosition(new_position);

	float rotation_angle = 180.0f / M_PI * acos(tangent.dot(Vector3::forward()));
	Vector3 rotation_axis = Vector3::forward().cross(tangent);
	hero.getTransform().setRotation(rotation_axis, rotation_angle);

}

void moveHeroAlongTrackParameterized(HeroBase& hero, BezierTrack& bezier_track) {
	// Non parameterized - chris
	Point p = bezier_track.getCurve().getPointFromS(s_track);
	Vector3 tangent = bezier_track.getCurve().getTangentFromS(s_track).unit();
	Vector3 new_position(p.getX(), p.getY(), p.getZ());
	hero.getTransform().setPosition(new_position);

	float rotation_angle = 180.0f / M_PI * acos(tangent.dot(Vector3::forward()));
	Vector3 rotation_axis = Vector3::forward().cross(tangent);
	hero.getTransform().setRotation(rotation_axis, rotation_angle);

}

void updateHeroes(){
	tim_the_enchanter.updateAnimation();	//Animate arm on enchanter
	krandul.updateAnimation();

	moveHeroAlongTrackNonParameterized(krandul, *track);
	moveHeroAlongTrackParameterized(jaegansmann, *track);

	// Increment t
	t_track += 0.005f;
	if(t_track > 1.0f){
		t_track = 0.0f;
	}

	// Increment s
	s_track += 0.005f;
	if (s_track > 1.0f) {
		s_track = 0.0f;
	}
}

void drawHeros() {
	tim_the_enchanter.draw();
	krandul.draw();
	jaegansmann.draw();
}

void renderWorld() {
	light.tellOpenGL();
	animated_light.tellOpenGL();

	// Iterate through the environment list and draw things
    glCallList(environmentDL);

	bezierDrawer->draw();
    track->draw();
	renderHeroNames();
	drawHeros();
}

void renderRegularScreen() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, windowWidth, windowHeight);

	camera_controller.update();
	renderWorld();
}

void renderOnPictureInPicture() {
	glViewport(0, 0, 320, 180);

	prepareToRenderHUD();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(windowWidth, 0);
		glVertex2f(windowWidth, windowHeight);
		glVertex2f(0, windowHeight);
	glEnd();
	cleanupAfterRenderingHUD();

	glClear(GL_DEPTH_BUFFER_BIT);

	first_person_camera_controller.update();
	renderWorld();
}

bool showingFirstPerson() {
	return show_first_person;
}

void showFirstPerson() {
	show_first_person = true;
}
void hideFirstPerson() {
	show_first_person = false;
}

void toggleFirstPersonView() {
	if (showingFirstPerson()) {
		hideFirstPerson();
	} else {
		showFirstPerson();
	}
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void)  {
	game_clock.tick();

    //clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();

	renderRegularScreen();
	renderHUD();

	if (showingFirstPerson()) {
		renderOnPictureInPicture();
	}

    //push the back buffer to the screen
    glutSwapBuffers();
}

void myTimer(int value){
	handleKeySignals();
	camera_controller.handleKeyboard(keyboard);

	updateHeroes();

    glutPostRedisplay();

	lightAngle++;	//animate light
	Vector3 old_position = animated_light.getTransform3D().getPosition();
	animated_light.getTransform3D().setPosition(
		Vector3(sin(lightAngle * 0.01) * 20,
				old_position.y,
				cos(lightAngle * 0.01) * 20));

    glutTimerFunc(value, &myTimer, value);
}

void fixMenuCallback(int value){
	// if(b->isControlCageVisible()){
	// 	glutChangeToMenuEntry(2, "Hide Control Cage", 1);
	// } else {
	// 	glutChangeToMenuEntry(2, "Display Control Cage", 1);
	// }
	//
	// if(b->isCurveVisible()){
	// 	glutChangeToMenuEntry(3, "Hide Bezier Curve", 2);
	// } else {
	// 	glutChangeToMenuEntry(3, "Display Bezier Curve", 2);
	// }
}

// myMenu() /////////////////////////////////////////////////////////////////////
//
//  Handles our Menu events
//
////////////////////////////////////////////////////////////////////////////////
void myMenu( int value ) {
    switch(value){
    case 0:
        exitProgram(0);
	case 1:
		// b->toggleControlCageVisibility();
		break;
	case 2:
		// b->toggleCurveVisibility();
		break;
	case 3:
		// b->toggleCurveVisibility();
		camera_controller.setCurrentCamera(free_camera);
		camera_controller.setSensitivity(0.005);
		camera_controller.update();
		glutPostRedisplay();
		break;
	case 4:
		// b->toggleCurveVisibility();
		camera_controller.setCurrentCamera(arcball_camera);
		camera_controller.setSensitivity(0.5);
		camera_controller.update();
		glutPostRedisplay();
		break;
	case 5:
		toggleFirstPersonView();
		break;
    default:
        printf("Invalid menu selection. Aborting.");
        exitProgram(1);
    }

	glutTimerFunc(10, &fixMenuCallback, 0);
}

void processHeroArcball(int value) {
	switch (value) {
	case 0:
		arcball_camera.setParent(tim_the_enchanter.getTransform());
		break;
	case 1:
		arcball_camera.setParent(krandul.getTransform());
		break;
	case 2:
		arcball_camera.setParent(jaegansmann.getTransform());
		break;
	}
}

void processHeroFirst(int value) {
	switch (value) {
	case 0:
		first_person_camera.setParent(tim_the_enchanter.getTransform(), 12);
		break;
	case 1:
		first_person_camera.setParent(krandul.getTransform(), 6.5);
		first_person_camera.setTheta(M_PI);
		break;
	case 2:
		first_person_camera.setParent(jaegansmann.getTransform(), 6.5);
		break;
	}
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
	//Arcball camera submenu
	int heroArcball = glutCreateMenu(processHeroArcball);
	glutAddMenuEntry("Enchanter", 0);
	glutAddMenuEntry("Krandul", 1);
	glutAddMenuEntry("Jaegansmann", 2);

	//first person camera submenu
	int heroFirst = glutCreateMenu(processHeroFirst);
	glutAddMenuEntry("Enchanter", 0);
	glutAddMenuEntry("Krandul", 1);
	glutAddMenuEntry("Jaegansmann", 2);

	//main menu
    glutCreateMenu(&myMenu);
    glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("Display Control Cage", 1);
	glutAddMenuEntry("Display Bezier Curve", 2);
	glutAddMenuEntry("Use Free Camera", 3);
	glutAddSubMenu("Use Arcball Camera", heroArcball);
	glutAddMenuEntry("Show/Hide first person camera", 5);
	glutAddSubMenu("First Person Camera Target", heroFirst);

    glutAttachMenu(2); // RMB
}

void normalKeysDown(unsigned char key, int x, int y) {
	keyboard.normalKeysDown(key, x, y);
}

void normalKeysUp(unsigned char key, int x, int y){
	keyboard.normalKeysUp(key, x, y);
}

// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Does not process command line arguments.
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {

	// Make sure a control point CSV file was passed in.
    if(argc != 2){
        printf("Error - %d arguments provided, 2 required\n\tusage: lab03.exe [world_file.json]\n", argc);
        exitProgram(1);
    }

    parseJSON(argv[1]);

	tim_the_enchanter.setBezierPatch(patches);
	//Create Heros
	//Enchanter = Hero_tim(Transform3D(Vector3(0,0,0)));

	//Create Heros
	//Enchanter = Hero_tim(Transform3D(Vector3(0,0,0)));

    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Exploring with the pet!");

	// light.turnOff();

	createMenus();

	arcball_camera.setRadius(70);

    // register callback functions...
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(normalKeysDown);
    glutKeyboardUpFunc(normalKeysUp);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resizeWindow);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);

    // Set up the timer
    glutTimerFunc(10, &myTimer, 10);
    // do some basic OpenGL setup
    initScene();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
