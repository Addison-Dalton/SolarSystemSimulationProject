#include "template.h"
#include <math.h>
#include <string>
#include "CelestialObject.h"
using namespace std;
using namespace AGK;



// This is the default constructor for the Sprite class.
// It sets index to 1 and imageFile to an empty string.
CelestialObject::CelestialObject()
{
   spriteIndex = 1;
   imageFile = "";
}

// This Sprite class constructor accepts as arguments
// the sprite index and the name of the image file,
// and initializes the member variables.
CelestialObject::CelestialObject(int index, string filename,float pX, float pY, float VX, float VY, float AX, float AY, float mass)
{
   spriteIndex = index;
   imageFile = filename;

   positionX = pX;
   positionY = pY;

   velocityX = VX;
   velocityY = VY;

   accelX = AX;
   accelY = AY;

   objectMass = mass;

   leftClick = false;
   rightClick= false;
   targeted = false;



}


// The Sprite::createSprite member function 
void CelestialObject::createSprite()
{
   // If the sprite does not already exist,
   //     then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
	  agk::SetSpritePosition(spriteIndex, positionX, positionY); //object position
   }
}
//---------------------------------constructors-----------------------------------------
void CelestialObject::createSprite(int index, string filename)
{
   // Set the member variables.
   spriteIndex = index;
   imageFile = filename;

   // If the sprite does not already exist,
   //   then create it.
   if (!agk::GetSpriteExists(spriteIndex))
   {
      agk::CreateSprite(spriteIndex, imageFile.c_str());
	  agk::SetSpritePosition(spriteIndex, positionX, positionY); //object position

   }
}

//sets all the information for object, includes it position, velocties, accel, and mass
void CelestialObject::intializeObject()
{
	//might not use

}

//-----------------------------------------Mutators-------------------------------------------
// sets the sprite's position.
void CelestialObject::setPosition(float x, float y)
{
   agk::SetSpritePosition(spriteIndex, x, y);
   positionX = x;
   positionY = y;
}

// sets the sprite's X coordinate.
void CelestialObject::setX(float x)
{
   agk::SetSpriteX(spriteIndex, x);
   positionX = x;
}

//sets size of sprite by a ratio
void CelestialObject::spriteSize(float pwidth, float pheight)
{
	agk::SetSpriteSize(spriteIndex,pwidth, pheight);
}
// sets the sprite's Y coordinate.
void CelestialObject::setY(float y)
{
   agk::SetSpriteY(spriteIndex, y);
   positionY = y;
}

//sets objects velocity
void CelestialObject::setV(float VX, float VY)
{
	velocityX = VX;
	velocityY = VY;
}
//sets objects x velocity
void CelestialObject::setVX(float VX)
{
	velocityX = VX;
}

//sets objects y velocity
void CelestialObject::setVY(float VY)
{
	velocityY = VY;
	agk::SetSpritePhysicsVelocity(spriteIndex,velocityX,velocityY);
}

//sets objects x accel
void CelestialObject::setAX(float AX)
{
	accelX = AX;
}

//sets objects y accel
void CelestialObject::setAY(float AY)
{
	accelY = AY;
}

//sets objects mass
void CelestialObject::setMass(float mass)
{
	objectMass = mass;
}

//sets it leftClick 
void CelestialObject::setleftClick(bool pleftClick)
{
	leftClick = pleftClick;
}

//rightClick
void CelestialObject::setRightClick(bool prightClick)
{
	rightClick = prightClick;
}

//targeted
void CelestialObject::setTargeted(bool ptargeted)
{
	targeted = ptargeted;
}


//-----------------------------------Accessor functions------------------------------------

// returns the sprite's index.
int CelestialObject::getSpriteIndex() 
{
   return spriteIndex;
}

// returns the name of the image file used to create this sprite.
string CelestialObject::getImageFile() 
{
   return imageFile;
}

// returns the sprite's X coordinate.            
float CelestialObject::getX() 
{
	return agk::GetSpriteX(spriteIndex);
}

// returns the sprite's Y coordinate.
float CelestialObject::getY() 
{
   return agk::GetSpriteY(spriteIndex);
}

//returns the objects xVelocity
float CelestialObject::getVX() 
{
	return velocityX;
}
//returns the objects yVelocity
float CelestialObject::getVY() 
{
	return velocityY;
}

//returns the objects xAccel
float CelestialObject::getAX() 
{
	return accelX;
}
//returns the objects yAccel
float CelestialObject::getAY() 
{
	return accelY;
}

//returns the objects mass
float CelestialObject::getMass() 
{
	return objectMass;
}

//returns the sprite's width coordinate.
float CelestialObject::getWidth() 
{
	return agk::GetSpriteWidth(spriteIndex);
}

//returns the sprite's height coordinate.
float CelestialObject::getHeight() 
{
	return agk::GetSpriteHeight(spriteIndex);
}

//returns if the sprite exists or not
bool CelestialObject::getObjectExist()
{
	return agk::GetSpriteExists(spriteIndex);
}

//returns bool if leftClicked or not
bool CelestialObject::getleftClick()
{
	return leftClick;
}

//returns bool if rightClicked or not
bool CelestialObject::getRightClick()
{
	return rightClick;
}

//returns bool if targeted
bool CelestialObject:: getTargeted()
{
	return targeted;
}
// The Sprite class destructor deletes the sprite from memory.
void CelestialObject::deleteSprite()
{
   agk::DeleteSprite(spriteIndex);
}

//nulls an object. Everything set to 0 or default bools. This way the object no longer interacts with others.
void CelestialObject::nullObject()
{
	spriteIndex = 0;
  
   positionX = 0;
   positionY = 0;

   velocityX = 0;
   velocityY = 0;

   accelX = 0;
   accelY = 0;

   objectMass = 0;
   leftClick = false;
   rightClick = false;
   targeted = false;
}
