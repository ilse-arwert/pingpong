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
