// Soil Moisture Sensor Setup
const int moisturePin = A0; // Analog pin for soil moisture sensor

// Rain Sensor Setup
const int rainPin = 8; // Digital pin for rain sensor

// Pump Setup
const int pumpPin = 7; // Digital pin for controlling the water pump

// Moisture Thresholds
const int dryThreshold = 1000;  // Adjust this value based on your sensor and soil conditions
const int wetThreshold = 500;  // Adjust this value based on your sensor and soil conditions

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Set pump and rain sensor pins as OUTPUT and INPUT, respectively
  pinMode(pumpPin, OUTPUT);
  pinMode(rainPin, INPUT);
}

void loop() {
  // Read soil moisture level
  int moisture = analogRead(moisturePin);

  // Read rain sensor
  int rainValue = digitalRead(rainPin);

  // Print the moisture and rain sensor values to the serial monitor
  Serial.print("Moisture: ");
  Serial.println(moisture);
  Serial.print("Rain Sensor: ");
  Serial.println(rainValue);

  // Check if it's not raining and the soil is too dry
  if (rainValue == HIGH && ( moisture > wetThreshold || moisture < dryThreshold)) {
    // Soil is too dry, turn on the pump
    digitalWrite(pumpPin, HIGH);
    Serial.println("Pump is ON (Soil too dry)");
  } else if (rainValue == LOW || moisture < wetThreshold) {
    // Soil is too wet, turn off the pump
    digitalWrite(pumpPin, LOW);
    Serial.println("Pump is OFF (Soil wet enough)");
  }
  else
  {
    Serial.println("Soil Moisture Sensor is in the Air");
    digitalWrite(pumpPin, LOW);
  }

  // Delay for a while before taking the next reading (adjust as needed)
  delay(1000);
}
