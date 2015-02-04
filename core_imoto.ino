
#include <SD.h>

int RIGHT = 9;
int LEFT = 8;
int ULTRASONIC_CONSTANT = 58;

// sense vars
int triggerRight = 7;
int echoRight =8;
int triggerLeft = 9;
int echoLeft = 10;
int rightDistance;
int leftDistance;
// Centimeters
int distance;

// file vars
File myFile;
String fileName = "imoto.csv";

char flagValue = '0';

void setup() {
  Serial.begin(9600); 
  pinMode(triggerRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(triggerLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  /*pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");*/
}

void loop() {
  rightDistance = senseUltraSonic(RIGHT);
  leftDistance = senseUltraSonic(LEFT);
  //saveData(rightDistance, leftDistance, 1, 1, millis());
  Serial.println("Distancia derecha" + (String)rightDistance + " cm");
  Serial.println("Distancia izquierda" + (String)leftDistance + " cm");
  if (flagValue == '1'){
  }
  delay(1000);
}

int senseUltraSonic(int side) {
  
  // Right sensor
  if (side == RIGHT) {
    digitalWrite(triggerRight,LOW); 
    delayMicroseconds(5);
    digitalWrite(triggerRight, HIGH); 
    delayMicroseconds(10);
    distance = pulseIn(echoRight, HIGH);
    distance = distance / ULTRASONIC_CONSTANT;
  }
  // Left sensor
  else {
    digitalWrite(triggerLeft,LOW); 
    delayMicroseconds(5);
    digitalWrite(triggerLeft, HIGH); 
    delayMicroseconds(10);
    distance = pulseIn(echoLeft, HIGH);
    distance = distance / ULTRASONIC_CONSTANT;
  }
  return distance;
}

void saveData(int ID, int d1, int d2, int vel, int date){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("imoto.csv", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    String registro = (String)ID + "," + (String)d1 + "," + (String)d2 + "," + (String)vel + "," + (String)date;
    myFile.println(registro);
    // close the file:
    myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + fileName);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    flagValue = '1';
  }
}

void downLoadData() {
  //Send data to the Serial port
  // re-open the file for reading:
  myFile = SD.open("imoto.csv");
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    Serial.print("EOF");
        
    // delete the file:
    SD.remove("imoto.csv");
    } 
    else {
      // if the file didn't open, print an error:
      Serial.println("error opening " + fileName);
    }
}
  
