// Define motor control pins (adjust based on your motor driver and wiring)
const int enablePin = 9; // PWM pin for motor speed control
const int in1Pin = 6;    // Input 1
const int in2Pin = 7;    // Input 2

// int squash_picking_seconds = 2000;
// int squash_wait_seconds = 2000;

int squash_picker_state = 1;

unsigned long currentMillis;
unsigned long squashPickingMillis;
unsigned long squashWaitingMillis;
unsigned long squashComingBackMillis;


void setup() {
  // Set the motor control pins as outputs
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  Serial.begin(9600);
}


void squash_ball_picker(){
  
  // squash_picker_state = 1;
    Serial.println(squash_picker_state);
    switch(squash_picker_state){
      case 0:
      squashPickingMillis = currentMillis;
      squash_picker_state = 1;
      Serial.println("Howdy");
      break;
      case 1:
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
         Serial.println("my");
        analogWrite(enablePin,100); // 255 is full speed
        if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
          squashWaitingMillis = currentMillis;
          squash_picker_state = 2;
        }
      break;
      case 2:
        analogWrite(enablePin, 0);
        // delay(1000);
        Serial.println("2");
        if (currentMillis - squashWaitingMillis >= 2000){ // Duration the picker waits
          squashComingBackMillis = currentMillis;
          squash_picker_state = 3;
        }
      break;
      case 3:
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enablePin, 100);
        Serial.println("3333333333333333333333333333");
        // delay(2000);
        if (currentMillis - squashComingBackMillis >= 3000){ // Duration the picker moves back upwards
          squashWaitingMillis = currentMillis;
          squash_picker_state = 4;
        }
        break;
      case 4:
        analogWrite(enablePin, 0);
        if (currentMillis - squashWaitingMillis >= 2000){
          squashPickingMillis = currentMillis;
          squash_picker_state = 5;
        }
        break;  
      case 5:
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(enablePin,100);
        if (currentMillis - squashPickingMillis >= 15000){   // Duration the picker moves towards the balls
        squashPickingMillis = currentMillis;
        squash_picker_state = 6;
        }
        break;
      case 6:
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enablePin,150);
        if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
        squashPickingMillis = currentMillis;
        }
        break;
    }

  
 }


void loop() {
  // Rotate the motor clockwise at full speed for 2 seconds
  currentMillis = millis();

  squash_ball_picker();

  
}

