
void checkMove(){
  // check if we're outside of the center
  if (xPos > x0 + SensorDegreeThreshold || xPos < x0 - SensorDegreeThreshold){
    if (sensor1){
      nextMove();
      updateTarget(1, currentPlayer);
    }
    if (sensor2){
      nextMove();
      updateTarget(2, currentPlayer);
    }
    if (sensor3){
      nextMove();
      updateTarget(3, currentPlayer);
    }
  }
}

void nextMove(){
  // TODO: Add sound to signal move made.
  
  // check if light is on player side
  if (currentPlayer == 'e' && xPos < x0 ){
    currentPlayer = 'w';
    moveSpd += moveSpdIncr;
  } 
  if (currentPlayer == 'w' && xPos > x0 ){
    currentPlayer = 'e';
    moveSpd += moveSpdIncr;
  }
}
