

const int thermistor1Pin = A0;    // input pin for the first thermistor
const int thermistor2Pin = A2;    // input pin for the second thermistor
const int doorPin = A5;    // input pin for the door
const int alarmLedPin = 12;      // pin for the error LED
const int LedPin = 13;       // pin for the heating LED


float temp1 = 0;  
float temp2 = 0;  
int door = 0;

const float thresh = 2.5;
const float hystersis = 0.1;

bool hot = false;
bool cold = false;
bool alert = true;
bool compared = true;


void hotorcold(float temp1) {
  if(temp1>thresh+hystersis) {
    cold = true;
    hot = false;

  } else if (temp1<thresh-hystersis) {
   hot = true;
   cold = false;
  }
}


void comparison(float temp1, float temp2){

  float diffper = abs(temp1-temp2)/((temp1+temp2)/2);
  
  if (diffper<0.2) {
    compared = true;
  } else {
    compared = false;
  }
}


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LedPin, OUTPUT);
  pinMode(alarmLedPin, OUTPUT);
  pinMode(doorPin, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {

temp1 = analogRead(thermistor1Pin)/1023.*5.0;
temp2 = analogRead(thermistor2Pin)/1023.*5.0;
door = digitalRead(doorPin);

hotorcold(temp1);
comparison(temp1, temp2);

if(hot == true || door == LOW || compared == false) {
  digitalWrite(alarmLedPin, HIGH);
  alert = true; 
}
else{
  digitalWrite(alarmLedPin, LOW);
  alert = false;
}

if(cold == true && alert == false) {
  digitalWrite(LedPin, HIGH);
  digitalWrite(alarmLedPin, LOW);
}
else{
  digitalWrite(LedPin, LOW);
}

Serial.print (temp1);
Serial.print (" ");
Serial.print (temp2);
Serial.print (" ");
Serial.print (door);
Serial.print (" ");
Serial.print (door);
Serial.print (" ");
Serial.println (alert);





  
}
