
#include <SD.h>
#include <EEPROM.h>

int RIGHT = 9;
int LEFT = 8;
int ULTRASONIC_CONSTANT = 58;
int DELAY = 1000;

// sense vars
int triggerRight = 6;
int echoRight = 7;
int triggerLeft = 8;
int echoLeft = 9;
int rightDistance;
int leftDistance;

// Centimeters
int distance;

// file vars
File myFile;
String fileName = "imoto.csv";

// flag serial event
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// name for arduino
char sID[7];

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
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  //Serial.println("initialization done.");
  inputString.reserve(50);
}

void loop() {
  // Sensing
  rightDistance = senseUltraSonic(RIGHT);
  leftDistance = senseUltraSonic(LEFT);
  
  // Saving sense data
  saveData("IM0001",rightDistance, leftDistance, 1, millis());
  //Serial.println("Distancia derecha" + (String)rightDistance + " cm");
  //Serial.println("Distancia izquierda" + (String)leftDistance + " cm");
  
  // switch for services exposed
  if (stringComplete) {
    // Download data
    if (inputString == "d") {
      downLoadData();
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
  }
  
  delay(DELAY);
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

void saveData(String idComputer, int rightDistance, int leftDistance, int sPeed, int date){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("imoto.csv", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    String registro = idComputer + "," + (String)rightDistance + "," + (String)leftDistance + "," + (String)sPeed + "," + (String)date;
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
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      inputString.replace("\n", "");
      stringComplete = true;
    } 
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
  
