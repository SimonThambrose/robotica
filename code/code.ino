//INT FRONT IR SENSOR
const int farLeftSensor = A0;
const int leftSensor = A1;
const int midSensor = A2;
const int rightSensor = A3;
const int farRightSensor = A4;

//INT MOTORS
int leftDirection = 4;   //Motor left direction     HIGH/LOW
int leftSpeed = 5;       //Motor left speed             0-255
int rightSpeed = 6;      //Motor right speed           HIGH/LOW
int rightDirection = 7;  //Motor right direction   0-255



void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000111;
  Serial.begin(9600);

  //SETUP IR SENSOR
  pinMode(farLeftSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(farRightSensor, INPUT);

  //SETUP RIGHT MOTOR
  pinMode(rightDirection, OUTPUT);  //INITIATES DIRECTION OF RIGHT MOTOR. LOW TO MOVE FORWARD

  //SETUP LEFT MOTOR
  pinMode(leftDirection, OUTPUT);  //INITIATES DIRECTION OF LEFT MOTOR. LOW TO MOVE FORWARD
}



void loop() {
  int sens[] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };

  String str = String(sens[0]) + " " + String(sens[1]) + " " + String(sens[2]) + " " + String(sens[3]) + " " + String(sens[4]);
  Serial.println(str);

  //STRAIGHT
  if (sens[0] && sens[1] && !sens[2] && sens[3] && sens[4]) {
    straight();
  }

  //TURN AROUND
  else if (sens[0] && sens[1] && sens[2] && sens[3] && sens[4]) {
    turnAround();
  }

  //LEFT
  else if (!sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) {
    left();
  }

  //RIGHT
  else if (sens[0] && sens[1] && sens[2] && !sens[3] && !sens[4]) {
    right();
  }

  //LEFT OR RIGHT
  else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    leftRight();
  }

  //STRAIGHT OR LEFT
  else if (!sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
    straightLeft();
  }

  //STRAIGHT OR RIGHT
  else if (sens[0] && sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    straightRight();
  }

  //SMALL ADJUSTMENT LEFT
  else if (sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
    lightLeft();
  }

  //STRONG ADJUSTMENT LEFT
  else if (sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) {
    strongLeft();
  }

  //SMALL ADJUSTMENT RIGHT
  else if (sens[0] && sens[1] && !sens[2] && !sens[3] && sens[4]) {
    lightRight();
  }

  //STRONG ADJUSTMENT RIGHT
  else if (sens[0] && sens[1] && sens[2] && !sens[3] && sens[4]) {
    strongRight();
  }

  //FINISH
  else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    finish();
  }
}


//Functions
//STRAIGHT
void straight() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 75);

  Serial.println("Straight");
  delay(25);
}

//TURN AROUND
void turnAround() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 75);

  Serial.println("Turn Around");
  delay(25);
}

//LEFT
void left() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 75);

  Serial.println("Left");
  delay(25);
}

//RIGHT
void right() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 75);

  Serial.println("Right");
  delay(25);
}

//LeEFT OR RIGHT
void leftRight() {
  digitalWrite(rightDirection, LOW);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Left or right");
  delay(25);
}

//STRAIGHT OR LEFT
void straightLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Straight or left");
  delay(25);
}

//STRAIGHT OR RIGHT
void straightRight() {

  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Straight or right");
  delay(25);
}

//SMALL ADJUSTMENT LEFT
void lightLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 35);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Light left");
  delay(25);
}

//STRONG ADJUSTMENT LEFT
void strongLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 45);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Strong left");
  delay(25);
}

//SMALL ADJUSTMENT RIGHT
void lightRight() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 35);

  Serial.println("Light right");
  delay(25);
}

//STRONG ADJUSTMENT RIGHT
void strongRight() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 45);

  Serial.println("Strong right");
  delay(25);
}

//FINISH
void finish() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 0);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 0);

  Serial.println("Finish");
  delay(25);
}