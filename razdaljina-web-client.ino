const int trigPin = 1;
const int echoPin= 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  delay(100);
  Raz();
}

long Raz(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
    return -1;
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }
}



















#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "ssid";
char pass[] = "password";
int keyIndex = 0;

const int trigPin = 0;
const int echoPin= 1;

int status = WL_IDLE_STATUS;

char server[] = "ip";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

void loop() {
  delay(500);

  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 3000)) {
    Serial.println("connected to server");
    long razdaljina = (long) Raz();
    client.println(String("GET /api/new-data?distance=") + razdaljina + String(" HTTP/1.1"));
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

long Raz(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
    return -1;
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }*
}

