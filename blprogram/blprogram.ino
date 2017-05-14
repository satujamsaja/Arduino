#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// Servo settings on shields.
#define SERVO2_PWM 9
#define SERVO1_PWM 10

// Ultrasonic sensor settings.
#define TRIGGER_PIN  16  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance.

// Use NewPing library.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// 
SoftwareSerial mySerial(14, 15); // RX, TX  

// DC gearbox motor shield, which is use  M2 and Motor M4.
AF_DCMotor motor1(2);
AF_DCMotor motor2(4);

// Use servo library.
Servo servo1;
Servo servo2;

// Default motor speed set to maximum.
int speed = 255;

void setup() {
  // Serial and software serial initialization.
  Serial.begin(9600);
  mySerial.begin(9600);

  // Servo setup
  servo1.attach(SERVO1_PWM);
  servo2.attach(SERVO2_PWM);

  // Set servo position on load.
  servo1.write(90);
  servo2.write(90);
}

void loop() {
  
  String c = "";
  
  while (mySerial.available() > 0) {
    c += (char) mySerial.read();
    delay(5);
  }

  if(c!= "") {
    Serial.println(c);
    String param1 = getParams(c,'-',0);
    String param2 = getParams(c,'-',1);

//    // Change motor speed
//    if(param1 == "SPEED") {
//      speed = param2.toInt();
//    }
//
//    // OAV enable disable
//    if(param1 == "OAV") {
//      if(param2 == "ENABLE") {
//        motorRun("FORWARD","",speed);
//        scanObstacle();
//      }
//      if(param2 == "DISABLE") {
//        motorRun("RELEASE","",0);
//      }
//    }
//
//    // Run motor based on parameter.
//    motorRun(param1,param2,speed); 
  }

}

/**
 * Motor control function.
 */
void motorRun(String motorDirection, String motorPosition, int speed) {

  if(motorPosition == "") {
    motorSpeed(speed);
    if(motorDirection == "FORWARD") {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
    else if(motorDirection == "BACKWARD") {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
    }
    else if(motorDirection == "RELEASE") {
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
  }
  else {
    if(motorPosition == "LEFT"){
      motor1.setSpeed(speed);
      motor2.setSpeed(speed/2);
    }
    else if(motorPosition == "RIGHT") {
      motor1.setSpeed(speed/2);
      motor2.setSpeed(speed/1);
    }
    
    if(motorDirection == "FORWARD") {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
    else if(motorDirection == "BACKWARD") {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
    }
  }
}

/**
 * Motor speed function.
 */
void motorSpeed(int speed) {
  speed = speed;
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
}  

/**
 * Get params from serial data coming from bluetooth.
 */
String getParams(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void scanObstacle() {
  boolean noObstacle = true;
  while(noObstacle) {
    int distance = sonar.ping_cm();
    if(distance < 20 && distance > 0){
      motorRun("RELEASE","",0);
      // Check surround obstacle and decide turn.
      int angle[] = {0,90,180,90};
      String directionRight = "";
      String directionLeft = "";
      for(int i=0; i < 4; i++) {
        servo2.write(angle[i]);
        delay(2000);
        int obstacleDist = sonar.ping_cm();
        delay(1000);
        if(obstacleDist < 20 && obstacleDist > 0) {
          // If on right has obstacle go left.
          if(angle[i] == 0) {
             directionLeft = "LEFT";
          }
          // if on left has obstacle go right.
          if(angle[i] == 180) {
            directionRight = "RIGHT";
          }
        }
      }
      // Decide where to go.
      if(directionRight == "" && directionLeft != "") {
        motorRun("FORWARD","LEFT", speed);
        delay(3000);
        motorRun("RELEASE","",0);
      }
      
      if(directionLeft == "" && directionRight != "") {
        motorRun("FORWARD","RIGHT", speed);
        delay(3000);
        motorRun("RELEASE","",0);
      }

      if(directionLeft != "" && directionRight != "") {
        motorRun("BACKWARD","", speed);
        delay(3000);
        motorRun("RELEASE","",0);
      }    
    }
    else {
      motorRun("FORWARD","", speed);
    }
  }
}

