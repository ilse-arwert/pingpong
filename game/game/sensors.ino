//TODO: Should we turn sensors into an array (sensorPin[] sensorBase[] etc) so that we can loop over them?

// pins
const int sensor1Pin = 2;
const int sensor2Pin = 0;
const int sensor3Pin = 4;

// base value
int sensor1Base;
int sensor2Base;
int sensor3Base;

// current value
int sensor1Current;
int sensor2Current;
int sensor3Current;

// sets base values.
void sensorInit(){
  sensor1Base = analogRead(sensor1Pin);
  sensor2Base = analogRead(sensor2Pin);
  sensor3Base = analogRead(sensor3Pin);
}

// sets sensor1/2/3 values to true/false.
void sensorUpdate(){

  sensor1Current = analogRead(sensor1Pin);
  sensor2Current = analogRead(sensor2Pin);
  sensor3Current = analogRead(sensor3Pin);
  
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
