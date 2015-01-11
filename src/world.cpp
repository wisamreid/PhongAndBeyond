#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cassert>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include "viewport.h"
#include "vector.h"
#include "color.h"
#include "light.h"
#include "shape.h"
#include "circle.h"


#define PI 3.14159265  // Should be used from mathlib
#define SPACE_BAR ' '
#define MAX_NUM_PL 5
#define MAX_NUM_DL 5

using namespace stl;

//****************************************************
// Global Variables
//****************************************************
Viewport  viewport;
double sphereRadius; //This is a hack used to complete assignment specs

std::vector<Light*> lights;
std::vector<Shape*> shapes;
Camera camera;

int mouseLight = 0;
int mouseLightRadius = 1000;


//****************************************************
// Simple init function
//****************************************************
void initScene(){

  // Nothing to do here for this simple example.

}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.resize(w,h);

  for (int i=0; i<shapes.size(); i++){
    shapes[i]->resize();
  }

  sphereRadius = std::min(viewport.getW(),viewport.getH())*0.9/2.0;

  glViewport (0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);

}


//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer

  glMatrixMode(GL_MODELVIEW); // indicate we are specifying camera transformations
  glLoadIdentity(); // make sure transformation is "zero'd"

  if (!fileName.empty()){
    viewport.beginImage();
  }

  // Start drawing
  for (int i=0; i < shapes.size(); i++){
    shapes[i]->draw();
  }
  
  if (!fileName.empty()){
    viewport.endImage();
    viewport.writeImage(fileName.c_str());
    exit(0);
  }

  glFlush();
  glutSwapBuffers(); // swap buffers (we earlier set double buffer)
}

//****************************************************
// function to process keyboard input
//***************************************************
void myKeyboard(unsigned char key, int x, int y) {
  if (key == 'q' || key == SPACE_BAR) {
    exit(0);
  }
  if (isdigit(key)){
    mouseLight = (std::atoi((const char*)&key)-1)%lights.size();
    std::cout << "Active light source: " << mouseLight << std::endl;
  }
}

void myArrowKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      mouseLightRadius += 100;
      break;  
    case GLUT_KEY_DOWN:
      mouseLightRadius -= 100;
      break;
    case GLUT_KEY_LEFT:
      //do something here
      break;
    case GLUT_KEY_RIGHT:
      //do something here
      break;
  }
  if (mouseLightRadius<0) {mouseLightRadius=0;}
  std::cout << "Active light radius: " << mouseLightRadius << std::endl;
  glutPostRedisplay();
}

//****************************************************
// function to process mouse input
//***************************************************
void myMouse(int button, int state, int x, int y) {
  //Do something later.
  //Possible button inputs: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
  //Possible state inputs: GLUT_UP or GLUT_DOWN 
}

void myMouseMotion(int mouseX, int mouseY) {
  // Location of the center of pixel relative to center of sphere
  float radius = mouseLightRadius;
  float x = (mouseX-viewport.getW()/2.0);
  float y = -(mouseY-viewport.getH()/2.0);
  float dist = sqrt(std::pow(x,2) + std::pow(y,2));
  if (dist > radius) { dist = radius;}
  float z = sqrt(radius*radius-dist*dist);
  if (lights.size()>0){
    lights[mouseLight]->moveLight(Vector(x,y,z));
  }

  glutPostRedisplay();
}














