const int analogInPin = A1;
const int bottomPin = 7;
const int topPin = 4;
const int pumpPin = 2;
int reading;

/*

   topPin
     |
     |
     \
      || Resistor(47k)
      /
     |
     |
     ----- analogInPin
     |
     |
     ----- probe 1

     ----- probe 2
     |
     |
     |
   bottomPin

*/

void setup() {

 // put your setup code here, to run once:
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(bottomPin,OUTPUT);
 pinMode(topPin, OUTPUT);
 pinMode(pumpPin,OUTPUT);
 Serial.begin(9600);
 Serial.println("Setup complete");
}

//---------------------------------

void loop() {
 takeReading();
 waterDecision(reading);
}

//---------------------------------

void takeReading() 
{
digitalWrite(topPin, HIGH);
digitalWrite(bottomPin, LOW);

delay(1000);

reading = analogRead(analogInPin);

digitalWrite(topPin, LOW);
digitalWrite(bottomPin, HIGH);

delay(1000);

digitalWrite(bottomPin, LOW);

Serial.print("Reading: ");
Serial.println(reading);

return reading;
}

//---------------------------------

void waterDecision(int value) {
  if (value > 400)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   digitalWrite(pumpPin,HIGH);
   delay(20000);
 }
 else if (value >= 350 && value < 400)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   delay(2000);
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   delay(3600000);
 }
 else if (value <= 350)
 {
   digitalWrite(LED_BUILTIN,HIGH);
   delay(2000);
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   delay(7200000);
 }
}
