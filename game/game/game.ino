#include <Servo.h> 
#include <math.h>

//the table:
//          N
//    ------.------ 
// W |      ,      | E
//   |             |
//    ------'------
//          S

// declare servo
Servo xServo;          
Servo yServo; 

// center point
int x0 = 90;
int y0 = 90;

// angle to edge
// only W and S need to be entered manually

int w = 122;
int s = 108;
int e = x0 - (w - x0);
int n = y0 - (s - y0);

float xPos = x0;
float yPos = y0;

float gameState = 0;

void setup() {
  // attach servos
  xServo.attach(4);
  yServo.attach(7);
  Serial.begin(9600);

}

void loop() {

  // run one of the two, not both
  moveCircle();
  // moveCorners();
  
  // some delay is needed otherwise servo goes crazy
  delay(25);
}

void moveCorners(){
    if (gameState == 0){
    goTo(x0, y0);
    delay(200);
    gameState++;
  }

  if (gameState == 1){
    goTowards(e, n, 1);
    nextState(e, n);  
  }
  
  if (gameState == 2){
    goTowards(e, s, 1);
    nextState(e, s);  
  }
  
  if (gameState == 3){
    goTowards(w, n, 2);
    nextState(w, n);  
  }

  if (gameState == 4){
    goTowards(w, s, 1);
    nextState(w, s);  
  }
  if (gameState == 5){
    gameState = 0;
  }
}

void moveCircle(){
  int r = n - y0;
  float tX = sin(gameState/20)* r;
  float tY = cos(gameState/20)* r ;
  goTowards(x0 + tX, y0 + tY, 1);
  nextState(x0 + tX, y0 + tY);
}

void nextState(float tX, float tY){
  // if target matches position
  if (tX == xPos && tY == yPos){
    gameState++;
  }
}
