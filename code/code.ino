// IR Sensor ports
const int farLeftSensor = A0;
const int leftSensor = A1;
const int midSensor = A2;
const int rightSensor = A3;
const int farRightSensor = A4;

// Motor ports
int rightDirection = 12;
int rightSpeed = 3;
int leftSpeed = 11;
int leftDirection = 13;

// Kick start motor boolean
bool kickstart = false;

void setup() {
  Serial.begin(9600);

  //Setup IR Sensor
  pinMode(farLeftSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(farRightSensor, INPUT);

  //Setup right engine
  pinMode(rightDirection, OUTPUT); // Initiates direction right motor. LOW to move forward, HIGH to move backwards.
  pinMode(rightSpeed, OUTPUT); // Initiates power value right motor (25%=64; 50%=127; 75% = 191; 100%=255).

  //Setup left engine
  pinMode(leftDirection, OUTPUT);  // Initiates direction left motor. LOW to move forward, HIGH to move backwards.
  pinMode(leftSpeed, OUTPUT); // Initiates power value left motor (25%=64; 50%=127; 75% = 191; 100%=255).
}

void loop() {
  int sens [] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };

  if (!kickstart) {
    kickStart();
  }

  // -- Test for sensor output values --
  // String str = String(sens[0]) + " " + String(sens[1]) + " " + String(sens[2]) + " " + String(sens[3]) + " " + String(sens[4]);
  // Serial.println(str);

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
//Kickstart-------------------------------------------
void kickStart() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 255);
  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 255);
  delay(100);
  kickstart = true;
}
//Straight-------------------------------------------
void straight() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 40);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 40);

  Serial.println("Straight");
  delay(25);
}

//Turn around----------------------------------------
void turnAround() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 40);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 40);

  Serial.println("Turn Around");
  delay(25);
}

//Left-----------------------------------------------
void left() {
  digitalWrite(rightDirection, HIGH);
  analogWrite(rightSpeed, 40);

  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 40);

  Serial.println("Left");
  delay(25);
}

//Right---------------------------------------------
void right() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 40);

  digitalWrite(leftDirection, HIGH);
  analogWrite(leftSpeed, 40);

  Serial.println("Right");
  delay(25);
}

//Finish---------------------------------------------
void finish() {
  digitalWrite(rightSpeed, 0);

  digitalWrite(leftSpeed, 0);

  Serial.println("Finish");
  delay(25);
}
