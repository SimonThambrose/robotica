//IR Sensor ports
const int farLeftSensor = A0;
const int leftSensor = A1;
const int midSensor = A2;
const int rightSensor = A3;
const int farRightSensor = A4;

//Motor ports
int leftDirection = 12;
int rightSpeed = 3;
int leftSpeed = 11;
int rightDirection = 13;

//Kickstart motor boolean
bool kickstart = false;

//Speed of the robot
int speed = 22;

//Speed in corners
int cornerSpeed = 30;

//Choices for reversing/turning around etc
int timesReversed = 0;

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000111;

  //Setup IR sensor
  pinMode(farLeftSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(farRightSensor, INPUT);

  //Setup right motor
  pinMode(leftDirection, OUTPUT); // Initiates direction right motor. LOW to move forward, HIGH to reverse.
  pinMode(rightSpeed, OUTPUT); // Initiates power value right motor (speed%=64; 50%=127; 75% = 191; 100%=speed5).

  //Setup left motor
  pinMode(rightDirection, OUTPUT);  // Initiates direction left motor. LOW to move forward, HIGH to reverse
  pinMode(leftSpeed, OUTPUT); // Initiates power value left motor (speed%=64; 50%=127; 75% = 191; 100%=speed5).
}

void loop() {
  int sens [] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };

  // if (!kickstart) {
  //   kickStart();
  // }

  // -- Test for sensor output values --
  // String str = String(sens[0]) + " " + String(sens[1]) + " " + String(sens[2]) + " " + String(sens[3]) + " " + String(sens[4]);

  //Straight
  if ((sens[0] && sens[1] && !sens[2] && sens[3] && sens[4]) || (sens[0] && !sens[1] && !sens[2] && !sens[3] && sens[4])) {
    straight();
  }

  //Reverse or Turn around
  else if (sens[0] && sens[1] && sens[2] && sens[3] && sens[4]) {
    turnAround();
  }

  //Left
  else if ((!sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) || (!sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) || (!sens[0] && !sens[1] && !sens[2] && !sens[3] && sens[4])) {
    left();
  }

  //Right
  else if ((sens[0] && sens[1] && !sens[2] && !sens[3] && !sens[4]) || (sens[0] && sens[1] && sens[2] && !sens[3] && !sens[4]) || (sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4])) {
    right();
  }

//   //Left or right
//   else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
//     leftRight();
//   }

//   //Straight or left
//   else if (!sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
//     straightLeft();
//   }

//   //Straight or right
//   else if (sens[0] && sens[1] && !sens[2] && !sens[3] && !sens[4]) {
//     straightRight();
//   }

  //Small adjustment left
  else if (sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
    lightLeft();
  }

  //Strong adjustment left
  else if (sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) {
    strongLeft();
  }

  //Small adjustment right
  else if (sens[0] && sens[1] && !sens[2] && !sens[3] && sens[4]) {
    lightRight();
  }

  //Strong adjustment right
  else if (sens[0] && sens[1] && sens[2] && !sens[3] && sens[4]) {
    strongRight();
  }

//   //Finish
//   else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
//     finish();
//   }

    else {
      stop();
    }
}


// //Functions
// //Kickstart
// void kickStart() {
//   digitalWrite(leftDirection, LOW);
//   analogWrite(rightSpeed, speed5);
//   digitalWrite(rightDirection, LOW);
//   analogWrite(leftSpeed, speed5);
//   delay(10);
//   kickstart = true;
// }

//Straight
void straight() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, speed);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, speed);

  delay(200);
}

//Reverse or Turn around
void turnAround() {
  if (timesReversed < 3) {
    digitalWrite(leftDirection, HIGH);
    analogWrite(rightSpeed, speed);
    digitalWrite(rightDirection, HIGH);
    analogWrite(leftSpeed, speed);++++695
    timesReversed ++;
    delay(500);
  }
  else {
    digitalWrite(leftDirection, LOW);
    analogWrite(rightSpeed, cornerSpeed);
    digitalWrite(rightDirection, HIGH);
    analogWrite(leftSpeed, cornerSpeed);
    timesReversed = 0;
    delay(200);
  }
}

//Left
void left() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, 0);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, cornerSpeed);
  delay(200);
}

//Right
void right() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, cornerSpeed);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, 0);
  delay(200);
}

// //Left or right
// void leftRight() {
//   digitalWrite(leftDirection, LOW);
//   analogWrite(rightSpeed, 20);
//   digitalWrite(rightDirection, LOW);
//   analogWrite(leftSpeed, 20);
//   delay(500);
// }

// //Straight or left
// void straightLeft() {
//   digitalWrite(leftDirection, HIGH);
//   analogWrite(rightSpeed, 20);
//   digitalWrite(rightDirection, LOW);
//   analogWrite(leftSpeed, 20);
//   delay(500);
// }

// //Straight or right
// void straightRight() {
//   digitalWrite(leftDirection, HIGH);
//   analogWrite(rightSpeed, 20);
//   digitalWrite(rightDirection, LOW);
//   analogWrite(leftSpeed, 20);
//   delay(500);
// }

//Small adjustment left
void lightLeft() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, 0);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, cornerSpeed);
  delay(200);
}

//Strong adjustment left
void strongLeft() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, 0);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, cornerSpeed);
  delay(200);
}

//Light adjustment right
void lightRight() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, cornerSpeed);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, 0);
  delay(200);
}

//Strong adjustment right
void strongRight() {
  digitalWrite(leftDirection, LOW);
  analogWrite(rightSpeed, cornerSpeed);
  digitalWrite(rightDirection, LOW);
  analogWrite(leftSpeed, 0);
  delay(200);
}

// //Finish
// void finish() {
//   analogWrite(rightSpeed, 0);
//   analogWrite(leftSpeed, 0);
//   delay(1000);
// }

//Stop
void stop() {
  analogWrite(rightSpeed, 0);
  analogWrite(leftSpeed, 0);
  delay(1000);
}
