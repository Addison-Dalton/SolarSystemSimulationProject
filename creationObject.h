#include "template.h"
#include <math.h>
#include <string>

using namespace std;
using namespace AGK;


class CreationObject		// 
{
private:
   int spriteIndex;  // The sprite index
   char* imageFile; // The name of the image file
   float positionX;
   float positionY;
   int depth; //depth of sprite
   float sizeX; //scaleSize in X
   float sizeY; //scaleSize in Y
   float objectMass; //mass of sprite
  
public:
   // Constructors
   CreationObject();
   CreationObject(int index, char* filename,float pX, float pY, int pDepth, float pSizeX, float pSizeY,float mass);
    
   // -------------------- Mutators-----------------------
   void createSprite();
   void createSprite(int SPRITE_INDEX, char* filename);
   void setPosition(float, float);
   void setX(float);
   void setY(float);
   void spriteSize(float, float);
   void setDepth(int);
   void setMass(float); //mass
   // --------------------Accessors------------------------
   int getSpriteIndex() ;
   char* getImageFile() ;
   //position
   float getX() ;
   float getY() ;
   //width and height
   float getWidth() ;
   float getHeight() ;
   //depth
   int getDepth();
   //mass
   float getMass() ;
   // Destructor
   void deleteSprite();
   //checks if sprite exists
   bool getObjectExist();

};