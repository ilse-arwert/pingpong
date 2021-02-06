//converted notes to frequencies with help of https://github.com/tsukisan/Arduino/blob/master/WiiClassicSoundboard/Notes.h
const int buzzerPin = 3;

void playPlayerEastSound() {
  int frequencies[] = {349, 523, 349, 1047};
  int durations[] = {125, 375, 125, 375};

  for(int i = 0; i < 4; i++) {
    int freq = frequencies[i];
    int duration = durations[i];
    tone(buzzerPin, freq, duration);
    delay(duration);
  }
}

void playPlayerWestSound() {
  int frequencies[] = {262, 523, 1319, 2093};
  int durations[] = {125, 375, 125, 375};

  for(int i = 0; i < 4; i++) {
    int freq = frequencies[i];
    int duration = durations[i];
    tone(buzzerPin, freq, duration);
    delay(duration);
  }
}

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
