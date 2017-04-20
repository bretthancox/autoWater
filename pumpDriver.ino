const int pumpPin = 2;
volatile int timePump = 0;
volatile int srlHolder;

void setup() {
 pinMode(LED_BUILTIN,OUTPUT);
 pinMode(pumpPin,OUTPUT);
 Serial.begin(9600);

blinkNow();
}

void loop() {
 while (Serial) {
  srlHolder = Serial.read();
  if (srlHolder == 1)//straight switch on; lights LED to show on
  {
   digitalWrite(LED_BUILTIN,HIGH);
   digitalWrite(pumpPin,HIGH);
   timePump = millis();
    }
  else if (srlHolder == 0)//straight switch off; switches LED off
  {
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   timePump = 0;
  }
 /* else if ((millis() - timePump) >= 60000 && (millis() - timePump) < 600000)//failsafe. If no off-signal is received, defaults to off after 60 seconds
  {
   digitalWrite(pumpPin,LOW);
   digitalWrite(LED_BUILTIN,LOW);
   timePump = 0;
  }*/
 }
while (!Serial) {
  blinkNow();
}
}


void blinkNow() {
 digitalWrite(LED_BUILTIN, HIGH);
 delay(1000);
 digitalWrite(LED_BUILTIN, LOW);
 delay(1000);
 digitalWrite(LED_BUILTIN, HIGH);
 delay(1000);
 digitalWrite(LED_BUILTIN, LOW);
}
