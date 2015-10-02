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

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

// For some reason, math.h isn't including constants - maybe an old version on the machine I'm compiling on...
#define M_PI 3.141592654

// My objects
#include "BezierCurve.hpp"
#include "Camera.hpp"
#include "Tree.hpp"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth  = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton; 		   	            // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse

float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
float radius = 10.0;                         // camera ZOOM in spherical coordinates

GLuint environmentDL;                       // display list for the 'world' - static, unmoving objects only

CameraController c;
BezierCurve b;

void exitProgram(int exit_val) {
	#ifdef __APPLE__			// if compiling on Mac OS
		_exit(exit_val);
	#else
		exit(exit_val);
	#endif
}

// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float getRand() {
   	return rand() / (float)RAND_MAX;
}

bool loadControlPoints( char* filename ) {
    char buffer[20];
    FILE *oFile;
    int pointCount;
    float x, y, z;
    std::vector<Point> pointVector;

    oFile = fopen(filename, "r");
    if(fgets(buffer, sizeof(buffer), oFile) != 0){
        if(sscanf(buffer, "%d", &pointCount) == 1){
            for(int i(0); i < pointCount; ++i){
                fgets(buffer, sizeof(buffer), oFile);
                sscanf(buffer, "%f,%f,%f", &x, &y, &z);
                b.addPoint(Point(x, y, z));
            }
        } else {
            printf("Error: \"%s\" is in the wrong format.\n", filename);
            exitProgram(1);
        }
    } else {
        printf("Error: \"%s\" could not be opened for reading.\n", filename);
        exitProgram(1);
    }


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
    bool ctrl_pressed = glutGetModifiers() == GLUT_ACTIVE_CTRL;

    if(leftMouseButton == GLUT_DOWN && !ctrl_pressed) {
        int deltaX = x - mouseX;
        int deltaY = y - mouseY;

        mouseX = x;
        mouseY = y;

        c.handleInput(deltaX, deltaY, 0.0);
    } else if (leftMouseButton == GLUT_DOWN && ctrl_pressed){
        int deltaY = y - mouseY;

        mouseY = y;

        c.handleInput(0.0, 0.0, deltaY);
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

    //******************************************************************
    // this is some code to enable a default light for the scene;
    // feel free to play around with this, but we won't talk about
    // lighting in OpenGL for another couple of weeks yet.
    float lightCol[4] = { 1, 1, 1, 1};
    float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
    float lPosition[4] = { 10, 10, 10, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // tell OpenGL not to use the material system; just use whatever we
    // pass with glColor*()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //******************************************************************

    glShadeModel(GL_FLAT);

    srand( time(NULL) );	// seed our random number generator

    generateEnvironmentDL();
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void)  {
    //clear the render buffer
    glDrawBuffer( GL_BACK );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
    glLoadIdentity();

    // Yay for simple camera objects
    c.update();

    // Iterate through the environment list and draw things
    glCallList(environmentDL);


	b.draw(64); // Draw the curve with resolution, parented to the vehicle


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

    if(key == 'w'){
        // v.driveForward();
    }else if(key == 'd'){
        // v.turnRight();
    }else if(key == 's'){
        // v.driveBackward();
    }else if(key == 'a'){
        // v.turnLeft();
    }
}



void myTimer(int value){
    glutPostRedisplay();

    glutTimerFunc(value, &myTimer, value);
}

void fixMenuCallback(int value){
	if(b.isControlCageVisible()){
		glutChangeToMenuEntry(2, "Hide Control Cage", 1);
	} else {
		glutChangeToMenuEntry(2, "Display Control Cage", 1);
	}

	if(b.isCurveVisible()){
		glutChangeToMenuEntry(3, "Hide Bezier Curve", 2);
	} else {
		glutChangeToMenuEntry(3, "Display Bezier Curve", 2);
	}
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
		b.toggleControlCageVisibility();
		break;
	case 2:
		b.toggleCurveVisibility();
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
        printf("Error - %d arguments provided, 2 required\n\tusage: lab03.exe [example.csv]\n", argc);
        exitProgram(1);
    }

    loadControlPoints(argv[1]);

    // create a double-buffered GLUT window at (50,50) with predefined windowsize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Exploring with the pet!");

	createMenus();

    // register callback functions...
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutKeyboardFunc(normalKeysDown);
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
