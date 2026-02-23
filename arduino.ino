#include <AccelStepper.h>
#include <Servo.h>

// X-Axis මෝටර් එකේ Pins (ULN2003 Driver)
#define motor1Pin1  8
#define motor1Pin2  9
#define motor1Pin3  10
#define motor1Pin4  11

// Y-Axis මෝටර් එකේ Pins (ULN2003 Driver)
#define motor2Pin1  2
#define motor2Pin2  3
#define motor2Pin3  4
#define motor2Pin4  5

// Servo Pin
#define servoPin 6

// මෝටර් එකක වේගය සහ acceleration අගයන්
float motorSpeed = 500.0; 
float motorAccel = 200.0;

// මෝටර් Objects නිර්මාණය කිරීම
AccelStepper stepperX(8, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepperY(8, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);
Servo penServo;

void setup() {
  Serial.begin(9600);
  
  // මෝටර් වල වේගය සකස් කිරීම
  stepperX.setMaxSpeed(motorSpeed);
  stepperX.setAcceleration(motorAccel);
  
  stepperY.setMaxSpeed(motorSpeed);
  stepperY.setAcceleration(motorAccel);

  // Servo එක සම්බන්ධ කිරීම
  penServo.attach(servoPin);
  
  // ආරම්භයේදී පෑන උඩට ගැනීම (Pen Up)
  penUp(); 
  
  Serial.println("Drawing Machine Ready!");

}

void loop() {
  // සරලව කොටුවක් ඇඳීමට උදාහරණයක් (Square Test)
  
  drawSquare();
  
  while(1); // එක පාරක් ඇඳලා නතර වීමට
}

// පෑන උඩට ගැනීමට
void penUp() {
  penServo.write(90); // ඔයාගේ mechanism එක අනුව අගය වෙනස් කරන්න
  delay(500);
}

// පෑන පහළට (කොළය මතට) ගැනීමට
void penDown() {
  penServo.write(10); // ඔයාගේ mechanism එක අනුව අගය වෙනස් කරන්න
  delay(500);
}

// කොටුවක් ඇඳීමේ function එක
void drawSquare() {
  penDown();
  moveTo(1000, 0);    // දකුණට
  moveTo(1000, 1000); // ඉහළට
  moveTo(0, 1000);    // වමට
  moveTo(0, 0);       // පහළට (මුලට)
  penUp();
}

// නිශ්චිත තැනකට පෑන ගෙන යාමට
void moveTo(long x, long y) {
  stepperX.moveTo(x);
  stepperY.moveTo(y);
  
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run();
    stepperY.run();
  }

}
