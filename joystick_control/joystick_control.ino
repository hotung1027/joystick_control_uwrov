// Allocate Pin number for different function
int joystick_x = 0;
int joystick_y = 1;
int led_blue = 2;
int led_yellow = 3;

// initialize value;
int led_blue_out, led_yellow_out;

void setup() {
  // Setup the communication bps to 9600
  Serial.begin(9600);
}

void loop() {
  // Analog Signal on Arduino has duty cycles, so wee need to add delay
  writeLEDFrom(joystick_x, led_blue, "Value from x :");
  delay(100);
  writeLEDFrom(joystick_y, led_yellow, "Value from y :");
}

void writeLEDFrom(int analogPin, int LED_Pin, String message){
  int ledOutputVoltage = convertAnalogFromRead(analogReadWithPin(analogPin, message));
  lightLED(LED_Pin,ledOutputVoltage );
}

int analogReadWithPin(int analogPin, String message){
  // the range of Analog Read is 0 - 1023
  /* the values of Analog Read is 
  proportional to the amount of voltage being applied to the pin. */
  int analogReadValue = analogRead(analogPin);
  Serial.println(message + String(analogReadValue) );
  return analogReadValue;
}

int convertAnalogFromRead(int analogReadValue){
  // the range of Analog Read is 0 - 1023
  // the range of Analog Write is 0 - 255
  int analogWriteValue = analogReadValue / 1024 * 255;
}

void lightLED(int LED_Pin, int value){
 // not need to call pinMode() to set the pin as an output before calling analogWrite()
 // TODO: convert caculation of Joystick to LED voltage should do here
 analogWrite(LED_Pin, value);
}

int testVoltage(int analogPin){
  double voltage = analogRead(analogPin) * 5.0 / 1024;
  Serial.println("The Voltage from Pin " + String(analogPin) + " is :" + String(voltage));
}
