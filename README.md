# Final assignment Robotics
<sub> By Kai Vrijenhoeff en Simon Kuperus </sub>

This Git project has been created to keep track of the code used in a final assigment of a first year's Robotics class on the Windesheim University[^1] in Zwolle.

The `leftDirection` and `rightDirection` indicate the direction of the engine-powered wheels.
They are digitally called using `digitalWrite(<left/right>Direction, <HIGH/LOW>);`.
Use `LOW` to move forward and `HIGH` to reverse.

The `leftSpeed` and `rightSpeed` are used to assign the speed to the engines.
These are called using `analogWrite(<left/right>Speed, speed);`, where `speed` is an integer with a default value of **23**.
The engine speed can vary from **0** to a maximum value of **225**.

The sensor data is initialized in the `loop()` with by creating the `sens[]` array shown below:
```cp
int sens[] = { digitalRead(farLeftSensor), digitalRead(leftSensor), digitalRead(midSensor), digitalRead(rightSensor), digitalRead(farRightSensor) };
```

This data can be used to check each sensor output as a boolean and be used in an if-statement to execute the desired outcome like shown below:
```cp
if (sens[0] && sens[1] && !sens[2] && sens[3] && sens[4]) {
    straight(); // Calls a function which sets motors to go forward with the default speed.
}
  ```
  
  [^1]: [Study IT Windesheim University Zwolle](https://www.windesheim.nl/opleidingen/voltijd/bachelor/hbo-ict-zwolle)
