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

bool emergencyStop = false;

// SerialEvent
String inputString = "";
boolean stringComplete = false;

// Start timer
unsigned long currentMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;

// Number of seconds to rotate pods
int rotate1 = 0;
int rotate2 = 0;
int rotate3 = 0;
int rotate4 = 0;

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

  inputString.reserve(200);
}

void loop(void) {
  currentMillis = millis();
  
  if (stringComplete) {
    parseInput();
    inputString = "";
    stringComplete = false;
  }
  else {
    elevatorOne();
    elevatorTwo();
    elevatorThree();
    elevatorFour();
  }
}

void serialEvent() {  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

// Read serial input
String readInput() {
  // Grab input
  // Input MUST be in the following format: #;#;#;#;
  // Where # can be any integer as seconds
  String input = Serial.readString();
  return input;
}

// Parse serial input
void parseInput() {
  // Stop elevators if input is "stop" by setting emergencyStop to true
  if (inputString == "stop") {
    //Serial.println("Stopping");
    emergencyStop = true;
  }
  // Start elevators again if input is "start"
  else if (inputString == "start") {
    //Serial.println("Starting");
    emergencyStop = false;
  }
  else if (inputString == "ping") {
    Serial.println("PONG");
  }
  // Rotate elevators based on input in seconds
  else if (inputString != "") {
    rotate(inputString);
  }
}

// Force elevators to rotate
void rotate(String input) {
  // Initialize counters and array to store delay time
  int substrCounter = 0;
  int arrayCounter = 0;
  int delays[4];

  // Parse input and store
  for (int i = 0; i < input.length(); i++) {
    if (input.substring(i, i + 1) == ";") {
      delays[arrayCounter] = input.substring(substrCounter, i).toInt();
      substrCounter = i + 1;
      arrayCounter++;
    }
  }

  // Elevator rotation logic
  // If all the delays are the same, rotate all elevators at once
  // Else, rotate each elevator one by one
  if (delays[0] == delays[1] && delays[0] == delays[2] && delays[0] == delays[3]) {
    //Serial.println("Rotating all pods");
    previousMillis1 = millis();
    previousMillis2 = millis();
    previousMillis3 = millis();
    previousMillis4 = millis();

    rotate1 = delays[0];
    rotate2 = delays[1];
    rotate3 = delays[2];
    rotate4 = delays[3];
  }
  else {
    //Serial.println("Rotating one pod");
    if (delays[0] > 0) {
      previousMillis1 = millis();
      rotate1 = delays[0];
    }
    if (delays[1] > 0) {
      previousMillis2 = millis();
      rotate2 = delays[1];
    }
    if (delays[2] > 0) {
      previousMillis3 = millis();
      rotate3 = delays[2];
    }
    if (delays[3] > 0) {
      previousMillis4 = millis();
      rotate4 = delays[3];
    }
  }

  // Debugging purposes
  //Serial.print("Input: ");
  //Serial.println(input);
  //Serial.print("Delay one: ");
  //Serial.println(delays[0]);
  //Serial.print("Delay two: ");
  //Serial.println(delays[1]);
  //Serial.print("Delay three: ");
  //Serial.println(delays[2]);
  //Serial.print("Delay four: ");
  //Serial.println(delays[3]);
}

// Sensor logic for Elevator 1
void elevatorOne() {
  if(emergencyStop) {
    digitalWrite(RELAY_1, HIGH);
    return;
  }
  else {
    int magnetState = digitalRead(MAGNET_1);
    if (magnetState == HIGH) {
      digitalWrite(RELAY_1, LOW);
    }
    else {  
      if (currentMillis - previousMillis1 <= 1000 * rotate1) {
        digitalWrite(RELAY_1, LOW);
      }
      else {
        digitalWrite(RELAY_1, HIGH);
      }
    }
  }
}

// Sensor logic for Elevator 2
void elevatorTwo() {
  if(emergencyStop) {
    digitalWrite(RELAY_2, HIGH);
    return;
  }
  else {
    int magnetState = digitalRead(MAGNET_2);
    if (magnetState == HIGH) {
      digitalWrite(RELAY_2, LOW);
    }
    else {
      if (currentMillis - previousMillis2 <= 1000 * rotate2) {
        digitalWrite(RELAY_2, LOW);
      }
      else {
        digitalWrite(RELAY_2, HIGH);
      }
    }
  }
}

// Sensor logic for Elevator 3
void elevatorThree() {
  if(emergencyStop) {
    digitalWrite(RELAY_3, HIGH);
    return;
  }
  else {
    int magnetState = digitalRead(MAGNET_3);
    if (magnetState == HIGH) {
      digitalWrite(RELAY_3, LOW);
    }
    else {
      if (currentMillis - previousMillis3 <= 1000 * rotate3) {
        digitalWrite(RELAY_3, LOW);
      }
      else {
        digitalWrite(RELAY_3, HIGH);
      }
    }
  }
}

// Sensor logic for Elevator 4
void elevatorFour() {
  if(emergencyStop) {
    digitalWrite(RELAY_4, HIGH);
    return;
  }
  else {
    int magnetState = digitalRead(MAGNET_4);
    if (magnetState == HIGH) {
      digitalWrite(RELAY_4, LOW);
    }
    else {
      if (currentMillis - previousMillis4 <= 1000 * rotate4) {
        digitalWrite(RELAY_4, LOW);
      }
      else {
        digitalWrite(RELAY_4, HIGH);
      }
    }
  }
}
