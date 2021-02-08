
void checkScore(){
  if(xPos > w + ScoreDegreeThreshold ){
    // east gets a points
    lcdRed();
    ePlayer ++;
    playPlayerEastSound();
    newRound();
  }
  if (xPos < e - ScoreDegreeThreshold){
    // west gets a points
    lcdBlue();
    wPlayer ++;
    playPlayerWestSound();
    newRound();
  }
}
