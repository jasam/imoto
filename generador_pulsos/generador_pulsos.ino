boolean signal;
int dinamycDelay;
float radius;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
  dinamycDelay = 78.99848887;
  radius = 0.0002794;
}

void loop() {
  digitalWrite(13, HIGH);
  delay(dinamycDelay);
  signal = digitalRead(8);
  Serial.println(signal);
  digitalWrite(13, LOW);
  delay(dinamycDelay);
  signal = digitalRead(8);
  Serial.println(signal); 
}  
