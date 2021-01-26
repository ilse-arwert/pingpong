// scores
int wPlayer = 0;
int ePlayer = 0;

void checkScore(){
  if(xPos > w + ScoreDegreeThreshold ){
    // east gets a points
    ePlayer ++;
    newRound();
  }
  if (xPos < e - ScoreDegreeThreshold){
    // west gets a points
    wPlayer ++;
    newRound();
  }
}
