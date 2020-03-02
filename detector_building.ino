// Created by Sean Shin
// Note: To have this successfully work for a detector built with a thermistor, you must find out
// the ACoefficient, BCoefficient, and CCoefficient of that specific thermistor. You can use 
// the Steinhart-Hart equation to find out the A, B, and C coefficients for your own thermistor.

int thermistorPin = 0;
 
float voltageInput = 5;
float voltageOutput;
 
float resistorResistance = 100000;
float thermistorResistance;
 
float ACoefficient = -0.004915617852;
float BCoefficient = 0.001599130566;
float CCoefficient = -0.000008148359156;
 
float temperature_correction;
float raw_temperature;
float corrected_temperature; 

void setup() {
  // Start the serial monitor for the temperature.
  Serial.begin(9600);

  // Initialize the LEDs
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}
 
void loop() {
  // Reads the voltage between the thermistor and resistor.
  voltageOutput = analogRead(thermistorPin);
 
  // Convert voltageOutput from millivolts to volts.
  voltageOutput = voltageOutput/1000;
 
  // Finds the resistance of the thermistor at the moment. This is necessary for the Steinhart Hart Equation which will be used to figure out the temperature.
  thermistorResistance = resistorResistance * 1/((voltageInput/voltageOutput) - 1);
 
  // Finds the actual temperature by using thermistorResistance and the coefficients of this particular thermistor in the Steinhart Hart Equation.
  raw_temperature = 1/(ACoefficient + (BCoefficient * log(thermistorResistance)) + (CCoefficient * (log(thermistorResistance)) * (log(thermistorResistance)) * (log(thermistorResistance))));

  // Convert from Kelvin to Celsius.
  raw_temperature = raw_temperature - 273.15;
  
  // Calculates the amount of correction needed to get an accurate reading.
  temperature_correction = ((0.0002316 * (raw_temperature) * (raw_temperature) * (raw_temperature)) - (0.01962 * (raw_temperature) * (raw_temperature)) + (0.3821 * (raw_temperature)) + 0.4969);
  Serial.println(temperature_correction);
  
  // Recalculate the temperature with the calculated correction.
  corrected_temperature = raw_temperature + temperature_correction;

  // Print the voltage.
  Serial.print(voltageOutput);
  Serial.println("V");

  // Print the temperature.
  Serial.print(corrected_temperature);
  Serial.println("° Celsius");

  // Code for turning on the desired LEDs
  
  // LED for the lowest temperature.
  if (corrected_temperature >= 0 && corrected_temperature < 25) {
    // Red LED
    digitalWrite(13, HIGH);

    // Turn off other LEDs
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the middle temperature.
  else if (corrected_temperature >= 25 && corrected_temperature < 50) {
    // Green LED
    digitalWrite(12, HIGH);

    // Turn off other LEDs
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the highest temperature.
  else if (corrected_temperature >= 50 && corrected_temperature < 75) {
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
