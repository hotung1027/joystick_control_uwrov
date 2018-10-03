/* Read Joystick
 *  ---------------------
 *  
 *  Reads the analog value of the joystick's slide,
 *  then outputs the value in 8-bit range (for led).
 */
 
#define inA1 7
#define inA2 8
#define inB1 9
#define inB2 10 //pins used for defining the DIRECTION OF ROTATION

#define JoyA 14 //A0
#define JoyB 15 //A1
#define Potentiometer 16 //A2

#define enA 5
#define enB 6 //pwm pins for outputting MOTORSPEED

int joyA, joyB;
float motorSpeedA = 0, motorSpeedB = 0;
const float t;

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  
  Serial.begin(9600);
}

void loop() {

  joyA = analogRead(JoyA);
  
  if(joyA < 470) {

    motorSpeedA -= (256 / t);
    constrain(motorSpeedA, 0, 255);
  }

  else if(joyA > 550) {

    motorSpeedA += (256 / t);
    constrain(motorSpeedA, 0, 255);
  }

  joyB = analogRead(JoyB);
  
  if(joyB < 470) {

    motorSpeedB -= (256/t);
    constrain(motorSpeedB, 0, 255);
  }

  else if(joyB > 550) {

    motorSpeedB += (256/t);
    constrain(motorSpeedB, 0, 255);
  }
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);

  delay(200);
}
