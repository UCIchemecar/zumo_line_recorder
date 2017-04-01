#include <Wire.h>
#include <Zumo32U4.h>

// This is the maximum speed the motors will be allowed to turn.
// A maxSpeed of 400 lets the motors go at top speed.  Decrease
// this value to impose a speed limit.
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
int steps[]={200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  buttonA.waitForButton();
}

void loop() {
  static int i=0;
  if(i<sizeof(steps))
  motors.setSpeeds(steps[i++], steps[i++]);
  else
  motors.setSpeeds(0, 0);
  delay(50);
}
