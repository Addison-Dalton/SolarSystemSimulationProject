#include "template.h"
#include <string>
using namespace std;
using namespace AGK;
app App3;

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
   double objectMass;
  
public:
   // Constructors
   CelestialObject();
   CelestialObject(int SPRITE_INDEX, string filename,float pX, float pY, float VX, float VY, float AX, float AY, double mass);
    
   // Mutators
   void createSprite();
   void createSprite(int SPRITE_INDEX, string filename);
   void setPosition(float, float);
   void setX(float);
   void setY(float);
   //velocity
   void setVX(float); 
   void setVY(float);
   //accel
   void setAX(float);
   void setAY(float);
   void spriteSize(float, float);
   //mass
   void setMass(double); //mass
   // Accessors
   int getSpriteIndex() const;
   string getImageFile() const;
   float getX() const;
   float getY() const;
   //velocity
   float getVX() const;
   float getVY() const;
   //accel
   float getAX() const;
   float getAY() const;
   //mass
   double getMass() const;
   //width and height
   float getWidth() const;
   float getHeight() const;
   // Destructor
   void deleteSprite();
};