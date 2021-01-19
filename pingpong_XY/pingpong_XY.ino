#include <Servo.h>      // include the Servo library
#include <math.h>


//the table:
//          A
//    ------.------ 
// B |      ,      | C
//   |             |
//    ------'------
//          D
// for the coordinates:
// x-Axis goes B->C
// y-Axis goes A->D
// the origin is below the flashlight, so angles (x0,y0) correspond to the XY coordinates (0,0)
// coordinates are in centimeters

Servo xServo;          // declare Servo object
Servo yServo;          // declare Servo object


//set up the photoresistors and the buzzer
const int upperSensorPin = 0;
int baseUpperLight;
int currentUpperLight;
const int middleSensorPin = 2;
int baseMiddleLight;
int currentMiddleLight;
const int lowerSensorPin = 4;
int baseLowerLight;
int currentLowerLight;
const int buzzer = 9;

//Variables
String currentPlayer = "right";

const int x0 = 81;
const int y0 = 90;
const double lampHeight = 139.0;
const int tableX = 168; //length of sides A and D
const int tableY = 90; //length of sides B and C

//locations of the sides in x or y coordinates, rounded to ints
const int N = 0.5 * tableY;
const int W = -0.5 * tableX;
const int E = 0.5 * tableX;
const int S = -0.5 * tableY;

struct tuple {
  double x;
  double y;
};

void setup() {
  // Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  xServo.attach(4);    // attach object 'myServo' to pin 4
  yServo.attach(7);    // attach object 'myServo' to pin 7

  //move light out of the way of the sensors
  xServo.write(20);
  yServo.write(20);
  delay(500);

  //read light levels
  baseMiddleLight = analogRead(middleSensorPin);
  baseUpperLight = analogRead(upperSensorPin);
  baseLowerLight = analogRead(lowerSensorPin);
  
  moveSlow(x0, y0);

  //signal that the game is about to start!
  tone(buzzer, 500);
  delay(1000);
  
  if(currentPlayer == "right") moveSlow(XYtoAngles(E, 0));
  else moveSlow(XYtoAngles(W, 0));
}

void loop() {
  unsigned long startMillis = millis();
  currentMiddleLight = analogRead(middleSensorPin);
  currentUpperLight = analogRead(upperSensorPin);
  currentLowerLight = analogRead(lowerSensorPin);

  //wait until the 3 sec deadline has passed or we register a reflected light
  while ((currentMiddleLight - baseMiddleLight) < 100 && (currentUpperLight - baseUpperLight) < 100 && (currentLowerLight - baseLowerLight) < 100 && (millis() - startMillis) < 3000) {
    currentMiddleLight = analogRead(middleSensorPin);
    currentUpperLight = analogRead(upperSensorPin);
    currentLowerLight = analogRead(lowerSensorPin);
  }
  
  if ((millis() - startMillis) > 3000) {
    //the player didn't reflect the light. sound the buzzer and stop the game.
    //to do: keep playing instead of stopping, maybe add a scorekeeping system?
    tone(buzzer, 1000, 1000);
    while(1); 
  }

  if ((currentMiddleLight - baseMiddleLight) > 100) {
    if (currentPlayer == "right") moveSlow(XYtoAngles(W, 0));
    else moveSlow(XYtoAngles(E, 0));
  }

  else if ((currentUpperLight - baseUpperLight) > 100) {
    if (currentPlayer == "right") moveSlow(XYtoAngles(W, N));
    else moveSlow(XYtoAngles(E, N));
  }

  else if ((currentLowerLight - baseLowerLight) > 100) {
    if (currentPlayer == "right") moveSlow(XYtoAngles(W, S));
    else moveSlow(XYtoAngles(E, S));
  }

  if (currentPlayer == "right") currentPlayer = "left";
  else currentPlayer = "right";
}

void moveSlow(int xAngle, int yAngle){
  int steps = 20;
  int dx = abs(xServo.read() - xAngle);
  int dy = abs(yServo.read() - yAngle);
  float stepY = dy/steps;

  //we can make this neater later by dumping it into a function takeStep(dx, dy, steps, counter)
  if(stepY<1) {
    int counter = 2;
    for(int i = 0; i < steps; i++) {
      counter = counter % 2;
      if(xServo.read() < xAngle) xServo.write(xServo.read()+floor(dx/steps));
      else xServo.write(xServo.read()-floor(dx/steps));
      if(yServo.read() < yAngle && counter == 0) yServo.write(yServo.read()+ceil(dy/steps));
      else if (counter == 0) yServo.write(yServo.read()-ceil(dy/steps));
      counter += 1;
      delay(30);
    }
  }

  else {
    for(int i = 0; i < steps; i++) {
      if(xServo.read() < xAngle) xServo.write(xServo.read()+floor(dx/steps));
      else xServo.write(xServo.read()-floor(dx/steps));
      if(yServo.read() < yAngle) yServo.write(yServo.read()+floor(dy/steps));
      else yServo.write(yServo.read()-floor(dy/steps));
      delay(30);
    }
  }

  xServo.write(xAngle);
  yServo.write(yAngle);
}

//void moveSlow(int xAngle, int yAngle){
//
//  while(xServo.read() != xAngle || yServo.read() != yAngle){
//    if(xServo.read() < xAngle){
//      xServo.write(xServo.read()+1);
//    }
//    if(xServo.read() > xAngle){
//      xServo.write(xServo.read()-1);
//    }
//    if(yServo.read() < yAngle){
//      yServo.write(yServo.read()+1);
//    }
//    if(yServo.read() > yAngle){
//      yServo.write(yServo.read()-1);
//    }
//    delay(30);
//  }
//}

void moveSlow(struct tuple ang){
  moveSlow(ang.x, ang.y);
}

double toDegrees(double radians) {
    return radians * (180.0 / PI);
}

double toRadians(double degrees) {
    return degrees * (PI / 180.0);
}

//i don't know which way around we're mounting this thing;
//i'm assuming that xAngle > x0 on the left/B side of the table
//and yAngle > y0 on the bottom/D side of the table
struct tuple XYtoAngles(int X, int Y) {
  struct tuple ang;
  double xAngleOffset = toDegrees(atan(X/lampHeight));
  ang.x = x0-xAngleOffset;
  double hypotenuse = sqrt(pow(X, 2) + pow(lampHeight, 2));
  double yAngleOffset = toDegrees(atan(Y/hypotenuse));
  ang.y = y0-yAngleOffset;
  return ang;
}
