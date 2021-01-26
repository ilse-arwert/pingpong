#include <Servo.h> 
#include <math.h>

//the table:
//        + N
//   --------------- 
//   |      1      | 
// W | +    2    - | E
//   |      3      |
//   ---------------
//        - S

// declare servo
Servo xServo;          
Servo yServo; 

// center point
const int x0 = 84;
const int y0 = 91;

// angle to edge
// only W and S need to be entered manually

const int w = 117;
const int s = 108;
const int e = x0 - (w - x0);
const int n = y0 - (s - y0);

float xPos = x0;
float yPos = y0;

// sensors on or off
bool sensor1 = false;
bool sensor2 = false;
bool sensor3 = false;

// who is playing, either 'e' or 'w'
char currentPlayer;

// scoring threshold, how many degrees over the table edge
const int ScoreDegreeThreshold = 8;
// sensor degree trigger threshold, how many degrees away from center to be able to trigger sensor
const int SensorDegreeThreshold = 7;
// sensor light treshold in order to change on/off
const int SensorLightThreshold = 20;

// change initial speed
float moveSpdInit = 0.2;
float moveSpd = moveSpdInit;
// change speed increment per move
float moveSpdIncr = 0.05;

int ledPin = 2;

void setup() {
  // attach servos
  xServo.attach(4);
  yServo.attach(7);
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  // random seed for which player starts
  randomSeed(analogRead(6));
  // initialise sensors
  sensorInit();

  // start the game
  newRound(); 
}

void loop() {

  gameUpdate();


  // some delay is needed otherwise servo goes crazy
  delay(25);
}
