#include <ESP32Servo.h>

Servo myServo;

void fan_setup() {
  myServo.attach(18);  // GPIO 18
}


void movefan(){
  myServo.write(0);
  delay(500);

  myServo.write(90);
  delay(500);

  myServo.write(180);
}

