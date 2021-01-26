int northPin = A0;
int middlePin = A2;
int southPin = A4;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(northPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(southPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  plotPin(southPin);
}

void printAllPins() {
  Serial.println(String("North: " + String(analogRead(northPin), DEC) + String(" --- Middle: " + String(analogRead(middlePin), DEC)) + String(" --- South: " + String(analogRead(southPin), DEC)))); 
}

void printPin(int pin) {
  Serial.println(String(pin, DEC) + ": " + String(analogRead(pin), DEC)); 
}

void plotPin(int pin) {
  Serial.println(analogRead(pin));
}
