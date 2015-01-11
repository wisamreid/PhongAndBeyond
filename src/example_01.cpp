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

std::string fileName = "";

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

  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"

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
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
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
  /*
  float radius = mouseLightRadius;
  float x = (mouseX-viewport.getW()/2.0);
  float y = -(mouseY-viewport.getH()/2.0);
  float dist = sqrt(std::pow(x,2) + std::pow(y,2));
  if (dist > radius) { dist = radius;}
  float z = sqrt(radius*radius-dist*dist);
  if (lights.size()>0){
    lights[mouseLight]->moveLight(Vector(x,y,z));
  }*/


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

//****************************************************
// function to parse the command line arguments
//***************************************************
void argParser(int* argc, char** argv) {
  int num_dl = 0;
  int num_pl = 0;

  double x = viewport.getW()/2.0;
  double y = viewport.getH()/2.0;
  double r = std::min(viewport.getW(),viewport.getH())*0.9/2.0;
  sphereRadius = r;
  shapes.push_back(new Circle(Vector(x,y,0.0),r));

  std::string arg;
  for (int i=1; i < *argc; i++) {
    arg = argv[i];

    if (arg.compare("-new") == 0) {
      arg = argv[++i];
      if (arg.compare("sphere") == 0){
        double x = std::atof(argv[++i]);
        double y = std::atof(argv[++i]);
        double r = std::atof(argv[++i]);
        shapes.push_back(new Circle(Vector(x,y,0.0),r));
      }
    }
    else if (arg.compare("-ka") == 0) {
      //Ambient color coefficients
      double r = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double g = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double b = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      Color ka = Color(r,g,b);
      shapes.back()->setAmbientCoef(ka);
      std::cout << "Ambient CC: " << r << ", " << g << ", " << b << std::endl;
    }
    else if (arg.compare("-kd") == 0) {
      //Diffuse color coefficients
      double r = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double g = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double b = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      Color kd = Color(r,g,b);
      shapes.back()->setDiffuseCoef(kd);
      std::cout << "Diffuse CC: " << r << ", " << g << ", " << b << std::endl;
    }
    else if (arg.compare("-ks") == 0) {
      //Specular color coefficients
      double r = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double g = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      double b = std::min(1.0,std::max(0.0,std::atof(argv[++i])));
      Color ks = Color(r,g,b);
      shapes.back()->setSpecularCoef(ks);
      std::cout << "Specular CC: " << r << ", " << g << ", " << b << std::endl;
    }
    else if (arg.compare("-sp") == 0) {
      //Power coefficient on specular term
      double power = std::atof(argv[++i]); // 0 to max_double
      shapes.back()->setSpecularPow(power);
      std::cout << "Specular Power: " << power << std::endl;
    }
    else if (arg.compare("-pl") == 0) {
      if (num_pl < MAX_NUM_PL) {
        //Add point light
        double x = std::atof(argv[++i]);
        double y = std::atof(argv[++i]);
        double z = std::atof(argv[++i]);
        double r = std::atof(argv[++i]);
        double g = std::atof(argv[++i]);
        double b = std::atof(argv[++i]);
        lights.push_back(new PointLight(Vector(x,y,z),Color(r,g,b)));
        num_pl++;
        std::cout << *(lights.back()) << std::endl;
      } else {
        std::cout << "Cannot add more than 5 POINT lights..." << std::endl;
      }
    }
    else if (arg.compare("-dl") == 0) {
      if (num_dl < MAX_NUM_DL) {
        //Add directional light
        double x = std::atof(argv[++i]);
        double y = std::atof(argv[++i]);
        double z = std::atof(argv[++i]);
        double r = std::atof(argv[++i]);
        double g = std::atof(argv[++i]);
        double b = std::atof(argv[++i]);
        lights.push_back(new DirectionLight(Vector(x,y,z),Color(r,g,b)));
        num_dl++;
        std::cout << *(lights.back()) << std::endl;
      } else {
        std::cout << "Cannot add more than 5 DIRECTIONAL lights..." << std::endl;
      }
    }
    else if (arg.compare("-s") == 0) {
      fileName = (std::string)"autosave/"+(std::string)(argv[++i]);
      std::cout << fileName << std::endl;
    }
    else if (arg.compare("-o") == 0) {
      shapes.back()->setOutline(true);
      glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Clear to gray, fully transparent
    }
    else if (arg.compare("-q") == 0) {
      shapes.back()->setQuantize(std::atof(argv[++i]));
    }
    else if (arg.compare("-a") == 0) {
      //Anisotropic, phong-like exponents to control the shape of the specular lobe.
      double nu = std::atof(argv[++i]);
      double nv = std::atof(argv[++i]);
      shapes.back()->setAnisotropicCoef(nu,nv);
    }
    else if (arg.compare("-t") == 0) {
      //Texture
      shapes.back()->setPerlinTexture(true,std::atof(argv[++i]),std::atof(argv[++i]),std::atoi(argv[++i]));
    }

  }

}

//Functions to test our code
void test() {
  std::cout << std::endl << "BEGIN TEST FUNCTION" << std::endl;
  viewport.beginImage();
  myDisplay();
  viewport.endImage();
  viewport.writeImage("test.png");

  //Test Color class
  Color c1 = Color();
  assert(c1.getR()==0.0 && c1.getG()==0.0 && c1.getB()==0.0);
  std::cout << c1 << std::endl;
  Color c2 = Color(0.1,0.2,0.5);
  assert(c2.getR()==0.1 && c2.getG()==0.2 && c2.getB()==0.5);
  std::cout << c2 << std::endl;
  Color c3 = c2+c2+c2;
  std::cout << c3 << std::endl;

  //Test Vector class
  Vector v1 = Vector();
  Vector v2 = Vector(2,1,2);
  Vector v3 = Vector(9);
  Vector v4 = Vector(1,1,1);
  Vector v5 = Vector(1,-1,1);
  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << v3 << std::endl;
  std::cout << v4.cross(v5) << std::endl;
  std::cout << v5.cross(v4) << std::endl;
  std::cout << v2.dot(v3) << std::endl;
  std::cout << v2.magnitude() << std::endl;
  std::cout << v2/v2.magnitude() << std::endl;

  //Test Light class
  PointLight pl1 = PointLight(Vector(11,12,13));
  DirectionLight dl1 = DirectionLight(Vector(14,15,16));
  std::cout << pl1 << std::endl;
  std::cout << dl1 << std::endl;

  std::cout << "END TEST FUNCTION" << std::endl << std::endl;
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

  //This initializes glut
  glutInit(&argc, argv);
  
  // Initalize theviewport
  viewport = Viewport(400,400);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  //The size and position of the window
  glutInitWindowSize(viewport.getW(), viewport.getH());
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  //This parses the arguments and sets up the global variables
  argParser(&argc, argv);

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape); // function to run when the window gets resized
  glutKeyboardFunc(myKeyboard); // function to run when keyboard input is received
  glutSpecialFunc(myArrowKeys); // function to run when arrow keys are pressed
  glutMotionFunc(myMouseMotion); // function to run when mouse input is received
  glutMouseFunc(myMouse);  // function to run when mouse input is received
  

  myDisplay();

  //test();

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}








