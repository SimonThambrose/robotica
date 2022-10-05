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

  TCCR0B = TCCR0B & B11111000 | B00000001;
}

void loop() {
  int sens [] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };

  if (!kickstart) {
    kickStart();
  }

  analogWrite(rightSpeed, 0);
  analogWrite(leftSpeed, 0);
}

void kickStart() {
  digitalWrite(rightDirection, LOW);
  analogWrite(rightSpeed, 255);
  digitalWrite(leftDirection, LOW);
  analogWrite(leftSpeed, 255);
  delay(100);
  kickstart = true;
}
