/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include "passwords.h"

// #define lab
#define robocar

#ifdef lab
  #define _SSID "lab"
  #define _PASS "rettontancep62"
#endif
#ifdef home
  #define _SSID "PMW"
  #define _PASS "MmeAllard"
#endif
#ifdef robocar
  #define _SSID "robocar"
  #define _PASS "letsbuildrobots"
#endif

#define _AUTHTOKEN "b0033467134c43ce9aa74f5c4e8206ce"

// You should get Auth Token emailed to you when you 
// make a Blynk account.
// Go to the Project Settings (nut icon).
char auth[] = _AUTHTOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = _SSID;
char pass[] = _PASS;

const int PWM1 = 3;
const int PWM2 = 4;

void setup() {
  Serial.begin(115200);

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);

  // Initialize the output variables as outputs
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  analogWriteRange(100);
  analogWriteFreq(1500);
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop(){
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  if (pinValue > 700) {
    digitalWrite(0,1);
  }
  digitalWrite(0,0);
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  if (pinValue > 700) {
    digitalWrite(2,1);
  }
  digitalWrite(2,0);
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
  digitalWrite(0, pinValue);
}
