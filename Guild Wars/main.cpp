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

#define BUFFER_SIZE 128

// My objects
#include "BezierCurve.hpp"
#include "BezierPatch.hpp"
#include "BezierPatchDrawer.hpp"
#include "Camera.hpp"
#include "Tree.hpp"
#include "Light.hpp"
#include "Transform3D.hpp"
#include "CameraController.hpp"
#include "ArcBallCamera.hpp"
#include "FreeCamera.hpp"
#include "GameClock.hpp"
#include "HeroNameDrawer.hpp"

// Included JSONcpp framework
// https://github.com/open-source-parsers/jsoncpp
#include "JSON.hpp"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 1366;
static size_t windowHeight = 768;
static float aspectRatio;

GLint leftMouseButton; 		   	            // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse

float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
float radius = 10.0;                         // camera ZOOM in spherical coordinates

GLuint environmentDL;                       // display list for the 'world' - static, unmoving objects only

BezierPatchDrawer *bezierDrawer;
BezierPatch *patches;

ArcBallCamera arcball_camera(90, 45);
FreeCamera free_camera(0, 2, 0);
CameraController camera_controller(arcball_camera, 0.5);

GameClock game_clock;

Transform3D krandul_transform;
HeroNameDrawer krandul_name_drawer(krandul_transform, "Krandul");

Light light(Transform3D(Vector3(0, 10, 0)), Color(1, 1, 1), Color(0, 0, 0));
bool leftCtrlMouse = false;

bool keysPressedArray[BUFFER_SIZE];
bool keysUpArray[BUFFER_SIZE];

using namespace std;

void exitProgram(int exit_val) {
	#ifdef __APPLE__			// if compiling on Mac OS
		_exit(exit_val);
	#else
		exit(exit_val);
	#endif
}

// global variable to keep track of the window id
int windowId;
void* default_font = GLUT_BITMAP_9_BY_15;
void* default_stroke_font = GLUT_STROKE_ROMAN;

void glutBitmapString(void* font, string to_draw) {
    for (int i = 0; i < to_draw.size(); ++i) {
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

	const Json::Value tim_hero = root.get("TimHero", "ASCII");
	printf("Tim: %s\n", tim_hero.get("BezierCurveFile", "ASCII").asString().c_str());

	const Json::Value trevor_hero = root.get("TrevorHero", "ASCII");
	printf("Trevor: %s\n", trevor_hero.get("BezierCurveFile", "ASCII").asString().c_str());
	string trevor_curve_file = trevor_hero.get("BezierCurveFile", "ASCII").asString();
	BezierCurve trevor_curve(parseCSVintoVector(strdup(trevor_curve_file.c_str())));

	const Json::Value chris_hero = root.get("ChrisHero", "ASCII");
	printf("Chris: %s\n", chris_hero.get("BezierCurveFile", "ASCII").asString().c_str());
	string chris_curve_file = chris_hero.get("BezierCurveFile", "ASCII").asString();
	BezierCurve chris_curve(parseCSVintoVector(strdup(chris_curve_file.c_str())));
	
	return true;
}





// drawGrid() //////////////////////////////////////////////////////////////////
//
//  Function to draw a grid in the XZ-Plane using OpenGL 2D Primitives (GL_LINES)
//
////////////////////////////////////////////////////////////////////////////////
void drawGrid() {
    /*
     *	We will get to why we need to do this when we talk about lighting,
     *	but for now whenever we want to draw something with an OpenGL
     *	Primitive - like a line, quad, point - we need to disable lighting
     *	and then reenable it for use with the GLUT 3D Primitives.
     */
    glDisable( GL_LIGHTING );

    glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);

    glBegin(GL_LINES);
        for(int i = -50; i < 50; ++i){
            glVertex3f(-50.0, 0.0, i);
            glVertex3f(50.0, 0.0, i);

            glVertex3f(i, 0.0, -50.0);
            glVertex3f(i, 0.0, 50.0);
        }
    glEnd();

    glEnable( GL_LIGHTING );
}

void drawForest(){
    for(int i = -50; i < 50; ++i){
        for(int j = -50; j < 50; ++j){
            if(getRand() > 0.995){
                Tree t(i, 0.0, j);
                t.draw();
            }
        }
    }
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
        glPushMatrix(); {
            drawGrid();
            drawForest();
        }; glPopMatrix();
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

void clearKeySignalArray(){
    for(int i(0); i < BUFFER_SIZE; ++i){
        keysPressedArray[i] = false;
        keysUpArray[i] = false;
    }
}

void handleKeySignals(){
    // Here is where you map signals to actions
    // Example:
    // if(keysPressedArray['w']){
    //     something.moveForward();
    // }
    // maps the signal 'w' to the action something.moveForward()

	if(keysPressedArray['1']){
		// b->toggleControlCageVisibility();
	}

	if(keysPressedArray['2']){
		// b->toggleCurveVisibility();
	}

    // Clear both buffers
    clearKeySignalArray();
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

	handleKeySignals();

    //clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();

    // Yay for simple camera objects
    camera_controller.update();

	light.tellOpenGL();
    // Iterate through the environment list and draw things
    glCallList(environmentDL);

	bezierDrawer->draw();
	renderHeroNames();
	renderHUD();

    //push the back buffer to the screen
    glutSwapBuffers();
}


// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown(unsigned char key, int x, int y) {
    if(key == 'q' || key == 'Q' || key == 27)
        exitProgram(0);

    keysPressedArray[int(key)] = true;
}

void normalKeysUp(unsigned char key, int x, int y){
    keysUpArray[int(key)] = true;
}


void myTimer(int value){
    glutPostRedisplay();

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
    default:
        printf("Invalid menu selection. Aborting.");
        exitProgram(1);
    }

	glutTimerFunc(10, &fixMenuCallback, 0);
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
    glutCreateMenu(&myMenu);
    glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("Display Control Cage", 1);
	glutAddMenuEntry("Display Bezier Curve", 2);
	glutAddMenuEntry("Use Free Camera", 3);
	glutAddMenuEntry("Use Arcball Camera", 4);
    glutAttachMenu(2); // RMB
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

    clearKeySignalArray();

    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Exploring with the pet!");

	createMenus();

	arcball_camera.setRadius(30);

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
