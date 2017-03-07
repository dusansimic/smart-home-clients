#include <SPI.h>
#include <WiFi101.h>
#include <dht11.h>

dht11 DHT11;
const int dhtPin = 0;

char ssid[] = "ssid";
char pass[] = "password";
int keyIndex = 0;

int status = WL_IDLE_STATUS;

char server[] = "ip";

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
    int chk = DHT11.read(dhtPin);

    Serial.print("Read sensor: ");
    switch (chk)
    {
      case DHTLIB_OK:
      Serial.println("OK");
      break;
      case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
      case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
      default:
      Serial.println("Unknown error");
      break;
    }

    float temperature = (float) DHT11.temperature;
    float humidity = (float) DHT11.humidity;
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
