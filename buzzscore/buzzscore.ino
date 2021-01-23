struct player {
  int score;
  int freq; 
};

struct player rightPlayer = { .score = 2, .freq = 100 };
struct player leftPlayer = { .score = 1, .freq = 1000 };
const int buzzerPin = 3;

void setup() {
  pinMode(buzzerPin, OUTPUT); 

  //has to be run once before score is changed to detect the change
  buzzScore(rightPlayer, leftPlayer);
  rightPlayer.score++;
  
  buzzScoreSync(rightPlayer, leftPlayer);
}

void loop() {
  buzzScore(rightPlayer, leftPlayer);
}

void buzzScoreSync(struct player firstPlayer, struct player secondPlayer) {
  struct player players[] = { firstPlayer, secondPlayer };

  for(int playerIndex = 0; playerIndex < (sizeof(players)/sizeof(struct player)); playerIndex++ ) {
    struct player p = players[playerIndex];
    for(int i = 0; i < p.score; i++) {
      tone(buzzerPin, p.freq, 500);
      delay(750);
    }
  }
}

void buzzScore(struct player firstPlayer, struct player secondPlayer) {
  static bool isPlayingSequence = false;
  static int prevFirstPlayerScore;
  static int prevSecondPlayerScore;
  const int tonePlayDuration = 250;
  const int toneDelayDuration = 500;

  if(isPlayingSequence) {
    struct player players[] = { firstPlayer, secondPlayer };
    static int playerIndex = 0;
    struct player p = players[playerIndex];
    static int remaingPoints = p.score;
    static bool isPlayingTone = false;
    static unsigned long startTime = millis();

    if(!remaingPoints) {
      if(playerIndex == 1) {
        playerIndex = 0;
        prevFirstPlayerScore = firstPlayer.score;
        prevSecondPlayerScore = secondPlayer.score;
        isPlayingSequence = false;
        return;
      } 

      playerIndex = 1;
      remaingPoints = players[playerIndex].score;
      return; 
    }

    if(!isPlayingTone && millis() > startTime + tonePlayDuration) {
      tone(buzzerPin, p.freq);
      isPlayingTone = true;
      startTime = millis();
    } else if(isPlayingTone && millis() > startTime + toneDelayDuration) {
      noTone(buzzerPin);
      isPlayingTone = false;
      startTime = millis();
      remaingPoints--;
    }
  }

  if(!prevFirstPlayerScore && !prevSecondPlayerScore) {
    prevFirstPlayerScore = firstPlayer.score;
    prevSecondPlayerScore = secondPlayer.score;
  }

  if(firstPlayer.score != prevFirstPlayerScore || secondPlayer.score != prevSecondPlayerScore) {
    isPlayingSequence = true;
  }
}
