#include <Servo.h>

//declare objects and variables
Servo picMotor, mothMotor;

//set all pins for necessary connections -- update before running
int picPin = 2; //flips autographed picture
int pullPin = 4; //pulley controller
int mothPin = 7; //button to activate lamp

//var to check for user input
int val = 0;
int constant = 91;
int left = 100;
int right = 50;

int xPos = 40;
int xMin = 0;
int xMax = xPos;
int xCorrect = 200;
int xOffset = 20;
bool crossed = false;
int frame = 40;

int distToCarina = 20;

//var of mothman's current state
//0 = resting, 1 = flying, 2 = landing
int mothMan = 0;
int pic = 0;
int autograph = 180;

//minimum sound level required to trigger sound sensor
int minSound = 16;

//other vars to check for different states
bool flying = false;

void setup() {
  // put your setup code here, to run once:
  picMotor.attach(picPin); //pin attached to autograph motor
  mothMotor.attach(pullPin); //pin attached to mothman
  picMotor.write(pic);
  //set pin modes
  pinMode(mothPin, INPUT);
}

void loop() {
  //check and update state
  if(mothMan == 0)
  {
    //mothman is resting -- check for moth signal
    if(digitalRead(mothPin) == HIGH)
    {
      //moth signal activated -- he begins his flight
      mothMan = 1;
    }
    mothMotor.write(constant);
  }
  else if(mothMan == 1)
  {
    //mothman is flying -- check for shout
    while(xPos > xMin && mothMan != 2)
    {
      xPos = xPos - 1;
      mothMotor.write(left);
      delay(frame);

      if(digitalRead(mothPin) == HIGH)
      {
        //sound got his attention -- he begins to land
        mothMan = 2;
      }
    }
    while(xPos < xMax && mothMan != 2)
    {
      xPos = xPos + 1;
      mothMotor.write(right);
      delay(frame);

      if(digitalRead(mothPin) == HIGH)
      {
        //sound got his attention -- he begins to land
        mothMan = 2;
      }
    }
    if(mothMan != 2)
    {
      mothMan = 0;
    }
  }
  else if(mothMan == 2) //mothman MUST be landing
  {
    //mothman is landing
    for(int i = 0; i < distToCarina; i++)
    {
      mothMotor.write(left);
      delay(frame);
    }
    picMotor.write(autograph);
    mothMan = 3;
  }
  else //mothman must be done
  {
    mothMotor.write(constant);
  }
}