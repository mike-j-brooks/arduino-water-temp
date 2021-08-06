// Libraries

#include <LiquidCrystal.h>  // LCD 1602
#include <SimpleDHT.h>      // DHT11 temp/humidity sensor
#include <OneWire.h>        // DS18B20 Water Temperature Sensor
#include <DallasTemperature.h>  // DS18B20 Water Temperature Sensor

const int water_sensor_pin = 2;

OneWire oneWire(water_sensor_pin);

DallasTemperature sensor(&oneWire);

void setup() {
  // start serial port
  Serial.begin(9600);

  // start library
  sensor.begin();

}

void loop() {

  sensor.requestTemperatures();
  delay(1000);
  
  celcius = sensor.getTempCByIndex(0);
  fahrenheit = sensor.toFahrenheit(celcius);

  Serial.print("Current temperature : ");
  Serial.print(fahrenheit);
  Serial.println(" F ");
  delay(1000);
}
