import processing.serial.*;

Serial port;



void setup() {
  printArray(Serial.list());

  port = new Serial(this, Serial.list()[0], 9600);
}

// up 0 down 1 left 2 right 3 reset 4

void draw() {
  if (keyPressed) {
    if (key ==  'w') {
      port.write(1);
    }
    if (key ==  's') {
      port.write(2);
    }
    if (key ==  'a') {
      port.write(3);
    }
    if (key ==  'd') {
      port.write(4);
    }
    if (key ==  'r') {
      port.write(5);
    }
  } else {
    port.write(0);
  }
}
