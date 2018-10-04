// Allocate Pin number for different function
#define joystickA_x 14 //A0
#define joystickA_y 15 //A1
#define joystickA_sw 3 //D3

//#define joystickB_y 

/* Motor Placement
*       ^  <------direction of propagation
*       ||
* B---------A
*/

//Motor A
#define enableA 5 //D5 
#define inputA1 7 //D7
#define inputA2 8 //D8

//Motor B
#define enableB 6 //D6
#define inputB1 9 //D9
#define inputB2 10 //D10

//Motor C
//#define enableC
//#define inputC1
//#define inputC2

//Analog Read Range values
#define analogReadMax  1023
#define analogReadMin  0
#define threshold  200

//Analog Write Range values
#define analogWriteMax  255
#define analogWriteMin  0

int lowerRange = (analogReadMax / 2) -  threshold;
int upperRange = (analogReadMax / 2) + threshold;


//Amound to add for each interval
int tick = 255/100;

// initialize value;
//int led_blue_out, led_yellow_out;
int x = 0, y = 0, z = 0,sw = 0;
int dx,dy,dz;
void setup() {
  // Setup the communication bps to 9600
  Serial.begin(9600);
  // Enable both motor have power supply
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  pinMode(inputA1, OUTPUT);
  pinMode(inputA2, OUTPUT);
  pinMode(inputB1, OUTPUT);
  pinMode(inputB2, OUTPUT);

  pinMode(joystickA_sw, INPUT_PULLUP);
//setDirection(inputC1, inputC2, true);
}

void loop() {
  // Analog Signal on Arduino has duty cycles, so wee need to add delay
  dy = analogReadWithPin(joystickA_y);
  delayMicroseconds(100);
  dx = analogReadWithPin(joystickA_x);
  delayMicroseconds(100);
  //dz = analogReadWithPin(joystickB_y);
  
  sw = digitalRead(joystickA_sw);
  Serial.println("SW:"+String(sw));
  if( 0 == sw  ){
    x = 0;
    delay(100);
  }
  else{
    y = constrain(y - dy, -analogWriteMax, analogWriteMax);
    // immediate turning
    x = constrain(
      map(dx, -tick, tick, -analogWriteMax, analogWriteMax),
      -analogWriteMax, analogWriteMax);
  }
  
  // Setup the motor spining direction
  motorOutputByValue(x,y,dx,dy);
  
  //motorOutputZ(dz);
  delay(10);
}


int analogReadWithPin(int analogReadPin){
  // the range of Analog Read is 0 - 1023
  /* the values of Analog Read is 
  proportional to the amount of voltage being applied to the pin. */
  int analogReadValue = analogRead(analogReadPin);
  if(analogReadValue < lowerRange){
    return map(analogReadValue, lowerRange, analogReadMin, 0, 
    -tick);

  }else if(analogReadValue >= upperRange){
    return map(analogReadValue, upperRange, analogReadMax, 0, tick);
  }else{
    return 0;
  }

}

int motorOutputByValue(int x, int y, int dx, int dy){
  //The value of analogWrite will be constrain within the range of analog Write after add of minus changes after the calculation

  /* For -255<- x ->255
  *       0 < y <= 255
  */
  Serial.println("X:"+String(x));
  Serial.println("Y:"+String(y));
  bool clockwise = (x >= 0);
  analogWriteTurning(enableB, enableA, y, x, analogWriteMin, analogWriteMax, clockwise);
}

void analogWriteTurning(int pinL,int pinR,int s,int ds,int lower, int upper,bool dir){
  // dir :True -> clockwise turning, False -> counter-clockwise turning
  //Assume 0 < s < {R}
  // -{R} < ds < {R}

  setDirection(inputA1, inputA2, (y>=0));
  setDirection(inputB1, inputB2, !(y>=0));
  int outputValue = constrain(abs(s)-abs(ds), lower, upper);
  if(dir){
    analogWrite(pinL,s);
    analogWrite(pinR,outputValue);
  }else{
    analogWrite(pinL, outputValue);
    analogWrite(pinR, s);
  }
}

//void motorOutputZ(int dz){
//  z = constrain(z + dz, -analogWriteMax, analogWriteMax);
//  bool dir =  (z>=0);
//  setDirection(inputC1,inputC2,dir);
//  analogWrite(enableC, abs(z));
//}


void setDirection(int in1, int in2, bool clockwise){
  // if clockwise is true, the input direction is reversed
  if(clockwise){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);  
  }
}

/*
 * TESTING
 */
int testVoltage(int analogPin){
  double voltage = analogRead(analogPin) * 5.0 / 1024;
  Serial.println("The Voltage from Pin " + String(analogPin) + " is :" + String(voltage));
}
