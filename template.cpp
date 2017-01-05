/*
Name: Addison Dalton
Date: 4/30/2014
MOD AND SIM. FINAL PROJECT

Simulation of a solar system. Program begins with about 6 planets orbiting the sun. The user can drag planets, launch planets (change their velocity), and target planets to displays their
mass, velocity and acceleration in x and y. The user can delete planets, edit their mass, reset the simulation, and summon a death star for fun. The death star is moved via the arrow keys
and can destroy targeted planets by pressing spacebar.
		

*/

// Includes, namespace and prototypes
#include "template.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include "CelestialObject.h"
#include <string>
#include "creationObject.h"

using namespace std;
using namespace AGK;
app App;

//----------------------------------GLOBAL VARIABLE DECLARATIONS-------------------------------------------

//VARIABLE FOR SCREEN DIMENSIONS
const int SCREEN_WIDTH = 6600;
const int SCREEN_HEIGHT = 3500;

//VARIABLES FOR MASS OF CREATED OBJECTS
const float createSunMass = 350000;
const float createLargeObjectMass = 420;
const float createMedObjectMass = 3;
const float createSmallObjectMass = .8;
const float createMoonMass = .0005;
CreationObject creationObjectArray[10];

float const dt = .1; //timestep
float G = .01; //universal gravity constant
float deathStarMove = 2; //the amount the deathStar will move with each arrow key press

//used to hold the x and y location of the mouse when a rightClick is made
float rightPressX = 0;
float rightPressY = 0;

bool deathStarExists = false;
bool infoTextEmpty = true; //keys the simulations from constantly "reprinting" planet's info when there's nothing to display
bool laserTimerRunning = false; //used with the timer that controls how long the laser remains on screen
bool laserFiring = false;// same as above
float laserTime = 0;
bool planetDestroyed = false; //used with timer that controls how long the particles for destroyed planets are emmitted
bool planetDestroyedTimerRunning = false;//same as above
float planetDestroyedTime =0;
bool gameRunning = false;
bool draggingPlanet = false;
bool celestialArrayFull = false;

int arrayPlaceHolder = 0; //holds the current place in an array,
const float laserHeight = 100; //have to make is constant, otherwise as the laser is scaled in the program, it's height changes

const int maxObjects = 50; //if I do add the ability for the use to add other objects, then this controls the max that can be added.
int spriteIndexCheck = 0; //used similairly to arrayPlaceHolder
//this array is used with the CelestialArray that holds the actual celestialObjects. 
//this array has the same place values as CelestialArray. It works in that if a place in CelestialArray currently has 
//an object, then celestialArrayCheck will hold a 1 in that place, if a place in CelestialArray holds no  object then
//celestialArrayCheck will hold a 0.
//it will keep track of open spots in celestialArray in case an object is deleted, or if all spots are full to alert the
//users that the maxObjects has been reached.
int celestialArrayCheck[maxObjects];

//----------------------------SPRITE VARIABLES---------------------------------
const int cloneSprite = 300; //used with target
const int deathStarIndex = 301;
const int laserIndex = 303;
const int MENU_INDEX = 304;
const int startScreenIndex = 305;
const int createSun = 401;
const int createLargeObject= 402;
const int createMedObject = 403;
const int createSmallObject = 404;
const int createMoon = 405;

//following strings hold the locations of the creation sprites


//-----------------------------TEXT VARIABLES-------------------------------------
//(LBL is label for the info being displayed Example LBL = "Velocity: ", while TXT is the actual planet's velocity number
const int vxLBL = 1; const int vxTXT = 11;
const int vyLBL = 2; const int vyTXT = 22;
const int axLBL = 3; const int axTXT = 33;
const int ayLBL = 4; const int ayTXT = 44;
const int massLBL = 5; const int massTXT = 55;
const int targetLBL = 6;

//these two are used to display the new velocity that will be given to a planet. They are shown while the planet is in "launch" mode
const int newVXTXT = 101; const int newVYTXT = 102; 

//following text variables dealing with new planet creation
const int createObjectsTitle = 201;
//----------------------------SOUND VARIABLES---------------------------------------
const int laserSound =1;

//---------------------------PARTICLES VARIABLES------------------------------------
const int destroyedParticles = 1;
//-----------------------BUTTON AND EDITBOX VARIABLES-----------------------------
//BUTTONS
const int massBTN = 1;
const int deleteBTN = 2;
const int resetBTN=3;
const int deathStarBTN =4;

//EDITBOX
const int massEdit = 1;

//------------------INITIAL CREATION OF CELESTIAL OBJECTS---------------------------------
CelestialObject celestialArray[maxObjects];
//object parameters are in this other (SpriteIndex, image File, X location, Y locations, Velocity X, Velocity Y, accel X, accel Y, mass) 
CelestialObject earth(3,"media/earth.png", 3000, 1650, 0,50,0,0,1);
CelestialObject sun(2,"media/sun.png",SCREEN_WIDTH/2-800,SCREEN_HEIGHT/2,0,0,0,0,330000);
CelestialObject mars(4,"media/mars.png", 3500, 1800, 0,-59,0,0,.107);
CelestialObject jupiter(5,"media/jupiter.png",2000,4000,-60,0,0,0,317.1);
CelestialObject saturn(6,"media/saturn.png",2000,500,70,-13,0,0,95.7);
CelestialObject moon(7,"media/moon.png",2300, 1700, 0, 70,0,0,.5);
CelestialObject venus( 8, "media/venus.png", 1700, 1900, 0,-50,0,0,.9);

//function that will place the sprites on screen that the user can drag to create new objects
void createAddObjects()
{
	//------------INITIALLY DECLARE CREATIONOBJECTS AND PLACE THEM IN ARRAY--------
	CreationObject star(createSun,"media/createSun.png",6300,2350,9,3,3,createSunMass);
	CreationObject largeObject(createLargeObject,"media/createLargeObject.png",7180,2460,9,3,3,createLargeObjectMass);
	CreationObject medObject(createMedObject,"media/createMedObject.png",6460,3100,9,3,3,createMedObjectMass);
	CreationObject smallObject(createSmallObject,"media/createSmallObject.png",6940,3120,9,3,3,createSmallObjectMass);
	CreationObject moon(createMoon,"media/createMoon.png",7300,3125,9,3,3,createMoonMass);
	
	//places them in array
	creationObjectArray[2] = star;
	creationObjectArray[3] = largeObject;
	creationObjectArray[4] = medObject;
	creationObjectArray[5] = smallObject;
	creationObjectArray[6] = moon;
	//------------------------CREATE SPRITES------------------------
	for(int k = 1; k<=7;k++)
	{
		creationObjectArray[k].createSprite();
	}

	//----------------------------TEXT--------------------------------
	agk::CreateText(createObjectsTitle, "Drag New Celestial Bodies");
	agk::SetTextPosition(createObjectsTitle, 6200,2200);
	agk::SetTextSize(createObjectsTitle, 95);
	agk::SetTextDepth(createObjectsTitle,9);
}

//function that will actually add new celestial objects to the game
void addObjects()
{

	//cycles through add object sprites
	if(agk::GetRawMouseLeftState()==1)
	{
		//get mouse location
		float mouseX = agk::ScreenToWorldX(agk::GetPointerX());
		float mouseY = agk::ScreenToWorldY(agk::GetPointerY());

		for(int k = 1; k<=7; k++)
		{
			if(agk::GetSpriteHitTest(creationObjectArray[k].getSpriteIndex(),mouseX,mouseY)==1 && draggingPlanet ==false) //checks if mouse is over any of the creation Sprites
			{
				for(int j = 1; j<=maxObjects; j++) //cycles through celestialArrayCheck for open spots in celestialArray
				{
					if(celestialArrayCheck[j]==0)
					{
						draggingPlanet = true; //sets dragging to true, so you don't continually make planets
						celestialArrayFull = false; //celestialArray isn't full yet.
						celestialArrayCheck[j] =1; //sets this place to 1, saying an object now exist there
						CelestialObject newCelestialObject(j+1,creationObjectArray[k].getImageFile(), mouseX-10,mouseY-10,0,0,0,0,creationObjectArray[k].getMass()); //creates new celestial object
						celestialArray[j] = newCelestialObject; //places it in array
						celestialArray[j].createSprite(); //places on screen
						break;
					}
				}
				break;
			}
		}
	}
}

 //function that checks if planet has been clicked for dragging. Also controls new velocity given to planets
void dragPlanet(CelestialObject& object)
{
	//gets the initial location of where the user clicked the mouse
	float mouseX = agk::ScreenToWorldX(agk::GetPointerX()); 
	float mouseY = agk::ScreenToWorldY(agk::GetPointerY());

//-------------------------CODE FOR DRAGGING OBJECT--------------------------

	//checks if left click is currently down
	if(agk::GetRawMouseLeftState()==1)
	{
		if(agk::GetSpriteHitTest(object.getSpriteIndex(), mouseX, mouseY)==1)// checks if an object has been clicked
		{
			object.setleftClick(true); //tells object it has been left clicked
			object.setTargeted(true);  //tells object it has been targeted
			draggingPlanet = true;
		}
	}
	else //if the left mouse click isn't down, then
	{
		object.setleftClick(false); //object not left Clicked
		draggingPlanet = false;
	}

	//if an object has been left clicked and has not yet been right clicked, then drag it
	if(object.getleftClick()==true && object.getRightClick()==false)
	{ 

		//updates objects position to initial mouses x and y
		object.setPosition(mouseX-object.getWidth()/2, mouseY-object.getHeight()/2);
		//sets their velociies to 0
		object.setVX(0); object.setVY(0);

		//checks if a right click has been made
		if(agk::GetRawMouseRightPressed()==1)
		{
			object.setRightClick(true); //object has been righClicked

			//position holders of where the right click was made; used to calculate a new velocity
			rightPressX = agk::ScreenToWorldX(agk::GetPointerX()); 
			rightPressY = agk::ScreenToWorldY(agk::GetPointerY());
		}
	}

//--------------------------CODE FOR NEW VELOCITY IF RIGHT CLICK HAS BEEN MADE----------------------------------

	//check if the left mouse button has been released and a right click was made then
	if(agk::GetRawMouseLeftState() !=1 && object.getRightClick()==true)
	{
		//get positions of mouse x and y location when the left mouse click was released
		float leftReleaseX = agk::ScreenToWorldX(agk::GetPointerX()); 
		float leftReleaseY = agk::ScreenToWorldY(agk::GetPointerY()); 

		//give the object it's new velocity. I divide by 4 as it gives a good velocity to mouse distance ratio. (no dividing causes a small distance to give a huge velocity)
		object.setVX(-(leftReleaseX - rightPressX)/4);
		object.setVY(-(leftReleaseY - rightPressY)/4);
		object.setRightClick(false);

		//deletes the text for new velocity x and y
		agk::DeleteText(newVXTXT);
		agk::DeleteText(newVYTXT);
	}
	//this will display the new velocity that a planet will be given once you release left click
	else if(agk::GetRawMouseLeftState() ==1 && object.getRightClick()==true)
	{
		//gets the velocity that would be given to the object if it was released at this point. Divide by 4 for same reason as above.
		float newVX = -(mouseX - rightPressX)/4;
		float newVY = -(mouseY - rightPressY)/4;

		//creates, places, and updates the new VX that will be given to an object
		agk::CreateText(newVXTXT, agk::Str(newVX));
		agk::SetTextString(newVXTXT, agk::Str(newVX));
		agk::SetTextSize(newVXTXT,80);
		agk::SetTextPosition(newVXTXT,object.getX()-25, object.getY()-130);

		//same as above, but for VY
		agk::CreateText(newVYTXT, agk::Str(newVY));
		agk::SetTextString(newVYTXT, agk::Str(newVY));
		agk::SetTextSize(newVYTXT, 80);
		agk::SetTextPosition(newVYTXT, object.getX()-25, object.getY()-65);
	}
}

//checks if a planet as been right clicked (targeted) used to display the planet's info
void targetPlanet()
{	
	if(agk::GetRawMouseLeftPressed()==1 || agk::GetRawMouseRightPressed()==1) //looks for either a left or right click press
	{
		for(int k = 1; k<=maxObjects; k++) //cycles through all the objects
		{
			//checks for hit between object and mouse location
			if(agk::GetSpriteHitTest(celestialArray[k].getSpriteIndex(), agk::ScreenToWorldX(agk::GetPointerX()), agk::ScreenToWorldY(agk::GetPointerY()))==1) 
			{
				celestialArray[k].setTargeted(true);
			}
			else
			{
				celestialArray[k].setTargeted(false);
			}
		}
	}
}

//function that will intially create and place the text that shows planet's info
void initialDisplayInfo()
{
	//first, create all the texts
	agk::CreateText(vxLBL, "Velocity X: "); agk::CreateText(vxTXT, " "); //vx
	agk::CreateText(vyLBL, "Velocity Y: "); agk::CreateText(vyTXT, " "); //vy
	agk::CreateText(axLBL, "Acceleration X: "); agk::CreateText(axTXT, " "); //ax
	agk::CreateText(ayLBL, "Acceleration Y: "); agk::CreateText(ayTXT, " "); //ay
	agk::CreateText(massLBL, "Mass: "); agk::CreateText(massTXT, " "); //mass
	agk::CreateText(targetLBL,"Target:"); //target

	//second, set the position of all texts
	agk::SetTextPosition(vxLBL, 6300, 250); agk::SetTextPosition(vxTXT, 6900, 250); //vx
	agk::SetTextPosition(vyLBL, 6300, 350); agk::SetTextPosition(vyTXT, 6900, 350); //vy
	agk::SetTextPosition(axLBL, 6300, 550); agk::SetTextPosition(axTXT, 7120, 550); //ax
	agk::SetTextPosition(ayLBL, 6300, 650); agk::SetTextPosition(ayTXT, 7120, 650); //ay
	agk::SetTextPosition(massLBL, 6300, 850); agk::SetTextPosition(massTXT, 6590, 850); //mass
	agk::SetTextPosition(targetLBL, 6300, -320); //target

	//third, set the size of all texts
	agk::SetTextSize(vxLBL, 85); agk::SetTextSize(vxTXT, 80); //vx
	agk::SetTextSize(vyLBL, 85); agk::SetTextSize(vyTXT, 80); //vy
	agk::SetTextSize(axLBL, 85); agk::SetTextSize(axTXT, 80); //ax
	agk::SetTextSize(ayLBL, 85); agk::SetTextSize(ayTXT, 80); //ay
	agk::SetTextSize(massLBL, 85); agk::SetTextSize(massTXT, 80); //mass
	agk::SetTextSize(targetLBL, 100); //target

	//fourth, set depth of all text
	agk::SetTextDepth(vxLBL, 9); agk::SetTextDepth(vxTXT, 9); //vx
	agk::SetTextDepth(vyLBL, 9); agk::SetTextDepth(vyTXT, 9); //vy
	agk::SetTextDepth(axLBL, 9); agk::SetTextDepth(axTXT, 9); //ax
	agk::SetTextDepth(ayLBL, 9); agk::SetTextDepth(ayTXT, 9); //ay
	agk::SetTextDepth(massLBL, 9); agk::SetTextDepth(massTXT, 9); //mass
	agk::SetTextDepth(targetLBL, 9); //target
}

//function that displays the info of the targeted planet
void displayInfo()
{

	for(int k = 1; k<=maxObjects; k++) //cycles through the planets
	{
		if(celestialArray[k].getTargeted()==true) //if a planet has been target, update the info
		{
			infoTextEmpty=false;
			agk::SetTextString(vxTXT, agk::Str(celestialArray[k].getVX())); //vx
			agk::SetTextString(vyTXT, agk::Str(celestialArray[k].getVY())); //vy
			agk::SetTextString(axTXT, agk::Str(celestialArray[k].getAX())); //ax
			agk::SetTextString(ayTXT, agk::Str(celestialArray[k].getAY())); //ay
			agk::SetTextString(massTXT, agk::Str(celestialArray[k].getMass())); //mass

			//if a new object has been selected, this deletes the old cloneSprite target pic.
			if(celestialArray[k].getSpriteIndex() != spriteIndexCheck) //if the current targeted object does not equal the same object as spriteIndex Check
			{
				agk::DeleteSprite(cloneSprite); //delete old target (cloned sprite)
				spriteIndexCheck = celestialArray[k].getSpriteIndex(); //since spriteIndex is intially 0 and none of my spriteIndexs are 0, then this will run when first called
																		// allows me to no have to initially set a targeted sprite to spiteIndexCheck
			}
			
			//if the clone sprite doesn't exist create it.
			if(agk::GetSpriteExists(cloneSprite)==0)                        //sprite
			{
			agk::CreateSprite(cloneSprite, celestialArray[k].getImageFile().c_str()); //I did createSprite as opposed to cloneSprite because the latter was causing bugs
		    agk::SetSpriteScaleByOffset(cloneSprite,3,3); //triples size of sprite. Scaled from the center of the sprite.
			agk::SetSpritePosition(cloneSprite, 6900, -350);
			agk::SetSpriteDepth(cloneSprite, 9);
			}
			break; //break out of loop
		}
		else if(infoTextEmpty==false) //if none of the planets are targeted, reset the info being displays back to empty sapce
		{
			infoTextEmpty=true;
			agk::SetTextString(vxTXT, " ");
			agk::SetTextString(vyTXT, " ");
			agk::SetTextString(axTXT, " ");
			agk::SetTextString(ayTXT, " ");
			agk::SetTextString(massTXT, " ");
			agk::DeleteSprite(cloneSprite);
		}
	}
}

//adds the buttons and editBoxs on screen
void addInputs()
{
	//-------------------------------BUTTONS--------------------------------
	//MASS 
	agk::AddVirtualButton(massBTN, 5700, 1500,300);
	agk::SetVirtualButtonText(massBTN, "Edit\nMass");
	agk::SetVirtualButtonVisible(massBTN,0);
	
	//DELETE
	agk::AddVirtualButton(deleteBTN, 5700, 1850,300);
	agk::SetVirtualButtonText(deleteBTN,"Delete");
	agk::SetVirtualButtonVisible(deleteBTN,0);
	//RESET
	agk::AddVirtualButton(resetBTN, 6050,1850, 300);
	agk::SetVirtualButtonText(resetBTN, "Reset");
	agk::SetVirtualButtonVisible(resetBTN,0);
	//DEATH STAR
	agk::AddVirtualButton(deathStarBTN,6400,1850,300);
	agk::SetVirtualButtonText(deathStarBTN,"Death\nStar");
	agk::SetVirtualButtonVisible(deathStarBTN,0);
	//------------------------------EDITBOXS--------------------------------
	agk::CreateEditBox(massEdit);
	agk::SetEditBoxPosition(massEdit,6800, 1315);
	agk::SetEditBoxSize(massEdit,300,150);
	agk::SetEditBoxTextSize(massEdit, 80);
	agk::SetEditBoxBackgroundColor(massEdit,90,90,90,255);
	agk::SetEditBoxDepth(massEdit,9);


}

//controls massBTN press events
void massBTNPress()
{
	for(int k = 1; k<=maxObjects; k++) //cycles through the planets
	{
		if(celestialArray[k].getTargeted()==true) //if a planet has been target
		{
			float newMass = atof(agk::GetEditBoxText(massEdit)); //gets the mass entered into the editBox
			
			//keeps 0 and negative numbers from occuring
			if(newMass <=0)
			{
				newMass =.00000001;
			}
			celestialArray[k].setMass(newMass); //updates object's mass
		}
	}
}

//controls deleteBTN press events
void deleteBTNPress()
{
	for(int k = 1; k<=maxObjects; k++) //cycles through the planets
	{
		if(celestialArray[k].getTargeted()==true) //if a planet has been targeted
		{
			celestialArray[k].deleteSprite();
			celestialArray[k].nullObject(); //this sets the planets velocites, acceleration, mass, ect to 0. 
			celestialArrayCheck[k] =0; //sets it's spot in ArrayCheck to 0. 

		}
	}
}

//controls resetBTN press events
void resetBTNPress()
{
	//cycles through array of objects and arrayChecker. 
	for(int k=1; k<=maxObjects; k++)
	{
		celestialArray[k].deleteSprite(); //deletes sprites
		celestialArray[k].nullObject(); //nulls all it's info
		celestialArrayCheck[k] = 0; //ArrayCheck is empty
	}
	infoTextEmpty = true; //resets infoTextEmpty to true
	laserFiring = false;//resets laserFiring to false
	laserTimerRunning = false;//resets laserTimerRunning to false
	planetDestroyed = false;//resets planetDestroyed to false
	planetDestroyedTimerRunning = false;//resets planetDestroyedTimerRunning to false
	draggingPlanet = false; //resets dragging planet to false
	//for death star
	agk::DeleteSprite(deathStarIndex);
	deathStarExists = false;
	agk::CreateSprite(deathStarIndex, "media/deathStar.png");
	agk::SetSpriteScale(deathStarIndex,1.2,1.2);
	agk::SetSpriteVisible(deathStarIndex,0);
	//for laser
	agk::DeleteSprite(laserIndex);

	//-------------reset all initial values-------------
	CelestialObject earth(3,"media/earth.png", 3000, 1650, 0,50,0,0,1);
	CelestialObject sun(2,"media/sun.png",SCREEN_WIDTH/2-800,SCREEN_HEIGHT/2,0,0,0,0,330000);
	CelestialObject mars(4,"media/mars.png", 3500, 1800, 0,-59,0,0,.107);
	CelestialObject jupiter(5,"media/jupiter.png",2000,4000,-60,0,0,0,317.1);
	CelestialObject saturn(6,"media/saturn.png",2000,500,70,-13,0,0,95.7);
	CelestialObject moon(7,"media/moon.png",2300, 1570, -30, 120,0,0,.00005);
	CelestialObject venus( 8, "media/venus.png", 1700, 1900, 0,-50,0,0,.9);

	//-----------replace them in object array--------------
	celestialArray[1] = sun; celestialArray[2] = earth; celestialArray[3] = mars; 
	celestialArray[4] = jupiter; celestialArray[5] = saturn; celestialArray[6] = moon;
	celestialArray[7] = venus;

	//----------places all sprites on screen again-----------
	for(int j = 1; j<maxObjects; j++)
	{
		celestialArray[j].createSprite();
		agk::SetSpriteScaleByOffset(celestialArray[j].getSpriteIndex(),1.8,1.8);
	}

	//--------------refills ArrayCheck to initial values--------------
	for(int k = 1;k<=7;k++)
	{
		celestialArrayCheck[k]=1;
	}

	//--------------resets info be displyed to empty values-------------
	agk::SetTextString(vxTXT, " ");
	agk::SetTextString(vyTXT, " ");
	agk::SetTextString(axTXT, " ");
	agk::SetTextString(ayTXT, " ");
	agk::SetTextString(massTXT, " ");
	agk::DeleteSprite(cloneSprite);
}

//controls deathStarBTN press events
void deathStarBTNPress()
{
	agk::SetSpritePosition(deathStarIndex,5900,3800); 
	agk::SetSpriteVisible(deathStarIndex,1);
	deathStarExists = true;
}

//function that checks if any of the buttons have been pressed
void checkAllButtons()
{
		//checks for mass button press
	if(agk::GetVirtualButtonPressed(massBTN)==1)
	{
		massBTNPress();
	}
	
	//checks for delete button press
	if(agk::GetVirtualButtonPressed(deleteBTN)==1)
	{
		deleteBTNPress();
	}
	
	//checks for reset button press
	if(agk::GetVirtualButtonPressed(resetBTN)==1)
	{
		resetBTNPress();
	}

	//checks for death star button press
	if(agk::GetVirtualButtonPressed(deathStarBTN)==1)
	{
		deathStarBTNPress();
	}
}

//controls deathStar movements
void deathStarMoving()
{
	//------------CODE FOR MOVEMENT------------------
	//gets current location of death star
	float currentX = agk::GetSpriteX(deathStarIndex);
	float currentY = agk::GetSpriteY(deathStarIndex);
	if(agk::GetRawKeyState(37)==1) //left arrow 
	{
		agk::SetSpriteX(deathStarIndex,-deathStarMove + currentX);
	}
	if(agk::GetRawKeyState(38)==1)//up arrow
	{
		agk::SetSpriteY(deathStarIndex, -deathStarMove + currentY);
	}
	if(agk::GetRawKeyState(39)==1)//right arrow
	{
		agk::SetSpriteX(deathStarIndex, deathStarMove + currentX);
	}
	if(agk::GetRawKeyState(40)==1)//down arrow
	{
		agk::SetSpriteY(deathStarIndex, deathStarMove + currentY);
	}
}

//controls deathStar laser
void deathStarLaser()
{
	for(int k =1; k<=maxObjects; k++) //cycles through objects
	{
		if(celestialArray[k].getTargeted()==true) //if an object is targeted
		{
			laserFiring = true;

			//----CALCULATIONS TO DETERMINE ANGLE OF LASER TOWARDS TARGET PLANET
			float deltaX = agk::GetSpriteX(deathStarIndex)-celestialArray[k].getX(); //distance difference in x between deathStar and target object
			float deltaY = agk::GetSpriteY(deathStarIndex)-celestialArray[k].getY(); //same as above, but in y
			float angleInDegrees = atan2(deltaY,deltaX)*180/PI; //arctan on distance differences, then convert to degrees

			//----CALCULATIONS TO DETERMINE HOW MUCH TO SCALE LASER
			float distR = sqrt(pow(deltaX,2)+pow(deltaY,2)); //vector distance  between death star and targeted object
			float spriteScaleValue = distR/laserHeight; //takes that total distance and divides it by the laser's default height (height because only laser's y is scaled)

			agk::CreateSprite(laserIndex, "media/laser.png"); //create the laser
			agk::PlaySound(laserSound); //play the sound

			//sets lasers position on deathStar, had to play with offset numbers to get something that looked somewhat right most of the time since the death Star can move (changes angle of the laser)
			agk::SetSpritePosition(laserIndex,agk::GetSpriteX(deathStarIndex)+50, agk::GetSpriteY(deathStarIndex)+agk::GetSpriteHeight(laserIndex)-40);

			agk::SetSpriteOffset(laserIndex,0,0);// changes the sprites "center or axis" to it's left corner
			agk::SetSpriteAngle(laserIndex, angleInDegrees-270); //angles the sprite, -270 because that's what worked
			agk::SetSpriteScale(laserIndex, 1, spriteScaleValue); //scales sprite (before it would scale from center, which caused both ends of laser to change, thus why I changed the offset)
			arrayPlaceHolder=k; //holds current place in array
			agk::CreateParticles(destroyedParticles,celestialArray[k].getX(), celestialArray[k].getY()); //creates particles where the targeted planet is
			agk::SetParticlesVelocityRange(destroyedParticles,.2,5); //gives a range at which the particles escape from the emitter
			agk::SetParticlesFrequency(destroyedParticles,100); //how many particles are created each second
			agk::SetParticlesStartZone(destroyedParticles,-50,-50,50,50); //gives a range around the emitter that particles can be created
			agk::SetParticlesSize(destroyedParticles,2); //size of particles
			agk::SetParticlesLife(destroyedParticles,1); //how long each particle shows on screen
			agk::SetParticlesMax(destroyedParticles,100); //max number of particles that the emitter can create.
			planetDestroyed = true;
			break; //once a target planet has been found, there is no reason to continue searching, breaks out of loop.
		}
	}
}

//function that controls everything dealing with the deathStar, include 2 previous functions
void deathStarCommand()
{
	//if death star exists, then move it
	if(deathStarExists ==true)
	{
		deathStarMoving();
	}

	//if death star exist, and spacebar is press, the fire laser at target(if one exists)
	if(deathStarExists ==true && agk::GetRawKeyPressed(32))
	{
		deathStarLaser();
	}
	
	if(planetDestroyed == true && planetDestroyedTimerRunning ==false)
	{
		planetDestroyedTime = agk::Timer()+1.5;
		planetDestroyedTimerRunning =true;
	}
	
	if(planetDestroyed == true && agk::Timer()>planetDestroyedTime)
	{
		agk::DeleteParticles(1);
		planetDestroyed = false;
		planetDestroyedTimerRunning = false;
	}
	
	//if the laser has been fired and the timer isn't running, then start it
	if(laserFiring==true && laserTimerRunning==false)
	{
		laserTime = agk::Timer()+.3; //set initial time to .3 of second ahead of current timer
		laserTimerRunning=true; //says timer is running
	}

	//if laser is firing and game time becomes greater then our timer, then delete planet and laser
	//basically allows the laser to exist on screen for a third of a second. 
	if(laserFiring == true && agk::Timer()>laserTime)
	{
		celestialArray[arrayPlaceHolder].deleteSprite();
		celestialArray[arrayPlaceHolder].nullObject();
		celestialArrayCheck[arrayPlaceHolder]=0;
		agk::DeleteSprite(laserIndex);
		laserFiring = false;
		laserTimerRunning=false;
	}
}

//calculates force between two objects in X 
float forceXFunc(CelestialObject object1, CelestialObject object2)
{
	float distX = object2.getX() - object1.getX();   //difference in x distance between to objects
	float distY = object2.getY() - object1.getY();   //same as above, but in y
	float R = sqrt((distX*distX) + (distY*distY));  //vector distance
	float forceX = (G*distX*(object1.getMass()*object2.getMass()))/(R*R); //formula to calculate force
	return forceX;
}

//calculates force between two objects in Y
float forceYFunc(CelestialObject object1, CelestialObject object2) //see forceXFunc
{
	float distX = object2.getX() - object1.getX();   
	float distY = object2.getY() - object1.getY();
	float R = sqrt((distX*distX) + (distY*distY));
	float forceY = (G*distY*(object1.getMass()*object2.getMass()))/(R*R);
	return forceY;
}

//checks for collision between two objects
void collisionDetection(CelestialObject& object1, CelestialObject& object2)
{
	if(agk::GetSpriteCollision(object1.getSpriteIndex(),object2.getSpriteIndex())) //checks for collision
	{
       if(object1.getMass() <= object2.getMass()) //if the first object has less mass
	   {
		   //then the second objects takes on the first object's mass
		   object2.setMass(object2.getMass()+object1.getMass());
		   object1.deleteSprite(); //first object sprite deleted
		   object1.nullObject(); //first object values nulled
		   
	   }
	   else //same as above but reversed. 
	   {
		   object1.setMass(object1.getMass()+object2.getMass()/2);
		   object2.deleteSprite();
		   object2.nullObject();
	   }
	}
}

//main function that updates the position of an object on screen	
//PLEASE FOR THE LOVE OF GOD PASS THIS BY REFERENCE OR YOU WILL BE STUCK WITH A PROBLEM FOR TWO WEEKS
 void updatePosition(CelestialObject& object, float forceX, float forceY ) 
 {

	 //preset variables
	 float X = object.getX();
	 float Y = object.getY();
	 float VX = object.getVX();
	 float VY = object.getVY();
	
	//-----------------ACCEL CALCULATIONS--------------------------
	float AXCalc = forceX/object.getMass();
	float AYCalc = forceY/object.getMass();

	//-----------------POSITION CALCULATIONS-----------------------
	float AX = AXCalc;
	float AY = AYCalc;
	VX = VX + AX*dt; //new velocity X
	VY = VY + AY*dt;  //Y

	//updates AX and AY for each planet
	object.setAX(AX*dt); object.setAY(AY+dt);

	//this keeps the object from going towards a larger object while a new velocity with right click is being made
	if(object.getRightClick()==false)
	{
	object.setV(VX, VY);
	}
	//updates the positions
	X = X + VX*dt; 
	Y = Y + VY*dt; 
	object.setPosition(X, Y);
 }



// -------------------------------Begin app, called once at the start------------------------
void app::Begin( void )
{
	//defines the initial plantery array
	celestialArray[1] = sun; celestialArray[2] = earth; celestialArray[3] = mars; 
	celestialArray[4] = jupiter; celestialArray[5] = saturn; celestialArray[6] = moon;
	celestialArray[7] = venus;
	
	//initializes the checker array according to how many objects are initially created
	for(int k = 1;k<=7;k++)
	{
		celestialArrayCheck[k]=1;
	}

	//-----------------------------sets various display setting------------------------------------
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	agk::SetViewZoomMode(1); //places the zoom on the center of screen
	agk::SetViewZoom(.75); //Didn't like the initial scale, so lowered it slightly
	agk::CreateSprite(MENU_INDEX, "media/menu.jpg");
	agk::CreateSprite(deathStarIndex, "media/deathStar.png");
	agk::CreateSprite(startScreenIndex, "media/startScreen.jpg");
	agk::SetSpritePosition(startScreenIndex, -1100,-590);
	agk::SetSpriteDepth(startScreenIndex, 5);
	agk::SetSpriteScale(deathStarIndex,1.2,1.2);
	agk::SetSpriteVisible(deathStarIndex,0);
	agk::SetSpriteDepth(MENU_INDEX, 9);
	agk::SetSpritePosition(MENU_INDEX, SCREEN_WIDTH-450,-600);
	
	
	//loop to create all the celestialobjects
	for(int start = 1; start<maxObjects; start++)
	{
		celestialArray[start].createSprite();
		agk::SetSpriteScaleByOffset(celestialArray[start].getSpriteIndex(),1.8,1.8);
	}
	//loads sound
	agk::LoadSound(laserSound,"media/laserSound.wav");

	//function call to create and place all text that will display info. 
	initialDisplayInfo();

	//function call to add all buttons to screen
	addInputs();

	//function that adds createPlanet Sprites
	createAddObjects();
}

// ------------------------------------------Main loop--------------------------------
void app::Loop ( void )
{	
	//check for spacebar press to start the game
	if(agk::GetRawKeyPressed(32)==1)
	{
		gameRunning = true;
		agk::DeleteSprite(startScreenIndex);
		//makes all the  buttons visible
		agk::SetVirtualButtonVisible(massBTN,1);
		agk::SetVirtualButtonVisible(resetBTN,1);
		agk::SetVirtualButtonVisible(deleteBTN,1);
		agk::SetVirtualButtonVisible(deathStarBTN,1);
	}

	if(gameRunning ==true)
	{
	targetPlanet(); //function call to check if a planet has been target
	addObjects();
	//cycles through each planet checking for drags
	for(int k = 1; k <= maxObjects; k++)
	{
		dragPlanet(celestialArray[k]);
	}

	displayInfo(); //shows info of targeted planet on the side screen

	checkAllButtons(); //calls function that checks all buttons for press events
	
	deathStarCommand(); //calls function that controls everything dealing with the deathStar
//-----------------------------------------MAIN CODE THAT MOVES PLANETS------------------------------
	//nested for loop to calculate forces between all objects and update their positions
	for(int chkPlanet = 1; chkPlanet<=maxObjects; chkPlanet++)
	{
		float forceX = 0;
		float forceY = 0;
		if(celestialArray[chkPlanet].getObjectExist())//makes sure the object exists before running calculations
		{
			for(int cyclePlanet = 1; cyclePlanet<=maxObjects; cyclePlanet++)
			{
				if(chkPlanet!=cyclePlanet && celestialArray[cyclePlanet].getObjectExist()) //so the planet doesn't calculate itself and makes sure the planets being cycled through exist
				{
					//adds up the total net force in x and y of the planet being checked compared to the other planets
					forceX = forceX + forceXFunc(celestialArray[chkPlanet],celestialArray[cyclePlanet]);
					forceY = forceY + forceYFunc(celestialArray[chkPlanet],celestialArray[cyclePlanet]);
					collisionDetection(celestialArray[chkPlanet],celestialArray[cyclePlanet]); //checks for collisions
				}
			}
			updatePosition(celestialArray[chkPlanet],forceX, forceY); //calculates and updates position of the planet being checked
		}
	}
	
	}
	// Update the screen.
	agk::Sync();

}

// Called when the app ends
void app::End ( void )
{
}
