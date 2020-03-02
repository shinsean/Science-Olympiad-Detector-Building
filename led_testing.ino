float testing_temperature; 

void setup() {
  // Start the serial monitor for the temperature.
  Serial.begin(9600);

  // Initialize the LEDs
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}
 
void loop() {
  // Assign testing temperature.
  testing_temperature = 20;
  
  // Print the temperature.
  Serial.print(testing_temperature);
  Serial.println("° Celsius");

  // Code for turning on the desired LEDs
  
  // LED for the lowest temperature.
  if (testing_temperature >= 0 && testing_temperature < 25) {
    // Red LED
    digitalWrite(13, HIGH);

    // Turn off other LEDs
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the middle temperature.
  else if (testing_temperature >= 25 && testing_temperature < 50) {
    // Green LED
    digitalWrite(12, HIGH);

    // Turn off other LEDs
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the highest temperature.
  else if (testing_temperature >= 50 && testing_temperature < 75) {
    // Blue LED   
    digitalWrite(11, HIGH);

    // Turn off other LEDs
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  } else {
    // Turn off all LEDs if they do not fall within parameters.
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
 
  delay(500);
}
