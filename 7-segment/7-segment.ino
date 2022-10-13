#define A 0
#define B 5
#define C 4
#define D 2
#define E 8
#define F 1
#define G 9
const int leftDisplay = 7;
const int rightDisplay = 6;
int crossingsCounter = 1;
char wentDirection = 'r';
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

void setup() {
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

void setState(bool mode) {
  for (int i = 0; i <= 6; i++) {
    digitalWrite(seg[i], mode);
  }
}

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

void loop() {
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
}
