// scores
int wPlayer = 0;
int ePlayer = 0;

void checkScore(){
  if(xPos > w + ScoreDegreeThreshold ){
    // east gets a points
    ePlayer ++;
    playScore(wPlayer, ePlayer);
    newRound();
  }
  if (xPos < e - ScoreDegreeThreshold){
    // west gets a points
    wPlayer ++;
    playScore(wPlayer, ePlayer);
    newRound();
  }
}
