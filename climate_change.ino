#include <DHT.h>

// Define pin connections
#define DHTPIN 2        // Pin where the DHT sensor is connected
#define DHTTYPE DHT11   // DHT11 or DHT22
#define FANPIN 3        // Pin connected to the fan (via relay or MOSFET)

// Define temperature threshold
#define TEMP_THRESHOLD 30 // Temperature in °C to trigger the fan

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Set fan pin as output
  pinMode(FANPIN, OUTPUT);
  digitalWrite(FANPIN, LOW); // Ensure fan is off initially

  Serial.println("Automatic Ventilation System Initialized");
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  float temp = dht.readTemperature(); // Read temperature in °C
  
  // Check if the sensor reading is valid
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Log temperature for debugging
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Control the fan based on the temperature
  if (temp > TEMP_THRESHOLD) {
    digitalWrite(FANPIN, HIGH); // Turn on the fan
    Serial.println("Fan ON");
  } else {
    digitalWrite(FANPIN, LOW); // Turn off the fan
    Serial.println("Fan OFF");
  }

  // Wait a short while before the next loop
  delay(2000); // 2-second delay
}
