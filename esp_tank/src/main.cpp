/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <passwords.h>

// You should get Auth Token in the Blynk App.
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
