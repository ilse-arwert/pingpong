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

int currentX = x0;
int currentY = y0;


void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  xServo.attach(4);    // attach object 'myServo' to pin 4
  yServo.attach(7);    // attach object 'myServo' to pin 7

  //move light out of the way of the sensors
  xServo.write(20);
  yServo.write(20);
  delay(500);


//  moveSlow(x0, y0);

}

void loop() {
  if (Serial.available()){
 
    if (Serial.parseInt() == 1 ){
      currentX++;
//      char my_string[3] = String(currentX);
      Serial.write(currentX);
    }
    if (Serial.parseInt() == 2){
      currentX--;
      Serial.write(currentX);
    }
    if (Serial.parseInt() == 3){
      currentY++;
      Serial.write(currentY);
    }
    if (Serial.parseInt() == 4){
      currentY--;
      Serial.write(currentY);
    }
    if (Serial.parseInt() == 5){
      currentX = x0;
      currentY = y0;
      Serial.write(currentX);
      Serial.write(currentY);
    }
  }
  

//  currentX++;
  xServo.write(currentX);
  yServo.write(currentY);
}



//void moveSlow(struct tuple ang){
//  moveSlow(ang.x, ang.y);
//}

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
