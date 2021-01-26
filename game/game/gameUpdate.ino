

// current target int
int targetX;
int targetY;


void gameUpdate(){
  
  sensorUpdate();
  
  // check if a move is made
  checkMove();

  goTowards(targetX, targetY, moveSpd);
  
  // check if we're over an edge
  checkScore();
  
}

void newRound(){
  // TODO: add beeping sound to signal new round
  playNewRoundSound();

  // printScore();
  
  // reset move speed
  moveSpd = moveSpdInit;
  // reset position
  goTo(x0, y0);

  digitalWrite(ledPin, HIGH);
  
  //wait before starting new round
  delay(1000);

  digitalWrite(ledPin, LOW);
  
  // select random player
  if (random(2) < 1){
    currentPlayer = 'w';
  } else {
    currentPlayer = 'e';
  }
  // go towards middle of current player side
  updateTarget(2, currentPlayer);
}


void printScore(){
  Serial.print("East score: ");
  Serial.println(ePlayer);
  Serial.print("West score: ");
  Serial.println(wPlayer);
}


void updateTarget(int sensor, char player){

  // TODO: Adjust y position so that light travels to corner of table, even if target lies beyond table (to enable scoring)
  // set y depending on sensor
  if (sensor == 1){
    targetY = n;
  }
  if (sensor == 2){
    targetY = y0;
  }
  if (sensor == 3){
    targetY = s;
  }
  
  // set x depending on player
  if (player == 'e'){
    targetX = e - ScoreDegreeThreshold * 2;
  }
  if (player == 'w'){
    targetX = w +  ScoreDegreeThreshold * 2;
  }

}
