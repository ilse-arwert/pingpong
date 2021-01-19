#include <Servo.h>      // include the Servo library
#include <math.h>


//the table:
//          N
//    ------.------ 
// W |      ,      | E
//   |             |
//    ------'------
//          S
// for the coordinates:
// the origin is below the flashlight, so angles (x0,y0) correspond to the XY coordinates (0,0)
// coordinates are in centimeters

Servo xServo;          // declare Servo object
Servo yServo;          // declare Servo object

const int x0 = 90;
const int y0 = 95;
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
  xServo.attach(4);    // attach object 'myServo' to pin 4
  yServo.attach(7);    // attach object 'myServo' to pin 7
  delay(10);
  xServo.write(x0);
  yServo.write(x0);
}


void loop() {
  //move to the four corners
  moveSlow(XYtoAngles(W, N));
  delay(1000);
  moveSlow(XYtoAngles(E, N));
  delay(1000);
  moveSlow(XYtoAngles(W, S));
  delay(1000);
  moveSlow(XYtoAngles(E, S));
  delay(1000);
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