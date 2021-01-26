// one of these two in the main loop:
// moveCircle();
// moveCorners();

// required for demo
float gameState = 0;

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
