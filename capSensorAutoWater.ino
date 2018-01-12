const int triggerReadPin = 7; //Used to provide power to the 555 timer circuit
const int readPin = 8; //Used to read the pulses from the 555 timer circuit
const int pumpPin = 2; //Used to trigger the water pump
void takeReading(int* a);
void waterDecision(int* value);
int highReading;
//int Lreading;
int highTime;
//int Ltime;


void setup() {

 // put your setup code here, to run once:
 pinMode(readPin,INPUT);
 pinMode(pumpPin,OUTPUT);
 pinMode(triggerReadPin, OUTPUT);
 Serial.begin(9600);
 Serial.println("Setup complete");
}

//---------------------------------

void loop() {
 takeReading( &highReading );
 Serial.println(highReading);
 waterDecision( &highReading );
}

//---------------------------------

void takeReading(int* a) {
digitalWrite(triggerReadPin, HIGH);
delay(1000);
highTime = 0;
//Ltime = 0;

for(int i=0;i<10;i++) {
  highTime += pulseIn(readPin,HIGH);
  //Ltime += pulseIn(readPin,LOW);
  }
  
*a = highTime/10;
//*b = Ltime/10;

return;
}

//---------------------------------

void waterDecision(int* value) {
  
  if (*value < 1000)
 {
   digitalWrite(pumpPin,HIGH);
   delay(10000);
   digitalWrite(pumpPin,LOW);
   Serial.println("Watered");
 }
 else if (*value >= 1000 && *value < 1500)
 {
   digitalWrite(pumpPin,LOW);
   Serial.println("Moist. Checking again in an hour.");
   delay(3600000);
 }
 else if (*value >= 1500)
 {
   digitalWrite(pumpPin,LOW);
   Serial.println("Wet. Checking again in two hours.");
   delay(7200000);
 }
 return;
}
