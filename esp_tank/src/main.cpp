

// Replace with your network credentials
const char* ssid     = homeSSID;
const char* password = homePASS;

const int output2 = 2;
const int output0 = 0;

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(output0, OUTPUT);
  pinMode(output2, OUTPUT);
  analogWriteRange(100);
  analogWriteFreq(1500);
  analogWrite(output0, 0);
  analogWrite(output2, 0);
}

void loop(){

}
