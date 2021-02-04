
void checkScore(){
  if(xPos > w + ScoreDegreeThreshold ){
    // east gets a points
    lcdRed();
    ePlayer ++;
    playScore(wPlayer, ePlayer);
    newRound();
  }
  if (xPos < e - ScoreDegreeThreshold){
    // west gets a points
    lcdBlue();
    wPlayer ++;
    playScore(wPlayer, ePlayer);
    newRound();
  }
}
