const int buzzerPin = 3;

void playScore(int firstScore, int secondScore) {
  int scores[] = {firstScore, secondScore};
  int frequencies[] = {100, 1000};
  
  for(int i = 0; i < 2; i++) {
    int score = scores[i];
    int freq = frequencies[i];
    
    for(int j = 0; j < score; j++) {
      tone(buzzerPin, freq, 200);
      delay(200);
    }
  }
}

void playHitSound() {
  tone(buzzerPin, 5, 100);
}

void playNewRoundSound() {
  const int melody[] = {500, 300, 200};
  for(int i = 0; i < 3; i++) {
    int freq = melody[i];
    tone(buzzerPin, freq, 200);
    delay(200);
  } 
}
