/*
Authors:
Wisam Reid cs184-ds
Eddie Groshev cs184-en
*/

#include "circle.h"
#include <cmath>
#include <algorithm>

// stl :: string theory labs (taking over a universe near you) 
using namespace stl;

extern Viewport viewport;
//extern Camera camera;
extern std::vector<Light*> lights;
#define PI 3.14159265;
#define EPSILON 0.000000000001

double textureWidth = 10;

Circle::Circle() : radius(1.0), center(0.0), ka(0.0), kd(0.0), ks(0.0), sp(1.0), nu(0.0), nv(0.0), outline(false), quantize(0), anisotropic(false), perlin(false), zoom(0), decayRate(0), octaves(0)
{
    // Intentionally empty
}

Circle::Circle(Vector c_, double r_) : radius(r_), center(c_), ka(0.0), kd(0.0), ks(0.0), sp(1.0), nu(0.0), nv(0.0), outline(false), quantize(0), anisotropic(false), perlin(false), zoom(0), decayRate(0), octaves(0)
{
    // Intentionally empty
}

Vector Circle::getNormal(Vector pointInWorldFrame) const { Vector temp = pointInWorldFrame-center; return temp/temp.magnitude();}

void Circle::setOutline(bool outline_) { outline=outline_; }
void Circle::setQuantize(int amount_) { quantize=std::max(amount_,0); }
void Circle::setPerlinTexture(bool perlin_, double zoom_, double decayRate_, int octaves_) { perlin=perlin_; zoom=zoom_; decayRate=decayRate_; octaves=octaves_; }

void Circle::setCenter(Vector c_){ center=c_; }
void Circle::setRadius(double r_){ radius=r_; }
void Circle::setAmbientCoef(Color ka_){ ka=ka_; }
void Circle::setDiffuseCoef(Color kd_){ kd=kd_; }
void Circle::setSpecularCoef(Color ks_){ ks=ks_; }
void Circle::setSpecularPow(double sp_){ sp=sp_; }
void Circle::setAnisotropicCoef(double nu_, double nv_){ anisotropic=true; nu=nu_; nv=nv_; }

void Circle::draw()
{
    /************************************
    *
    * Code paraphrased from TA example 
    *
    ************************************/

    glBegin(GL_POINTS);

    int i,j; // pixel index

    // X
    int minX = std::max(0,(int)floor(this->center.getX()-this->radius)-50);
    int maxX = std::min(viewport.getW()-1,(int)ceil(this->center.getX()+this->radius)+50);
    // Y
    int minY = std::max(0,(int)floor(this->center.getY()-this->radius)-50);
    int maxY = std::min(viewport.getH()-1,(int)ceil(this->center.getY()+this->radius)+50);

    for (i=minX;i<maxX;i++) {
      for (j=minY;j<maxY;j++) {

        // Location of the center of pixel relative to center of sphere
        float x = (i+0.5-center.getX());
        float y = (j+0.5-center.getY());

        float dist = sqrt(std::pow(x,2) + std::pow(y,2));
        
        if (outline && dist > radius && dist < radius + 4.0) { //4 is the outline thinkness
          viewport.setPixel(i, j, Color(0.0));
        }
        else if (dist<=radius) {
          Color pixelColor = Color(0.0);

          // This is the front-facing Z coordinate
          float z = sqrt(radius*radius-dist*dist);
          Vector pointInWorldFrame = Vector(i+0.5,j+0.5,z);

          Vector normal;
          if (perlin) {
            normal = perlinTexture(i, j, this->getNormal(pointInWorldFrame));
          } else {
            normal = this->getNormal(pointInWorldFrame);
          }
          for (int k=0; k<lights.size(); k++){
            if (perlin){
              double dotprod = this->getNormal(pointInWorldFrame).dot(-lights[k]->getDirectionAt(pointInWorldFrame));
              if (dotprod <= 0){ continue; }
            }
            Color result = this->BRDF(lights[k]->getIntensity(), -lights[k]->getDirectionAt(pointInWorldFrame), Vector(0,0,1), normal);

            if (quantize > 0){
                pixelColor += result.descretized(1.0/quantize);
            }
            else {
                pixelColor += result;
            }
          }

          viewport.setPixel(i, j, pixelColor);
          //viewport.setPixel(i, j, texturize(pointInWorldFrame, textureWidth, pixelColor));
        }
      }
    }
    glEnd();

   /*************************************/ 
}

void Circle::resize(){
  double x = viewport.getW()/2.0;
  double y = viewport.getH()/2.0;
  double r = std::min(viewport.getW(),viewport.getH())*0.9/2.0;
  center = Vector(x,y,0.0);
  radius = r;
}

Color removeInvalid(Color c){
  double r = c.getR();
  double newR;
  if (r!=r || r<0.0) newR = 0.0;
  else newR = r;
  double g = c.getG();
  double newG;
  if (g!=g || g<0.0) newG = 0.0;
  else newG = g;
  double b = c.getB();
  double newB;
  if (b!=b || b<0.0) newB = 0.0;
  else newB = b;
  return Color(newR, newG, newB);
}

Color Circle::BRDF(Color lightIntensity, Vector lightDirection, Vector viewer, Vector normal)
{
    double c_1 = 1.0;
    if (anisotropic){
        //http://www.cs.utah.edu/~shirley/papers/jgtbrdf.pdf
        //Anisotropic Phong BRDF diffuse
        double c_2 = (1-pow(1-normal.dot(lightDirection)/2.0,5))*(1-pow(1-normal.dot(viewer)/2.0,5));
        c_2 = c_2*28.0/23.0/PI;
        Color color = removeInvalid(kd*(ks*-1+1)*c_2)*lightIntensity;

        //Anisotropic Phong BRDF specular
        Vector halfVec = viewer+lightDirection;
        halfVec /= halfVec.magnitude();

        //Compute basis vectors
        Vector u = Vector(normal.getZ(),normal.getX(),-normal.getY()); //After a bunch of guess and check normal vectors, this seemed to match the pictures in the paper.
        u /= u.magnitude();

        Vector v = normal.cross(u);
        v /= v.magnitude();

        double exponent = (nu*pow(halfVec.dot(u),2)+nv*pow(halfVec.dot(v),2))/(1-pow(halfVec.dot(normal),2));
        double c_3 = pow(normal.dot(halfVec),exponent);
        double denom = halfVec.dot(lightDirection)*std::max(normal.dot(lightDirection),normal.dot(viewer));
        c_3 *= sqrt((nu+1)*(nv+1))/8.0/denom/PI;
        color += removeInvalid((ks+(ks*-1+1)*pow(1-halfVec.dot(lightDirection), 5))*c_3)*lightIntensity;
        color += ka*lightIntensity*c_1;

        return color;
    } else {
        //Regular ambient, diffuse, specular stuff...
        double c_2 = std::max(0.0, (lightDirection).dot(normal));
        Vector reflection = -lightDirection + normal*(lightDirection.dot(normal))*2.0;
        double c_3 = pow(std::max(0.0, reflection.dot(viewer)), sp);
        
        return ka*lightIntensity*c_1 + kd*lightIntensity*c_2 + ks*lightIntensity*c_3;
    }
}

void decodeOneStep(const char* filename)
{
  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;

  //decode
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

std::vector<unsigned char> image; //the raw pixels
unsigned width, height;
//decode
unsigned error = lodepng::decode(image, width, height, "autosave/cel_shading.png");

Color Circle::texturize(Vector point, double w, const Color& c)
{
  double theta = std::acos((point.getZ()-center.getZ())/radius);
  double phi = std::atan2(point.getY()-center.getY(),point.getX()-center.getX());
  //double theta = std::acos(point.getY()-center.getY());
  //double phi = std::atan2((point.getZ()-center.getZ())/radius,point.getX()-center.getX());
  if (phi<0.0) { phi += 2*PI;}
  double u = phi/2.0;
  u /= PI;
  double v = PI-theta;
  v /= PI;

  int x = (int)((height-1))*u;
  int y = (int)((width-1))*v;
  std::cout << "x: " << x << "y: " << y << std::endl;
  //x = u;
  //y = v;

  double r = image[y*width*4+x*4+0];
  double g = image[y*width*4+x*4+1];
  double b = image[y*width*4+x*4+2];

  //r = image[x*height*4+y*4+0];
  //g = image[x*height*4+y*4+1];
  //b = image[x*height*4+y*4+2];

  return Color(r/255.0,g/255.0,b/255.0);


  double t;
  //t = point[0];
  t = u;
  t/=5.0;
  //t/=point[1]/2.0;
  t*=PI;
  t= sin(t);
  t+=1;
  t/=2.0;
  //t = (1 + sin ((point[0]/w)*PI))/2.0;

  return c.normalized()*(1-t) + ((c.normalized()*-0.1)+1)*t;
}


// Citation: http://rosettacode.org/wiki/Linear_congruential_generator 
double Circle::random(double x,double y)
{
   int prime=(int)x+(int)y*57;
    prime=(prime<<13)^prime;
     int n=(prime*(prime*prime*60493+19990303)+1376312589)&0x7fffffff;
      return 1.0-((double)n/1073741824.0);
} 

// Perlin texture, random distribution of surface normals 
Vector Circle::perlinTexture(int i, int j, Vector normal){
      double getNoiseX = 0.0; 
      double getNoiseY = 0.0;
      double getNoiseZ = 0.0;
      for(int k=0;k<octaves-1;k++){
        double frequency = pow(2,k);
        double amplitude = pow(decayRate,k);
        getNoiseX += random(((double)i)*frequency/zoom,((double)j)/zoom*frequency)*amplitude;
        getNoiseY += random(((double)i)*frequency/zoom,((double)j)/zoom*frequency)*amplitude;
        getNoiseZ += random(((double)i)*frequency/zoom,((double)j)/zoom*frequency)*amplitude;
      }
      Vector noize = Vector(getNoiseX, getNoiseY, getNoiseZ);
      return normal * noize;
}

