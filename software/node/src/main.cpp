/************** Code by Mike Bardwell 2018 **************
   Adapted from PlatformIO Blynk example for the NodeMCU
 **************                            **************/

/************** includes **************/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <passwords.h>

/************** prototypes **************/
void printAll(void);
void stall();
void moveFwd();
void turnLeft();
void turnRight();
void updateMovement();
int valueCheck(int);

/************** constants **************/
char auth[] = _AUTHTOKEN;
char ssid[] = _SSID;
char pass[] = _PASS;

const int LED = D0;
const int PWML = D7;
const int PWMR = D8;
int joyHorz = 0, joyVert = 0, slider = 10, button = 0; // joystick variables
int desiredfreq = 1; // in Hz
float holdtime = 0;
bool V0flag = false, V1flag = false;

/************** setup **************/
void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  // Initialize the output variables as outputs
  pinMode(PWML, OUTPUT);
  pinMode(PWMR, OUTPUT);
  analogWriteRange(100); // re-map analog values to 100
  analogWriteFreq(1500); // set PWM frequency
  stall(); // start tank on stall

  Blynk.begin(auth, ssid, pass);
}

/************** start loop **************/
void loop(){
  Blynk.run();
  if (!button) stall();
}

/************** private functions **************/
BLYNK_WRITE(V0)
{
  joyHorz = map(param.asInt(), 0, 1023, -512, 512);
  updateMovement();
}

BLYNK_WRITE(V1)
{
  joyVert = map(param.asInt(), 0, 1023, -512, 512);
  updateMovement();
}

BLYNK_WRITE(V2)
{
  slider = map(param.asInt(), 0, 1023, 0, 100);
}

BLYNK_WRITE(V3)
{
  button = param.asInt();
  printAll();
}

void printAll() {
  Serial.print("joyHorz: ");
  Serial.print(joyHorz);
  Serial.print(" joyVert: ");
  Serial.print(joyVert);
  Serial.print(" Slider: ");
  Serial.print(slider);
  Serial.print(" Button: ");
  Serial.println(button);
}

int valueCheck(int analogInput) {
  // check for a negative input
  if (analogInput < 0) return analogInput = 0;
  else return analogInput;
}

void stall() {
  analogWrite(PWMR, 0);
  analogWrite(PWML, 0);
}

void moveFwd() {
  analogWrite(PWMR, slider);
  analogWrite(PWML, slider);
}

void turnLeft() {
  analogWrite(PWMR, slider);
  analogWrite(PWML, 0);
}

void turnRight() {
  analogWrite(PWML, slider);
  analogWrite(PWMR, 0);
}

void updateMovement() {
  if (millis() - holdtime > (1000/desiredfreq)) {
    if (joyVert > 300) moveFwd();
    else if (joyHorz > 300) turnRight();
    else if (joyHorz < -300) turnLeft();
    else stall();
    printAll();
    holdtime = millis();
  }
}
