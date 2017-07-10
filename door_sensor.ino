// Elevator 1
const int MAGNET_1 = 22;
const int RELAY_1 = 24;

// Elevator 2
const int MAGNET_2 = 28;
const int RELAY_2 = 30;

// Elevator 3
const int MAGNET_3 = 36;
const int RELAY_3 = 38;

// Elevator 4
const int MAGNET_4 = 46;
const int RELAY_4 = 48;

void setup() {
 Serial.begin(9600);
 pinMode(MAGNET_1, INPUT_PULLUP);
 pinMode(MAGNET_2, INPUT_PULLUP);
 pinMode(MAGNET_3, INPUT_PULLUP);
 pinMode(MAGNET_4, INPUT_PULLUP);
 pinMode(RELAY_1, OUTPUT);
 pinMode(RELAY_2, OUTPUT);
 pinMode(RELAY_3, OUTPUT);
 pinMode(RELAY_4, OUTPUT);
}

void loop() {
 // Force elevators to rotate if input is given
 if (Serial.available()) {
  rotate();
 }
  
 // Sensor logic
 // If the magnets are touching, turn power off
 // Else, turn power on.
 elevatorOne();
 elevatorTwo();
 elevatorThree();
 elevatorFour();
}

// Force elevators to rotate
void rotate() {
 // Grab input
 // Input MUST be in the following format: #;#;#;#;
 // Where # can be any integer as seconds
 String input = Serial.readString();

 // Initialize counters and array to store delay time
 int substrCounter = 0;
 int arrayCounter = 0;
 int delays[4];

 // Parse input and store
 for (int i = 0; i < input.length(); i++) {
  if (input.substring(i, i+1) == ";") {
   delays[arrayCounter] = input.substring(substrCounter, i).toInt();
   substrCounter = i + 1;
   arrayCounter++;
  }
 }

 // Elevator rotation logic
 // If all the delays are the same, rotate all elevators at once
 // Else, rotate each elevator one by one
 if(delays[0] == delays[1] && delays[0] == delays[2] && delays[0] == delays[3]) {
  Serial.println("Starting all rotations...");
  elevatorAllRotate(delays[0]);
 }
 else {
  Serial.println("Starting individual rotations...");
  if(delays[0] > 0) { elevatorOneRotate(delays[0]); }
  if(delays[1] > 0) { elevatorTwoRotate(delays[1]); }
  if(delays[2] > 0) { elevatorThreeRotate(delays[2]); }
  if(delays[3] > 0) { elevatorFourRotate(delays[3]); }
 }

 // Debugging purposes
 Serial.print("Input: ");
 Serial.println(input);
 Serial.print("Delay one: ");
 Serial.println(delays[0]);
 Serial.print("Delay two: ");
 Serial.println(delays[1]);
 Serial.print("Delay three: ");
 Serial.println(delays[2]);
 Serial.print("Delay four: ");
 Serial.println(delays[3]);
}

// Force all elevators to rotate for t seconds
void elevatorAllRotate(int t) {
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  delay(t * 1000);
  Serial.println("Completed all rotations!");
}

// Force Elevator 1 to rotate for t seconds
void elevatorOneRotate(int t) {
  digitalWrite(RELAY_1, LOW);
  delay(t * 1000);
  Serial.println("Completed elevator one rotation!");
}

// Force Elevator 2 to rotate for t seconds
void elevatorTwoRotate(int t) {
  digitalWrite(RELAY_2, LOW);
  delay(t * 1000);
  Serial.println("Completed elevator two rotation!");
}

// Force Elevator 3 to rotate for t seconds
void elevatorThreeRotate(int t) {
  digitalWrite(RELAY_3, LOW);
  delay(t * 1000);
  Serial.println("Completed elevator three rotation!");
}

// Force Elevator 4 to rotate for t seconds
void elevatorFourRotate(int t) {
  digitalWrite(RELAY_4, LOW);
  delay(t * 1000);
  Serial.println("Completed elevator four rotation!");
}

// Sensor logic for Elevator 1
void elevatorOne() {
 int magnetState = digitalRead(MAGNET_1);
 if(magnetState == HIGH) {
   digitalWrite(RELAY_1, LOW);
 } else {
   digitalWrite(RELAY_1, HIGH);
 }
}

// Sensor logic for Elevator 2
void elevatorTwo() {
 int magnetState = digitalRead(MAGNET_2);
 if(magnetState == HIGH) {
   digitalWrite(RELAY_2, LOW);
 } else {
   digitalWrite(RELAY_2, HIGH);
 }
}

// Sensor logic for Elevator 3
void elevatorThree() {
 int magnetState = digitalRead(MAGNET_3);
 if(magnetState == HIGH) {
   digitalWrite(RELAY_3, LOW);
 } else {
   digitalWrite(RELAY_3, HIGH);
 }
}

// Sensor logic for Elevator 4
void elevatorFour() {
 int magnetState = digitalRead(MAGNET_4);
 if(magnetState == HIGH) {
   digitalWrite(RELAY_4, LOW);
 } else {
   digitalWrite(RELAY_4, HIGH);
 }
}
