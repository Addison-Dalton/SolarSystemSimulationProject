#include "template.h"
#include <math.h>
#include <string>
#include "creationObject.h"
using namespace std;
using namespace AGK;



// This is the default constructor for the Sprite class.
// It sets index to 1 and imageFile to an empty string.
CreationObject::CreationObject()
{
   spriteIndex = 1;
   imageFile = "";
}

// This Sprite class constructor accepts as arguments
// the sprite index and the name of the image file,
// and initializes the member variables.
CreationObject::CreationObject(int index, char* filename,float pX, float pY,int pDepth, float pSizeX, float pSizeY, float pMass)
{
   spriteIndex = index;
   imageFile = filename;

   positionX = pX;
   positionY = pY;

   depth = pDepth;
   sizeX = pSizeX;
   sizeY = pSizeY;
   objectMass = pMass;
}


// The Sprite::createSprite member function 
void CreationObject::createSprite()
{
   // If the sprite does not already exist,
   //     then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile);
	  agk::SetSpritePosition(spriteIndex, positionX, positionY); //object position
	  agk::SetSpriteDepth(spriteIndex,depth); //objects depth
	  agk::SetSpriteScale(spriteIndex,sizeX,sizeY); //objects scale
   }
}
//---------------------------------constructors-----------------------------------------
void CreationObject::createSprite(int index, char* filename)
{
   // Set the member variables.
   spriteIndex = index;
   imageFile = filename;

   // If the sprite does not already exist,
   //   then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile);
	  agk::SetSpritePosition(spriteIndex, positionX, positionY); //object position
	  agk::SetSpriteDepth(spriteIndex,depth); //objects depth
	  agk::SetSpriteScale(spriteIndex,sizeX,sizeY); //objects scale

   }
}

//-----------------------------------------Mutators-------------------------------------------
// sets the sprite's position.
void CreationObject::setPosition(float x, float y)
{
   agk::SetSpritePosition(spriteIndex, x, y);
   positionX = x;
   positionY = y;
}

// sets the sprite's X coordinate.
void CreationObject::setX(float x)
{
   agk::SetSpriteX(spriteIndex, x);
   positionX = x;
}

// sets the sprite's Y coordinate.
void CreationObject::setY(float y)
{
   agk::SetSpriteY(spriteIndex, y);
   positionY = y;
}

//sets size of sprite by a ratio
void CreationObject::spriteSize(float psizeX, float psizeY)
{
	agk::SetSpriteScale(spriteIndex, psizeX,psizeY);
	sizeX = psizeX;
	sizeY = psizeY;
}
//sets depth of sprite
void CreationObject::setDepth(int pDepth)
{
	agk::SetSpriteDepth(spriteIndex,pDepth);
	depth = pDepth;
}

//sets objects mass
void CreationObject::setMass(float mass)
{
	objectMass = mass;
}


//-----------------------------------Accessor functions------------------------------------

// returns the sprite's index.
int CreationObject::getSpriteIndex() 
{
   return spriteIndex;
}

// returns the name of the image file used to create this sprite.
char* CreationObject::getImageFile() 
{
   return imageFile;
}

// returns the sprite's X coordinate.            
float CreationObject::getX() 
{
	return agk::GetSpriteX(spriteIndex);
}

// returns the sprite's Y coordinate.
float CreationObject::getY() 
{
   return agk::GetSpriteY(spriteIndex);
}

//returns if the sprite exists or not
bool CreationObject::getObjectExist()
{
	return agk::GetSpriteExists(spriteIndex);
}

//returns the objects mass
float CreationObject::getMass() 
{
	return objectMass;
}

// The Sprite class destructor deletes the sprite from memory.
void CreationObject::deleteSprite()
{
   agk::DeleteSprite(spriteIndex);
}

//returns depth of sprite
int CreationObject::getDepth()
{
	return	agk::GetSpriteDepth(spriteIndex);
}
