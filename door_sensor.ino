const int MAGNET = 5;
const int RELAY = 22;

void setup() {
 Serial.begin(9600);
 pinMode(MAGNET, INPUT_PULLUP);
 pinMode(RELAY, OUTPUT);
}

void loop() {
 int magnetState = digitalRead(MAGNET);
 Serial.println(magnetState);
 if(magnetState == LOW) {
   digitalWrite(RELAY, LOW);
 } else {
   digitalWrite(RELAY, HIGH);
 }
}
