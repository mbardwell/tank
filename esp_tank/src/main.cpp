// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <Wire.h>
#include "passwords.h"

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = homeSSID;
const char* password = homePASS;

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Function
int stop(String message);
int forward(String message);
int right(String message);
int left(String message);
int backward(String message);

#define default_speed 50
bool ledon = true, ledoff = false;
long timer1 = 0;
void digitalPWM(int, float, int );

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Functions
  // rest.function("stop", stop);
  // rest.function("forward", forward);
  // rest.function("left", left);
  // rest.function("right", right);
  // rest.function("backward", backward);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("robot");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);

}

void digitalPWM(int pin, float duty, int freq) {
  float D = duty/100;
  Serial.print("D: "); Serial.println(1000*D/(freq));
  Serial.println(millis() - timer1);
  if ((millis() - timer1 > (1000*D/(freq))) & ledon) {
    digitalWrite(pin, HIGH);
    timer1 = millis(); ledon = 0; ledoff = 1;
  }
  else if ((millis() - timer1 > (1000*(1-D)/(freq))) & ledoff) {
    digitalWrite(pin, LOW);
    timer1 = millis(); ledon = 1; ledoff = 0;
  }
}
