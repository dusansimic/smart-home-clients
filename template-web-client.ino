#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "ssid";
char pass[] = "password";
int keyIndex = 0;

int status = WL_IDLE_STATUS;

char server[] = "ip address";

WifiClient client;

void setup {
  Serial.begin(9600);
  while(!Serial)
    ;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);


    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();
}

void loop {
  delay(5000);

  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 3000)) {
    Serial.println("connected to server");

    client.println("GET /api/check HTTP/1.1");
    client.println(String("Host: ") + server);
    client.println("Connection: close");
    client.println();
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  client.close();
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
