#include <SPI.h>
#include <WiFi101.h>
#include <DHT.h>

const int dhtPin = 0;
#define DHTTYPE DHT11

DHT dht(dhtPin, DHTTYPE);

char ssid[] = "harms";
char pass[] = "isaocovekdaniil";
int keyIndex = 0;

int status = WL_IDLE_STATUS;

char server[] = "192.168.0.10";

WiFiClient client;

void setup() {

  Serial.begin(9600);
  
}

void loop() {
  delay(5000);
  if (status != WL_CONNECTED) {
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);

      status = WiFi.begin(ssid, pass);


      delay(10000);
    }
    Serial.println("Connected to wifi");
    printWiFiStatus();
  }



  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 3000)) {

    float temperature = (float) dht.readTemperature();
    float humidity = (float) dht.readTemperature();
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println(String("GET /api/new-data?temperature=") + temperature + "&humidity=" + humidity + " HTTP/1.1");

    client.println(String("Host: ") + server);
    client.println("Connection: close");
    client.println();
  }


  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  client.stop();


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
