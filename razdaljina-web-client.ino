const int trigPin=2;
const int echoPin= 3;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  delay(100);
  long raz = Raz();
  Serial.println(raz);
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
    return -1;
    //Serial.println("Out of range");
  }
  else {
    return distance;
    //Serial.print(distance);
    //Serial.println(" cm");
  }
}
