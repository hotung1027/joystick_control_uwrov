/* Motor Control
 *  
 *  We will call each motors A and B
 *  4 output pins are used for direction
 *  2 pwm pins for speed
 *  We use 2 joysticks, each for one motor
 *  
 */

#define inA1 5
#define inA2 6
#define inB1 7
#define inB2 8 //pins used for defining the DIRECTION OF ROTATION

#define enA 9
#define enB 10 //pwm pins for outputting MOTORSPEED

int motorSpeedA = 0, motorSpeedB = 0;
int joyA = 0, joyB = 0;

void setup() {

  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
}

void loop() {

  //Read joyA and joyB;
  
  if(joyA < 470) {

    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW); //change of direction
    
    motorSpeedA = map(joyA, 470, 0, 0, 255));
  }

  else if(joyA > 550) {

    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    
    motorSpeedA = map(joyA, 550, 1023, 0, 255));
  }

  else motorSpeedA = 0;


  if(joyB < 470) {

    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW); //change of direction
    
    motorSpeedB = map(joyB, 470, 0, 0, 255));
  }

  else if(joyB > 550) {

    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
    
    motorSpeedB = map(joyB, 550, 1023, 0, 255));
  }

  else motorSpeedB = 0;

  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}
