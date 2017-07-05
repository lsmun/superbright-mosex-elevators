// Elevator 1
const int MAGNET_1 = 2;
const int RELAY_1 = 28;

// Elevator 2
const int MAGNET_2 = 3;
const int RELAY_2 = 26;

// Elevator 3
const int MAGNET_3 = 4;
const int RELAY_3 = 24;

// Elevator 4
const int MAGNET_4 = 5;
const int RELAY_4 = 22;

// Variables used in Serial input reading example
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;

// Variables used in parse data example
char tempChars[numChars];
char messageFromPC[numChars] = {0};

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

 //recvWithEndMarker();
  
 // Force elevator to rotate
 //if(newData == true) {
 // rotate();
 //}
 
 //showNewData();

  if (Serial.available()) {
    Serial.println(Serial.readString());
  }
  

 // Sensor logic: If the magnets are touching, turn power off. Otherwise, turn power on.
 elevatorOne();
 elevatorTwo();
 elevatorThree();
 elevatorFour();
}

// Force elevator to rotate
void rotate() {
 
 // Rotate time per elevator
 int rotateOne;
 int rotateTwo;
 int rotateThree;
 int rotateFour;
 
 // Store input
 //Serial.print("Checkpoint #1: ");
 //Serial.println(receivedChars);

 //Serial.print("Checkpoint #2: ");
 //Serial.println(strstr(receivedChars,";"));

// if(strstr(receivedChars,";") > 0) {
//  
// }
// else {
//  int rotateAll = (receivedChars[0] - 48) * 1000;
//    Serial.println("Check point #3");
//    Serial.println(rotateAll);
// }
  
 for (int i = 0; i < sizeof(receivedChars); i++) {

  // Case where input does not have a delimiter and is 2 digits
  if(receivedChars[2] == -1) {
    int rotateAll = ((receivedChars[0] - 48) * 10 + (receivedChars[1] - 48)) * 1000;
    Serial.println("Check point #2");
    Serial.println(rotateAll);
    break;
  }
// }

// if (input[0] != -1) {
//  while (n >= 0) {
//   input[n] = -1;
//   n--;
//  }
// }
 
  //Serial.println(line);
//  int delayTimeInSec = (Serial.read() - 48) * 1000;
//  digitalWrite(RELAY_1, HIGH);
//  digitalWrite(RELAY_2, HIGH);
//  digitalWrite(RELAY_3, HIGH);
//  digitalWrite(RELAY_4, HIGH);
//  delay(delayTimeInSec);
}
}

// Function grabbed from a forum to store input
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}

// Function grabbed from forum to parse data
void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    //integerFromPC = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    //floatFromPC = atof(strtokIndx);     // convert this part to a float

}

// Sensor logic for Elevator 1
void elevatorOne() {
 int magnetState = digitalRead(MAGNET_1);
 if(magnetState == LOW) {
   digitalWrite(RELAY_1, LOW);
 } else {
   digitalWrite(RELAY_1, HIGH);
 }
}

// Sensor logic for Elevator 2
void elevatorTwo() {
 int magnetState = digitalRead(MAGNET_2);
 if(magnetState == LOW) {
   digitalWrite(RELAY_2, LOW);
 } else {
   digitalWrite(RELAY_2, HIGH);
 }
}

// Sensor logic for Elevator 3
void elevatorThree() {
 int magnetState = digitalRead(MAGNET_3);
 if(magnetState == LOW) {
   digitalWrite(RELAY_3, LOW);
 } else {
   digitalWrite(RELAY_3, HIGH);
 }
}

// Sensor logic for Elevator 4
void elevatorFour() {
 int magnetState = digitalRead(MAGNET_4);
 if(magnetState == LOW) {
   digitalWrite(RELAY_4, LOW);
 } else {
   digitalWrite(RELAY_4, HIGH);
 }
}
