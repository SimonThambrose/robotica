# Final assignment Robotics
<sub> By Kai Vrijenhoeff en Simon Kuperus </sub>

This Git project has been created to keep track of the code used in a final assigment of a first year's Robotics class on the Windesheim University[^1] in Zwolle.

The project contains three main Arduino files: [7-segment.ino](https://github.com/SimonThambrose/robotica/blob/dev/7-segment/7-segment.ino), [code.ino](https://github.com/SimonThambrose/robotica/blob/dev/code/code.ino) and [sandbox.ino](https://github.com/SimonThambrose/robotica/blob/dev/sandbox/sandbox.ino).
The 7-segment.ino file contains testcode for the creation of the two 7-segment displays on the robot.
The sandbox.ino is a playground used for testing code snippets or new solutions.
The code.ino file is where the final code will be tested with the physical robot, a short introduction to the code in this file will be described below.

## Direction and speed

```php
// TODO: Describe Arduino motor shield, required ports 3, 11, 12 and 13.
// TODO: Describe TCCR2B = TCCR2B & B11111000 | B00000111.
```

The `leftDirection` and `rightDirection` indicate the direction of the engine-powered wheels.
They are digitally called using `digitalWrite(<left/right>Direction, <HIGH/LOW>);`.
Use `LOW` to move forward and `HIGH` to reverse.

The `leftSpeed` and `rightSpeed` are used to assign the speed to the engines.
These are called using `analogWrite(<left/right>Speed, speed);`, where `speed` is an integer with a default value of **23**.
The engine speed can vary from **0** to a maximum value of **225**.

```php
// TODO: Describe basic usage of motor directions and speed in functions.
```

## Using the line sensor
The sensor data is initialized in the `loop()` by creating the `sens[]` array.

```cp
int sens[] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };
```

This reads all sensor data each time the code has looped and overwrites the array.

The data can be used to check each sensor output as a boolean and be used in an if-statement to execute the desired outcome.

```cp
if (sens[0] && sens[1] && !sens[2] && sens[3] && sens[4]) {
    straight(); // Calls a function which sets motors to go forward with the default speed.
}
```

The `sens[]` array can also be required to be overwritten again when entering a function which checks for a certain reading.
This can simply be done by calling the `digitalRead(<sensor>)` for each sensor again and adding them to the array.

```cp
void checkForLeft() { // Function to check for a left corner
    (...)
    int sens[] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };
    (...)
    if (sens[0] && sens[1] && sens[2] && sens[3] && sens[4]) {
        left();
    } else {
        (...)
    }
}
```

## 7-segment displays

```php
// TODO: Describe use of 7-segment displays.
```
  
  [^1]: [Study IT Windesheim University Zwolle](https://www.windesheim.nl/opleidingen/voltijd/bachelor/hbo-ict-zwolle)
