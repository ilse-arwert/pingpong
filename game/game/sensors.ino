// pins
const int sensor1Pin = 2;
const int sensor2Pin = 0;
const int sensor3Pin = 1;

// current average base value
float sensor1Base;
float sensor2Base;
float sensor3Base;

//vectors holding the base values
int BaseAveragingCount = 16;
int sensor1Bases [16];
int sensor2Bases [16];
int sensor3Bases [16];
int currentIndex = 0;

// current value
int sensor1Current;
int sensor2Current;
int sensor3Current;

// sets base values.
void sensorInit(){
  sensor1Base = analogRead(sensor1Pin);
  sensor2Base = analogRead(sensor2Pin);
  sensor3Base = analogRead(sensor3Pin);
  for (int i = 0; i < BaseAveragingCount; i++) {
    sensor1Bases[i] = sensor1Base;
    sensor2Bases[i] = sensor2Base;
    sensor3Bases[i] = sensor3Base;
  }
}

// sets sensor1/2/3 values to true/false.
void sensorUpdate(){

  sensor1Current = analogRead(sensor1Pin);
  sensor2Current = analogRead(sensor2Pin);
  sensor3Current = analogRead(sensor3Pin);

  // Serial.println("Before updating: ");
  // printArrays();
  updateBaseline(sensor1Current, sensor2Current, sensor3Current);
  
  if ((sensor1Current - sensor1Base) > SensorLightThreshold){
    sensor1 = true;
  } else {
    sensor1 = false;
  }
    if ((sensor2Current - sensor2Base) > SensorLightThreshold){
    sensor2 = true;
  } else {
    sensor2 = false;
  }
    if ((sensor3Current - sensor3Base) > SensorLightThreshold){
    sensor3 = true;
  } else {
    sensor3 = false;
  }
}

void updateBaseline(int s1, int s2, int s3) {
  //als er geen licht op de sensors staat, updaten we de baselines
//    Serial.println("Updating the baselines");
    currentIndex += 1;
    currentIndex = currentIndex % BaseAveragingCount;
    sensor1Bases[currentIndex] = s1;
    sensor2Bases[currentIndex] = s2;
    sensor3Bases[currentIndex] = s3;
    
    // printArrays();
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;

    for (int i = 0; i < BaseAveragingCount; i++) {
      sum1 += sensor1Bases[i];
    }
    for (int i = 0; i < BaseAveragingCount; i++) {
      sum2 += sensor2Bases[i];
    }
    for (int i = 0; i < BaseAveragingCount; i++) {
      sum3 += sensor3Bases[i];
    }
    
    sensor1Base = sum1/BaseAveragingCount;
    sensor2Base = sum2/BaseAveragingCount;
    sensor3Base = sum3/BaseAveragingCount;

    Serial.print(sensor2Base);
    Serial.print(",");
    Serial.println(sensor2Current);
}

void printBases() {
  Serial.println("Sensor 1: ");
  Serial.println("Base value: " + String(sensor1Base));
  Serial.println("Current value: " + String(sensor1Current));
  Serial.println("Sensor 2: ");
  Serial.println("Base value: " + String(sensor2Base));
  Serial.println("Current value: " + String(sensor2Current));
  Serial.println("Sensor 3: ");
  Serial.println("Base value: " + String(sensor3Base));
  Serial.println("Current value: " + String(sensor3Current));
}

void printArrays() {
  Serial.println("Base values sensor 1:");
  for (int i = 0; i < BaseAveragingCount; i++) {
    Serial.println(sensor1Bases[i]);
  }
  Serial.println("Base values sensor 2:");
  for (int i = 0; i < BaseAveragingCount; i++) {
    Serial.println(sensor2Bases[i]);
  }
  Serial.println("Base values sensor 3:");
  for (int i = 0; i < BaseAveragingCount; i++) {
    Serial.println(sensor3Bases[i]);
  }
  Serial.println();
}
