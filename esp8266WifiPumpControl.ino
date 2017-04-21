#include <ESP8266WiFi.h>
 
 const char* ssid = "AP";
 const char* password = "passsword1";
 const char* ssid_work = "AP_work";
 const char* password_work = "password2";
 const int outputOff = 0;
 const int outputOn = 1;
 volatile char host; //This is the holder for the IP address, once issued by the AP
 int ledPin = LED_BUILTIN;
 
 WiFiServer server(301); //just pick any port number you like
 
 void setup() {
   Serial.begin(9600);
   delay(10);
 Serial.println(WiFi.localIP());
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH);
 
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
 
   WiFi.begin(ssid, password);
   delay(10000);
 
   if (WiFi.status() != WL_CONNECTED) {
     Serial.println("No connection. Failing over to work WiFI");
     Serial.println();
     Serial.println();
     Serial.print("Connecting to ");
     Serial.println(ssid_work);
     WiFi.begin(ssid_work, password_work);
     while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
     }
   }
   Serial.println("");
   Serial.println("WiFi connected");
 
   // Start the server
   server.begin();
   Serial.println("Server started");
 
   // Print the IP address
   Serial.println(WiFi.localIP());
   host = char(WiFi.localIP());
   Serial.println(host);
   
 }
 
 void loop() {
   // Check if a client has connected
   WiFiClient client = server.available();
   if (!client) {
     return;
   }
 
   // Wait until the client sends some data
   while (!client.available()) {
     delay(1);
   }
 
   // Read the first line of the request
   String req = client.readStringUntil('\r');
   Serial.println(req);
   client.flush();
 
   // Match the request
   if (req.indexOf("") != -10) {  //checks if you're on the main page
     if (req.indexOf("/led/OFF") != -1) { //checks if you clicked OFF and sets LED OFF - TEST
       digitalWrite(ledPin, HIGH);
       Serial.println("You clicked OFF");
     }
     if (req.indexOf("/led/ON") != -1) { //checks if you clicked ON and sets LED ON - TEST
       digitalWrite(ledPin, LOW);
       Serial.println("You clicked ON");
     }
     {
     if (req.indexOf("/pump/OFF") != -1) { //checks if you clicked OFF and sends serial signal to switch pump off
       Serial.write(outputOff);
       digitalWrite(ledPin, LOW);
       delay(1000);
       digitalWrite(ledPin, HIGH);
       Serial.println("You clicked OFF");
     }
     {
     if (req.indexOf("/pump/ON") != -1) { //checks if you clicked ON  and sends serial signal to switch pump on
       Serial.write(outputOn);
       digitalWrite(ledPin, LOW);
       delay(1000);
       digitalWrite(ledPin, HIGH);
       delay(1000);
       digitalWrite(ledPin, LOW);
       delay(1000);
       digitalWrite(ledPin, HIGH);
       Serial.println("You clicked ON");
       }
     }
    }
 }
   else {
     Serial.println("invalid request");
    client.stop();
     return;
   }
 
   // Prepare the response
   String s = "HTTP/1.1 200 OK\r\n";
   s += "Content-Type: text/html\r\n\r\n";
   s += "<!DOCTYPE HTML>\r\n<html>\r\n";
   s += "<br><input type=\"button\" name=\"bl\" value=\"Turn LED ON \" onclick=\"location.href='/led/ON'\">";
   s += "<br><br><br>";
   s += "<br><input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" onclick=\"location.href='/led/OFF'\">";
   s += "<br><br><br>";
   s += "<br><input type=\"button\" name=\"bl\" value=\"Turn pump ON\" onclick=\"location.href='/pump/ON'\">";
   s += "<br><br><br>";
   s += "<br><input type=\"button\" name=\"bl\" value=\"Turn pump OFF\" onclick=\"location.href='/pump/OFF'\">";
   s += "</html>\n";
 
   client.flush();
 
 
   // Send the response to the client
   client.print(s);
   delay(1);
 
   if (WiFi.status() != WL_CONNECTED) {
     Serial.println("No connection. Retrying");
     Serial.println();
     Serial.println();
     Serial.print("Connecting to ");
     Serial.println(ssid);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
     }
   }
   
 }