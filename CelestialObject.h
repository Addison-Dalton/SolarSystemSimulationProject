#include "template.h"
#include <math.h>
#include <string>

using namespace std;
using namespace AGK;


class CelestialObject		// 
{
private:
   int spriteIndex;  // The sprite index
   string imageFile; // The name of the image file
   float positionX;
   float positionY;
   float velocityX;
   float velocityY;
   float accelX;
   float accelY;
   float objectMass;
   bool  leftClick;
   bool  rightClick;
   bool targeted;
  
public:
   // Constructors
   CelestialObject();
   CelestialObject(int index, string filename,float pX, float pY, float VX, float VY, float AX, float AY, float mass);
    
   // -------------------- Mutators-----------------------
   void createSprite();
   void createSprite(int SPRITE_INDEX, string filename);
   void setPosition(float, float);
   void setX(float);
   void setY(float);
   //velocity
   void setVX(float); 
   void setVY(float);
   void setV(float, float);
   //accel
   void setAX(float);
   void setAY(float);
   void spriteSize(float, float);
   //ClickDetections
   void setleftClick(bool);
   void setRightClick(bool);
   void setTargeted(bool);
   void intializeObject(); //might not use
   void setMass(float); //mass

   // --------------------Accessors------------------------
   int getSpriteIndex() ;
   string getImageFile() ;
   //position
   float getX() ;
   float getY() ;
   //velocity
   float getVX() ;
   float getVY() ;
   //accel
   float getAX() ;
   float getAY() ;
   //mass
   float getMass() ;
   //width and height
   float getWidth() ;
   float getHeight() ;
   //click detections
   bool getleftClick();
   bool getRightClick();
   bool getTargeted();
   // Destructor
   void deleteSprite();
   void nullObject();

   //checks if sprite exists
   bool getObjectExist();

};