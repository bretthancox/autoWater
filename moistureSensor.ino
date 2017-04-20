//Deprecated file

const int analogInPin = A1;
const int drivingPin = 7;
const int numReadings = 11;
const int pumpPin = 2;
int sensorValue = 0;
int sensorAvg = 0;

void setup() {

 // put your setup code here, to run once:
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(drivingPin,OUTPUT);
 pinMode(pumpPin,OUTPUT);
 Serial.begin(9600);
}

void loop() {
 /* Reads the soil moisture sensor 10 times, then averages the reading to reduce analog read noise:*/
for(int x = 0; x < numReadings; x++) {
   digitalWrite(drivingPin,HIGH);
   delay(4000);
   sensorValue = sensorValue + analogRead(analogInPin);
   digitalWrite(drivingPin,LOW);
   Serial.println("Sensor number: ");
   Serial.println(sensorValue);
 }

sensorAvg = (sensorValue/numReadings);
Serial.println("Sensor average: ");
Serial.println(sensorAvg);

 if (sensorAvg < 900)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   digitalWrite(pumpPin,HIGH);
   delay(30000);
 }
 else if (sensorAvg >= 900 && sensorAvg < 1000)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   delay(2000);
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   delay(3600000);
 }
 else if (sensorAvg >= 1000)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   delay(2000);
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   delay(7200000);
 }

 sensorValue = 0;
}
