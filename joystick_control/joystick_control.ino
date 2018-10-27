// Allocate Pin number for different function
#define joystickA_y 14 //A0
#define joystickB_y 15 //A1


// Potentiometer
#define pmeter 16 //A2


/* Motor Placement
*      ^  <------direction of propagation
*     ||
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
#define enableC 11 //D11
#define inputC1 12 //D12
#define inputC2 13 //D13

//Analog Read Range values
#define analogReadMax  1023
#define analogReadMin  0
#define threshold  100

//Analog Write Range values
#define analogWriteMax  200
#define analogWriteMin  0

int lowerRange = (analogReadMax / 2) - threshold;
int upperRange = (analogReadMax / 2) + threshold;


//Amount to add for each interval
#define rate 10
#define rate_x 5
#define rate_y 3
int tick = 5 * rate;

// initialize value;
//int led_blue_out, led_yellow_out;
int a,b,c;
void setup() {
  // Setup the communication bps to 9600
  Serial.begin(9600);
  // Enable both motor have power supply
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(enableC, OUTPUT);

  pinMode(inputA1, OUTPUT);
  pinMode(inputA2, OUTPUT);
  pinMode(inputB1, OUTPUT);
  pinMode(inputB2, OUTPUT);
  pinMode(inputC1, OUTPUT);
  pinMode(inputC2, OUTPUT);

//setDirection(inputC1, inputC2, true);
}

void loop() {
  // Analog Signal on Arduino has duty cycles, so wee need to add delay
  a = analogReadWithPin(joystickA_y);
  delayMicroseconds(100);
  b = analogReadWithPin(joystickB_y);
  delayMicroseconds(100);
  c = analogReadWithPin(pmeter);
  delayMicroseconds(100);

  // Setup the motor spining direction
  motorOutput(enableA, inputA1, inputA2, a,  analogWriteMin, analogWriteMax, true);
  motorOutput(enableB, inputB1, inputB2, b,  analogWriteMin, analogWriteMax, false);
  motorOutput(enableC, inputC1, inputC2, c,  analogWriteMin, analogWriteMax, true);
  delay(10);
}


int analogReadWithPin(int analogReadPin){
  // the range of Analog Read is 0 - 1023
  /* the values of Analog Read is 
  proportional to the amount of voltage being applied to the pin. */
  int analogReadValue = analogRead(analogReadPin);
  if(analogReadValue <= lowerRange){    
    return map(analogReadValue, lowerRange, analogReadMin, 0,-analogWriteMax);
  }else if(analogReadValue >= upperRange){    
    return map(analogReadValue, upperRange, analogReadMax, 0, analogWriteMax);    
  }else{
    return 0;    
  }

}


void motorOutput(int en, int in1,int in2,int s,int lower, int upper,bool dir){
  // dir :True -> clockwise turning, False -> counter-clockwise turning
  //Assume -{R} < s < {R}

  setDirection(in1, in2, !((s>=0)^(dir)));
  int outputValue = constrain(abs(s), lower, upper);
  analogWrite(en,outputValue);

}



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
  delayMicroseconds(100);
}

/*
 * TESTING
 */
int testVoltage(int analogPin){
  double voltage = analogRead(analogPin) * 5.0 / 1024;
  Serial.println("The Voltage from Pin " + String(analogPin) + " is :" + String(voltage));
}
