//IR Sensor ports
const int farLeftSensor = A0;
const int leftSensor = A1;
const int midSensor = A2;
const int rightSensor = A3;
const int farRightSensor = A4;

// 7-segment display ports
#define A 0
#define B 5
#define C 4
#define D 2
#define E 8
#define F 1
#define G 9
const int leftDisplay = 7;
const int rightDisplay = 6;
int crossingsCounter = 0;
char wentDirection = '0';
bool finished = false;

bool segMode = false;
int seg[] {A, B, C, D, E, F, G};
byte chars = 34;

byte Chars[34][9] {
  {'0', 1, 1, 1, 1, 1, 1, 0}, //0
  {'1', 0, 1, 1, 0, 0, 0, 0}, //1
  {'2', 1, 1, 0, 1, 1, 0, 1}, //2
  {'3', 1, 1, 1, 1, 0, 0, 1}, //3
  {'4', 0, 1, 1, 0, 0, 1, 1}, //4
  {'5', 1, 0, 1, 1, 0, 1, 1}, //5
  {'6', 1, 0, 1, 1, 1, 1, 1}, //6
  {'7', 1, 1, 1, 0, 0, 0, 0}, //7
  {'8', 1, 1, 1, 1, 1, 1, 1}, //8
  {'9', 1, 1, 1, 1, 0, 1, 1}, //9
  {'a', 1, 1, 1, 0, 1, 1, 1}, //A
  {'b', 0, 0, 1, 1, 1, 1, 1}, //b
  {'c', 1, 0, 0, 1, 1, 1, 0}, //C
  {'d', 0, 1, 1, 1, 1, 0, 1}, //d
  {'e', 1, 0, 0, 1, 1, 1, 1}, //E
  {'f', 1, 0, 0, 0, 1, 1, 1}, //F
  {'g', 1, 0, 1, 1, 1, 1, 0}, //G
  {'h', 0, 1, 1, 0, 1, 1, 1}, //H
  {'i', 0, 0, 0, 0, 1, 1, 0}, //I
  {'j', 0, 1, 1, 1, 1, 0, 0}, //J
  {'l', 0, 0, 0, 1, 1, 1, 0}, //L
  {'n', 0, 0, 1, 0, 1, 0, 1}, //n
  {'o', 0, 0, 1, 1, 1, 0, 1}, //o
  {'p', 1, 1, 0, 0, 1, 1, 1}, //P
  {'q', 1, 1, 1, 0, 0, 1, 1}, //q
  {'r', 0, 0, 0, 0, 1, 0, 1}, //r
  {'s', 1, 0, 1, 1, 0, 1, 1}, //S
  {'t', 0, 0, 0, 1, 1, 1, 1}, //t
  {'u', 0, 1, 1, 1, 1, 1, 0}, //U
  {'y', 0, 1, 1, 1, 0, 1, 1}, //y
  {'-', 0, 0, 0, 0, 0, 0, 1}, //-
  {']', 1, 1, 1, 1, 0, 0, 0}, //]
  {'[', 1, 0, 0, 1, 1, 1, 0}, //[
  {'_', 0, 0, 0, 1, 0, 0, 0}, //_
};

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

  //Setup 7-segment display
  pinMode(seg[0], OUTPUT);
  pinMode(seg[1], OUTPUT);
  pinMode(seg[2], OUTPUT);
  pinMode(seg[3], OUTPUT);
  pinMode(seg[4], OUTPUT);
  pinMode(seg[5], OUTPUT);
  pinMode(seg[6], OUTPUT);
  pinMode(leftDisplay, OUTPUT);
  pinMode(rightDisplay, OUTPUT);
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
    analogWrite(leftSpeed, speed); ++++695
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

if (!finished) {
  digitalWrite(rightDisplay, HIGH); // Turn right display off
  digitalWrite(leftDisplay, LOW); // Turn left display on
  Print(crossingsCounter);
  delay(5);
  digitalWrite(leftDisplay, HIGH); // Turn left display off
  digitalWrite(rightDisplay, LOW); // Turn right display on
  Print(wentDirection);
  delay(5);
} else {
  digitalWrite(rightDisplay, HIGH);
  digitalWrite(leftDisplay, LOW);
  Print('f');
  delay(5);
  digitalWrite(leftDisplay, HIGH);
  digitalWrite(rightDisplay, LOW);
  Print('i');
  delay(5);
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

//Reset 7-segment display
void setState(bool mode) {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(seg[i], mode);
  }
}

//Print char on display
void Print(char Char) {
  int charNum = -1;
  setState(segMode);
  for (int i = 0; i < chars ; i++) {
    if (Char == Chars[i][0]) {
      charNum = i;
    }
  }

  if (charNum == -1 ) {
    for (int i = 0; i <= 6; i++) {
      digitalWrite(seg[i], HIGH);
      delay(100);
      digitalWrite(seg[i], LOW);
    }
    for (int i = 0; i <= 2; i++) {
      delay(100);
      setState(HIGH);
      delay(100);
      setState(LOW);
    }
  } else {
    for (int i = 0; i < 7; i++) {
      digitalWrite(seg[i], Chars[charNum][i + 1]);
    }
  }
}

//Print int on display
void Print(int num) {
  setState(segMode);
  if (num > chars || num < 0 ) {
    for (int i = 0; i <= 6; i++) {
      digitalWrite(seg[i], HIGH);
      delay(100);
      digitalWrite(seg[i], LOW);
    }

    for (int i = 0; i <= 2; i++) {
      delay(100);
      setState(HIGH);
      delay(100);
      setState(LOW);
    }
  } else {
    if (segMode == 0) {
      for (int i = 0; i < 7; i++) {
        digitalWrite(seg[i], Chars[num][i + 1]);
      }
    } else {
      for (int i = 0; i < 7; i++) {
        digitalWrite(seg[i], !Chars[num][i + 1]);
      }
    }
  }
}
