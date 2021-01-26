// destination x, y, speed
void goTowards(float x, float y, float spd){
  float distX = x - xPos;
  float distY = y - yPos;
  float mag = sqrt(sq(distX)+sq(distY));
//  Serial.println(mag);
  if (mag <= spd){
    ;
    goTo(x, y);
  } else {
    goTo(
      xPos + (distX / mag) * spd, 
      yPos + (distY / mag) * spd
      );
  }
}

// go directly to position
void goTo(float x, float y){
  xServo.write(round(x));
  yServo.write(round(y));
  xPos = x;
  yPos = y;
}

void goToTarget(int sensor, char player){
  int newX;
  int newY;

  // TODO: Adjust y position so that light travels to corner of table, even if target lies beyond table (to enable scoring)
  // set y depending on sensor
  if (sensor == 1){
    newY = n;
  }
  if (sensor == 2){
    newY = y0;
  }
  if (sensor == 3){
    newY = s;
  }
  
  // set x depending on player
  if (player == 'e'){
    newX = e;
  }
  if (player == 'w'){
    newX = w;
  }

  goTowards(newX, newY, moveSpd);
  
}
