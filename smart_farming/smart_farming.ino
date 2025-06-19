#include <DHT.h>

// Define Pins
#define DHTPIN D4        // Temperature Sensor
#define DHTTYPE DHT11    // or DHT22
#define PIRPIN D0        // PIR Motion Sensor
#define SOILPIN A0       // Soil Moisture Sensor
#define RAINPIN D2       // Rain Sensor
#define RELAYPIN D3      // Relay Module
#define BUZZERPIN D1     // Buzzer

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(PIRPIN, INPUT);
  pinMode(RAINPIN, INPUT);
  pinMode(SOILPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);

  digitalWrite(RELAYPIN, LOW);   // Pump OFF initially
  digitalWrite(BUZZERPIN, LOW);  // Buzzer OFF
}

void loop() {
  // Temperature & Humidity
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Soil Moisture
  int soilValue = analogRead(SOILPIN);  // 0 to 1023
  bool isSoilDry = soilValue > 600;     // Adjust threshold as needed

  // Rain Detection
  bool isRaining = digitalRead(RAINPIN) == LOW;

  // Motion Detection
  bool motionDetected = digitalRead(PIRPIN) == HIGH;

  // Pump Control
  if (isSoilDry && !isRaining) {
    digitalWrite(RELAYPIN, HIGH); // Pump ON
  } else {
    digitalWrite(RELAYPIN, LOW);  // Pump OFF
  }

  // Buzzer Alerts
  if (motionDetected || isRaining) {
    digitalWrite(BUZZERPIN, HIGH);
  } else {
    digitalWrite(BUZZERPIN, LOW);
  }

  // Debugging Output
  Serial.println("---- Sensor Data ----");
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("Soil: ");
  Serial.println(soilValue);

  Serial.print("Rain: ");
  Serial.println(isRaining ? "Yes" : "No");

  Serial.print("Motion: ");
  Serial.println(motionDetected ? "Yes" : "No");
  Serial.println("---------------------\n");

  delay(2000);  // 2 seconds delay
}
