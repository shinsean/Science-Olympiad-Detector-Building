# Created by Sean Shin
# Note: To have this successfully work for a detector built with a thermistor, you must find out
# the ACoefficient, BCoefficient, and CCoefficient of that specific thermistor. You can use 
# the Steinhart-Hart equation to find out the A, B, and C coefficients for your own thermistor.

int thermistorPin = 0;
 
float voltageInput = 5;
float voltageOutput;
 
float resistorResistance = 100000;
float thermistorResistance;
 
float ACoefficient = -318.8113444e-03;
float BCoefficient = 494.3021254e-04;
float CCoefficient = -1720.624125e-07;
 
float temperature;
 
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
  temperature = 1/(ACoefficient + (BCoefficient * log(thermistorResistance)) + (CCoefficient * (log(thermistorResistance)) * (log(thermistorResistance)) * (log(thermistorResistance))));
 
  // Convert from Kelvin to Celsius.
  temperature = temperature - 273.15;

  // Print the voltage.
  Serial.print(voltageOutput);
  Serial.println("mV");

  // Print the temperature.
  Serial.print(temperature);
  Serial.println("° Celsius");

  // Code for turning on the desired LEDs
  
  // LED for the lowest temperature.
  if (temperature < 15) {
    // Red LED
    digitalWrite(13, HIGH);

    // Turn off other LEDs
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the middle temperature.
  if (temperature > 15 && temperature < 30) {
    //Green LED
    digitalWrite(12, HIGH);

    // Turn off other LEDs
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  }
  // LED for the highest temperature.
  if (temperature > 30) {
    digitalWrite(11, HIGH);

    // Turn off other LEDs
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  }
 
  delay(500);
}
