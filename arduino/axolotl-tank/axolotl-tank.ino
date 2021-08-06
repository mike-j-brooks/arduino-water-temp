// Libraries

#include <LiquidCrystal.h>  // LCD 1602
#include <SimpleDHT.h>      // DHT11 temp/humidity sensor
#include <OneWire.h>        // DS18B20 Water Temperature Sensor
#include <DallasTemperature.h>  // DS18B20 Water Temperature Sensor

const int water_sensor_pin = 2;

OneWire oneWire(water_sensor_pin);

DallasTemperature waterSensor(&oneWire);

void setup() {
  // start serial port
  Serial.begin(9600);

  // start library
  waterSensor.begin();

}

void loop() {

  waterSensor.requestTemperatures();
  delay(1000);
  
  celcius = waterSensor.getTempCByIndex(0);
  fahrenheit = waterSensor.toFahrenheit(celcius);

  Serial.print("Current temperature : ");
  Serial.print(fahrenheit);
  Serial.println(" F ");
  delay(1000);
}
