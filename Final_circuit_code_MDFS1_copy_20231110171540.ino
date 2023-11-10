// Define motor control pins (adjust based on your motor driver and wiring)
#include <Servo.h>

const int enablePinSP = 10; // PWM pin for motor speed control
const int in1PinSP = 30;    // Input 1
const int in2PinSP = 31;    // Input 2

const int enablePinTP = 9; // PWM pin for motor speed control
const int in1PinTP = 32;    // Input 1
const int in2PinTP = 33;    // Input 2

const int enablePinSA = 8; // PWM pin for motor speed control
const int in1PinSA = 34;    // Input 1
const int in2PinSA = 35;    // Input 2

const int enablePinTA = 7; // PWM pin for motor speed control
const int in1PinTA = 36;    // Input 1
const int in2PinTA = 37;    // Input 2

Servo servoSquash;
Servo servoTennis;

int servoSquashPin = 12 ;
int servoTennisPin = 13 ;



int posS = 0;
int posT = 0;


// int squash_picking_seconds = 2000;
// int squash_wait_seconds = 2000;

int squash_picker_state = 0;
int tennis_picker_state = 0;
int squash_arm_state = 0;
int tennis_arm_state = 0;
int main_state = 0;

unsigned long currentMillis;
unsigned long squashPickingMillis;
unsigned long squashWaitingMillis;
unsigned long squashComingBackMillis;

unsigned long forwardArmMillis;
unsigned long backArmMillis;
unsigned long latchCloseMillis;
unsigned long latchOpenMillis;
unsigned long mainMillis;


void setup() {
  // Set the motor control pins as outputs
  servoSquash.attach(servoSquashPin);
  servoTennis.attach(servoTennisPin);

  pinMode(enablePinSP, OUTPUT);
  pinMode(in1PinSP, OUTPUT);
  pinMode(in2PinSP, OUTPUT);

   pinMode(enablePinTP, OUTPUT);
  pinMode(in1PinTP, OUTPUT);
  pinMode(in2PinTP, OUTPUT);

   pinMode(enablePinSA, OUTPUT);
  pinMode(in1PinSA, OUTPUT);
  pinMode(in2PinSA, OUTPUT);

   pinMode(enablePinTP, OUTPUT);
  pinMode(in1PinTP, OUTPUT);
  pinMode(in2PinTP, OUTPUT);

  Serial.begin(9600);
}

// void open_latch(){


// }


// void close_latch(){


// }


void squash_ball_picker(){
  
  // squash_picker_state = 1;
    // Serial.println(squash_picker_state);
    switch(squash_picker_state){
      case 0:
      squashPickingMillis = currentMillis;
      squash_picker_state = 1;
      // Serial.println("Howdy");
      break;
      case 1:
        digitalWrite(in1PinSP, LOW);
        digitalWrite(in2PinSP, HIGH);
        //  Serial.println("my");
        analogWrite(enablePinSP,100); // 255 is full speed
        if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
          squashWaitingMillis = currentMillis;
          squash_picker_state = 2;
        }
      break;
      case 2:
        analogWrite(enablePinSP, 0);
        // delay(1000);
        // Serial.println("2");
        if (currentMillis - squashWaitingMillis >= 2000){ // Duration the picker waits
          squashComingBackMillis = currentMillis;
          squash_picker_state = 3;
        }
      break;
      case 3:
        digitalWrite(in1PinSP, HIGH);
        digitalWrite(in2PinSP, LOW);
        analogWrite(enablePinSP, 100);
        // Serial.println("3333333333333333333333333333");
        // delay(2000);
        if (currentMillis - squashComingBackMillis >= 3000){ // Duration the picker moves back upwards
          squashWaitingMillis = currentMillis;
          squash_picker_state = 4;
        }
        break;
      case 4:
        analogWrite(enablePinSP, 0);
        if (currentMillis - squashWaitingMillis >= 2000){
          squashPickingMillis = currentMillis;
          squash_picker_state = 5;
        }
        break;  
      case 5:
        digitalWrite(in1PinSP, LOW);
        digitalWrite(in2PinSP, HIGH);
        analogWrite(enablePinSP,100);
        if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
        squashPickingMillis = currentMillis;
        squash_picker_state = 7;
        }
        break;
      // case 6:
      //   digitalWrite(in1PinSP, HIGH);
      //   digitalWrite(in2PinSP, LOW);
      //   analogWrite(enablePinSP,100);
      //   if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
      //   squashPickingMillis = currentMillis;
      //   }
      //   break;
        case 6:
        analogWrite(enablePinSP,0);
        break;
    }

  
 }

 void tennis_ball_picker (){
   // squash_picker_state = 1;
    Serial.println(tennis_picker_state);
    switch(tennis_picker_state){
      case 0:
      squashPickingMillis = currentMillis;
      tennis_picker_state = 1;
      break;
      case 1:
        digitalWrite(in1PinTP, LOW);
        digitalWrite(in2PinTP, HIGH);
        analogWrite(enablePinTP,100); // 255 is full speed
        if (currentMillis - squashPickingMillis >= 3200){   // Duration the picker moves towards the balls
          squashWaitingMillis = currentMillis;
          tennis_picker_state = 2;
        }
      break;
      case 2:
        analogWrite(enablePinTP, 0);
        // delay(1000);
  
        if (currentMillis - squashWaitingMillis >= 2150){ // Duration the picker waits
          squashComingBackMillis = currentMillis;
          tennis_picker_state = 3;
        }
      break;
      case 3:
        digitalWrite(in1PinTP, HIGH);
        digitalWrite(in2PinTP, LOW);
        analogWrite(enablePinTP, 100);
        // delay(2000);
        if (currentMillis - squashComingBackMillis >= 3200){ // Duration the picker moves back upwards
          squashWaitingMillis = currentMillis;
          tennis_picker_state = 4;
        }
        break;
      case 4:
        analogWrite(enablePinTP, 0);
        if (currentMillis - squashWaitingMillis >= 2150){
          squashPickingMillis = currentMillis;
          tennis_picker_state = 5;
        }
        break;  
      // case 5:
      //   digitalWrite(in1PinTP, LOW);
      //   digitalWrite(in2PinTP, HIGH);
      //   analogWrite(enablePinTP,100);
      //   if (currentMillis - squashPickingMillis >= 15000){   // Duration the picker moves towards the balls
      //   squashPickingMillis = currentMillis;
      //   tennis_picker_state = 6;
      //   }
      //   break;
      case 5:
        digitalWrite(in1PinTP, LOW);
        digitalWrite(in2PinTP, HIGH);
        analogWrite(enablePinTP,100);
        if (currentMillis - squashPickingMillis >= 3000){   // Duration the picker moves towards the balls
        squashPickingMillis = currentMillis;
        }
        break;
      case 7:
      analogWrite(enablePinTP,0);
      break;
    }

 }




 void tennis_ball_extendable_arm (){
   // squash_picker_state = 1;
    // Serial.println(tennis_picker_state);
    switch(tennis_arm_state){
      case 0:
      forwardArmMillis = currentMillis;
      tennis_arm_state = 1;
      break;
      case 1:
        digitalWrite(in1PinTA, LOW);
        digitalWrite(in2PinTA, HIGH);
        analogWrite(enablePinTA,80); // 255 is full speed
        if (currentMillis - forwardArmMillis >= 3000){   // Duration the picker moves towards the balls
          latchOpenMillis = currentMillis;
          tennis_arm_state = 2;
        }
      break;
      case 2:  // SERVO MOTOR OPENING
        analogWrite(enablePinTA, 0);
        servoTennis.write(90);
        // delay(1000);
  
        if (currentMillis - latchOpenMillis >= 2500){ // Duration the picker waits
          latchCloseMillis = currentMillis;
          tennis_arm_state = 3;
        }
      break;
      case 3: //SERVO MOTOR CLOSING
        // digitalWrite(in1PinTA, HIGH);
        // digitalWrite(in2PinTA, LOW);
        analogWrite(enablePinTA, 0);
        servoTennis.write(0);

        // delay(2000);
        if (currentMillis - latchCloseMillis >= 1000){ // Duration the picker moves back upwards
          backArmMillis = currentMillis;
          tennis_arm_state = 4;
        }
        break;
      case 4:
        // analogWrite(enablePinTA, 0);
        digitalWrite(in1PinTA, HIGH);
        digitalWrite(in2PinTA, LOW);
        analogWrite(enablePinTA,80);
        if (currentMillis - backArmMillis >= 2400){
          // squashPickingMillis = currentMillis;
          tennis_arm_state = 5;
        }
        break;  
        case 5:
        analogWrite(enablePinTA, 0);
        break;
      
    }

 }

 void squash_ball_extendable_arm (){
   // squash_picker_state = 1;
    // Serial.println(tennis_picker_state);
    switch(squash_arm_state){
      case 0:
      forwardArmMillis = currentMillis;
      squash_arm_state = 1;
      break;
      case 1:
        digitalWrite(in1PinSA, LOW);
        digitalWrite(in2PinSA, HIGH);
        analogWrite(enablePinSA,80); // 255 is full speed
        if (currentMillis - forwardArmMillis >= 2500){   // Duration the picker moves towards the balls
          latchOpenMillis = currentMillis;
          squash_arm_state = 2;
        }
      break;
      case 2:  // SERVO MOTOR OPENING
        analogWrite(enablePinSA, 0);
        servoSquash.write(90);
        // delay(1000);
  
        if (currentMillis - latchOpenMillis >= 2500){ // Duration the picker waits
          latchCloseMillis = currentMillis;
          squash_arm_state = 3;
        }
      break;
      case 3: //SERVO MOTOR CLOSING
        servoSquash.write(0);
        analogWrite(enablePinSA, 0);
        if (currentMillis - latchCloseMillis >= 1000){ // Duration the picker moves back upwards
          backArmMillis = currentMillis;
          squash_arm_state = 4;
        }
        break;
      case 4:
        // analogWrite(enablePinTA, 0);
        digitalWrite(in1PinSA, HIGH);
        digitalWrite(in2PinSA, LOW);
        analogWrite(enablePinSA,80);
        if (currentMillis - backArmMillis >= 1900){
          // squashPickingMillis = currentMillis;
          squash_arm_state = 5;
        }
        break;  
        case 5:
        analogWrite(enablePinSA, 0);
        break;
      
    }

 }


void loop() {
 
  currentMillis = millis();

  switch(main_state){
    case 0:
    mainMillis = currentMillis;
    main_state = 1;
    break;
    case 1:
    squash_ball_picker();
    if (currentMillis - mainMillis >= 15000){
        mainMillis = currentMillis;
        main_state = 2;
      }
    break;
    case 2:
    squash_ball_extendable_arm();
    if (currentMillis - mainMillis >= 8900){
        mainMillis = currentMillis;
        main_state = 3;
      }
    break;
    case 3:
      digitalWrite(in1PinSP, LOW);
      digitalWrite(in2PinSP, HIGH);
      analogWrite(enablePinSP,100);
        if (currentMillis - squashPickingMillis >= 2500){   // Duration the picker moves towards the balls
        mainMillis = currentMillis;
        main_state = 4;
        }
        break;
    case 4:
    tennis_ball_picker();
    if (currentMillis - mainMillis >= 14700){
        mainMillis = currentMillis;
        main_state = 5;
      }
    break;
    case 5:
    tennis_ball_extendable_arm();
    if (currentMillis - mainMillis >= 9900){
        mainMillis = currentMillis;
        main_state = 6;
      }
    break;
    case 6:
    digitalWrite(in1PinTP, LOW);
      digitalWrite(in2PinTP, HIGH);
      analogWrite(enablePinTP,100);
        if (currentMillis - squashPickingMillis >= 2700){   // Duration the picker moves towards the balls
        mainMillis = currentMillis;
        main_state = 7;
        }
    break;
    case 7:
    analogWrite(enablePinSA, 0);
    analogWrite(enablePinTA, 0);
    analogWrite(enablePinSP, 0);
    analogWrite(enablePinTP, 0);
    break;
  }

 

  
}

