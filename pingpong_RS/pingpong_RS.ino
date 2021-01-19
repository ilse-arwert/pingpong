#include <Servo.h>      // include the Servo library
#include <math.h>

//the table:
//          A
//    ------.------ 
// B |      ,      | C
//   |             |
//    ------'------
//          D

Servo rotate;          // declare Servo object
Servo swing;          // declare Servo object

//set up the photoresistors
const int upperSensorPin = 0;
int baseUpperLight;
int currentUpperLight;

const int middleSensorPin = 1;
int baseMiddleLight;
int currentMiddleLight;

const int lowerSensorPin = 2;
int baseLowerLight;
int currentLowerLight;

const int buzzer = 9;

//Variables
int lampHeight = 165;
String currentPlayer = "right"; //The first player is at side C, on the right

// Coordinates: (Rotate, Swing, X-coordinate, Y-coordinate)
// middle: R x, S 90
int A[] = {0, 120};
int B[] = {90, 45};
int C[] = {90, 135};
int D[] = {0, 60};

int AB[] = {120, 40};
int AC[] = {60, 140};
int BD[] = {60, 40};
int CD[] = {120, 140};

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  rotate.attach(4);    // attach object 'myServo' to pin 4
  swing.attach(7);    // attach object 'myServo' to pin 7
  
  swing.write(C[1]);
  rotate.write(C[0]);
  
  baseMiddleLight = analogRead(middleSensorPin);
  baseUpperLight = analogRead(upperSensorPin);
  baseLowerLight = analogRead(lowerSensorPin);
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
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    while(1); //the player didn't reflect the light. sound the buzzer and stop the game.
  }
  
  if ((currentMiddleLight - baseMiddleLight) > 100) {
    moveThroughMiddle();
  }

  else if ((currentUpperLight - baseUpperLight) > 100) {
    if (currentPlayer == "left") moveLight(AC);
    else moveLight(AB);
  }

  else if ((currentLowerLight - baseLowerLight) > 100) {
    if (currentPlayer == "left") moveLight(CD);
    else moveLight(BD);
  }

  if (currentPlayer == "left") currentPlayer = "right";
  else currentPlayer = "left";
}

// oh dit is helemaal kut
//void calcAngles(int[4] goal, int[4] current) {
//  int middleS;
//  double middleY = (current[3] + goal[3])/2;
//  if (middleY == 0) return; //if we go through the middle it's easy.
//
//  // the swing is essentially a cup parabola over the rotation.
//  int currentSwing = swing.read();
//  int currentRotate = rotate.read();
//
//  //this isn't quite right but works for now
//  if (middleY > 0 {
//    int middleS = 90 + atan2(middleY , lampHeight);
//  }
//  else int middleS = 90 - atan2(abs(middleY) , lampHeight);
//  
//}

void moveThroughMiddle() {
  int currentSwing = swing.read();
  int toSwing = 2 * (90 - currentSwing);
  delay(1000);
  if(toSwing > 0) { //moving to the right
    while (toSwing > 0) {
      currentSwing += 1;
      toSwing -= 1;
      swing.write(currentSwing);
      delay(20);
    }
  }
  else { //moving to the left
    while (toSwing < 0) {
      currentSwing -= 1;
      toSwing += 1;
      swing.write(currentSwing);
      delay(20);
    }
  }
}

//this is a quick cheat, ball won't go in a straight line yet
void moveLight(int target[]) {
  rotate.write(target[0]);
  moveThroughMiddle();
}
