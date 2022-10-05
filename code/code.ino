//Int IR Sensor
const int farLeftSensor = A0;
const int leftSensor = A1;
const int midSensor = A2;
const int rightSensor = A3;
const int farRightSensor = A4;

int leftDirection = 4; //Motor left direction
int leftSpeed = 5; //Motor left speed
int rightSpeed = 6; //Motor right speed
int rightDirection = 7; //Motor right direction

void setup() {

  Serial.begin(9600);

  //Setup IR Sensor
  pinMode(farLeftSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(farRightSensor, INPUT);

  //Setup right engine
  pinMode(rightDirection, OUTPUT); //Initiates direction right motor. LOW to move forward

  //Setup left engine
  pinMode(leftDirection, OUTPUT);  //Initiates direction left motor. HIGH to move forward LOW to move backward
}

void loop() {

  int sens [] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };

  String str = String(sens[0]) + " " + String(sens[1]) + " " + String(sens[2]) + " " + String(sens[3]) + " " + String(sens[4]);
  Serial.println(str);

  //Straight
  if (sens[0] && sens[1] && !sens[2] && sens[3] && sens[4]) {
    straight();
  }

  //Turn around
  else if (sens[0] && sens[1] && sens[2] && sens[3] && sens[4]) {
    turnAround();
  }

  //Left
  else if (!sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) {
    left();
  }

  //Right
  else if (sens[0] && sens[1] && sens[2] && !sens[3] && !sens[4]) {
    right();
  }

  //Left or right
  else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    leftRight();
  }

  //Straight or left
  else if (!sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
    straightLeft();
  }

  //Straight or right
  else if (sens[0] && sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    straightRight();
  }

  //Light left
  else if (sens[0] && !sens[1] && !sens[2] && sens[3] && sens[4]) {
    lightLeft();
  }

  //Strong left
  else if (sens[0] && !sens[1] && sens[2] && sens[3] && sens[4]) {
    strongLeft();
  }

  //Light Right
  else if (sens[0] && sens[1] && !sens[2] && !sens[3] && sens[4]) {
    lightRight();
  }

  //Strong right
  else if (sens[0] && sens[1] && sens[2] && !sens[3] && sens[4]) {
    strongRight();
  }

  //Finish
  else if (!sens[0] && !sens[1] && !sens[2] && !sens[3] && !sens[4]) {
    finish();
  } 
}





//Functions
//Straight-------------------------------------------
void straight() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 75);

  Serial.println("Straight");
  delay(25);
}

//Turn around----------------------------------------
void turnAround() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 75);

  Serial.println("Turn Around");
  delay(25);
}

//Left-----------------------------------------------
void left() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 75);

  Serial.println("Left");
  delay(25);
}

//Right---------------------------------------------
void right() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 75);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 75);

  Serial.println("Right");
  delay(25);
}

//Left or right-------------------------------------
void leftRight() {
  digitalWrite(rightDirection, LOW);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);
  
  Serial.println("Left or right");
  delay(25);
}

//Straight or left----------------------------------
void straightLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Straight or left");
  delay(25);
}

//Straight or right---------------------------------
void straightRight() {

  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Straight or right");
  delay(25);
}

//Light left-----------------------------------------
void lightLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 35);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Light left");
  delay(25);
}

//Strong left----------------------------------------
void strongLeft() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 45);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 25);

  Serial.println("Strong left");
  delay(25);
}

//Light right----------------------------------------
void lightRight() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 35);

  Serial.println("Light right");
  delay(25);
}

//Strong right---------------------------------------
void strongRight() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 25);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 45);

  Serial.println("Strong right");
  delay(25);
}

//Finish---------------------------------------------
void finish() {
  digitalWrite(rightDirection, HIGH);
  digitalWrite(rightSpeed, 0);

  digitalWrite(leftDirection, LOW);
  digitalWrite(leftSpeed, 0);

  Serial.println("Finish");
  delay(25);
}
