#include <Wire.h>
#include <Zumo32U4.h>

// This is the maximum speed the motors will be allowed to turn.
// A maxSpeed of 400 lets the motors go at top speed.  Decrease
// this value to impose a speed limit.
const uint16_t maxSpeed = 200;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
void calibrateSensors()
{

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}
void setup() {
  // put your setup code here, to run once:
lineSensors.initFiveSensors();
buzzer.play(">g32>>c32");
buttonA.waitForButton();
  calibrateSensors();
  buzzer.play("L16 cdegreg4");
  while(buzzer.isPlaying());
  Serial1.begin(9600);
  buttonA.waitForButton();
}

void loop() {
  // put your main code here, to run repeatedly:
int16_t position = lineSensors.readLine(lineSensorValues);
  long int t1=millis();
  int16_t error = position - 2000;
int16_t speedDifference = error / 5 + 9 * (error - lastError);
  lastError = error;
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
  Serial1.print(leftSpeed); Serial1.print(",");
  Serial1.print(rightSpeed); Serial1.print(",");
  delay(35);
}
