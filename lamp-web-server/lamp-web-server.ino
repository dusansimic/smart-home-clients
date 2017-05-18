/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFi101.h>


char ssid[] = "harms";      // your network SSID (name)
char pass[] = "isaocovekdaniil";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int state = LOW;
bool stateChanged = false;
const int ledPin = 0;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
  }

  // attempt to connect to WiFi network:
  
  server.begin();
  pinMode(ledPin, OUTPUT);
  // you're connected now, so print out the status:
}


void loop() {

  if ( status != WL_CONNECTED) {
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);
  
      // wait 10 seconds for connection:
      delay(10000);
    }
    printWiFiStatus();
  }

  if (stateChanged) {
    stateChanged = !stateChanged;
    digitalWrite(ledPin, state);
  }
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        if (request.indexOf("/turn-on") != -1 && state == LOW) {
          stateChanged = !stateChanged;
          state = !state;
        } else if (request.indexOf("/turn-off") != -1 && state == HIGH) {
          stateChanged = !stateChanged;
          state = !state;
        }
        client.flush();
        if (stateChanged) {
          client.println("HTTP/1.1 200 OK");
          client.println("Connection: close");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("ok");
        } else {
          client.println("HTTP/1.1 400 BAD REQUEST");
          client.println("Connection: close");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("not ok");
        }
      }
      // give the web browser time to receive the data
      delay(100);
      client.stop();
      // close the connection:
      Serial.println("client disonnected");
    }
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
