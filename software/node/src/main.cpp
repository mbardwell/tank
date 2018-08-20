/************** Code by Mike Bardwell 2018 **************
   Adapted from PlatformIO Blynk example for the NodeMCU
 **************                            **************/

/************** includes **************/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <passwords.h>

/************** prototypes **************/
void printAll(void);

/************** constants **************/
char auth[] = _AUTHTOKEN;
char ssid[] = _SSID;
char pass[] = _PASS;

const int LED = D0;
const int PWM1 = D7;
const int PWM2 = D8;
int joyL = 0, joyR = 0, slider = 0, button = 0; // joystick variables
int desiredfreq = 10; // in Hz
float holdtimeL = 0, holdtimeR = 0;

/************** setup **************/
void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  // Initialize the output variables as outputs
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  analogWriteRange(100); // re-map analog values to 100
  analogWriteFreq(1500);
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);

  Blynk.begin(auth, ssid, pass);
}

/************** start loop **************/
void loop(){
  Blynk.run();
}

/************** private functions **************/
BLYNK_WRITE(V0)
{
  if (millis() - holdtimeL > (1000/desiredfreq)) {
    joyL = map(param.asInt(), 0, 1023, 0, slider - 20);
    if (button) analogWrite(PWM1, joyL);
    else analogWrite(PWM1, 0);
    printAll();
    holdtimeL = millis();
  }
}

BLYNK_WRITE(V1)
{
  if (millis() - holdtimeR > (1000/desiredfreq)) {
    joyR = map(param.asInt(), 0, 1023, 0, slider - 20);
    if (button) analogWrite(PWM2, joyR);
    else analogWrite(PWM2, 0);
    printAll();
    holdtimeR = millis();
  }
}

BLYNK_WRITE(V2)
{
  slider = map(param.asInt(), 0, 1023, 0, 100);
}

BLYNK_WRITE(V3)
{
  button = param.asInt();
  printAll();
  digitalWrite(LED, button);
}

void printAll() {
  Serial.print("joyL: ");
  Serial.println(joyL);
  Serial.print("joyR: ");
  Serial.println(joyR);
  Serial.print("Slider: ");
  Serial.println(slider);
  Serial.print("Button: ");
  Serial.println(button);
}
