import processing.serial.*;

Serial port;



void setup() {
  printArray(Serial.list());

  port = new Serial(this, Serial.list()[2], 9600);
  port.bufferUntil('\n');
}

// up 0 down 1 left 2 right 3 reset 4

void draw() {
   
  if (keyPressed) {
    if (key ==  'w') {
      port.write("1\n");
      //print('w');
    }
    if (key ==  's') {
      port.write("2\n");
    }
    if (key ==  'a') {
      port.write("3\n");
    }
    if (key ==  'd') {
      port.write("4\n");
    }
    if (key ==  'r') {
      port.write("5\n");
    }
  } 
  
  if (port.available() > 0){
    print(port.read());
  }
}
