//#include <dht.h>


// Libraries
#include <LiquidCrystal.h>      // LCD 1602
#include <DHT.h>                // DHT11 temp/humidity sensor
#include <OneWire.h>            // DS18B20 Water Temperature Sensor
#include <DallasTemperature.h>  // DS18B20 Water Temperature Sensor


// Safe temperature range in Fahrenheit 
const int max_temp = 67;
const int min_temp = 59;

// GPIO Pin attachments
const int air_sensor_pin = 4;
const int water_sensor_pin = 13;
const int lcd_pin_RS = 7;
const int lcd_pin_E = 8;
const int lcd_pin_D4 = 9;
const int lcd_pin_D5 = 10;
const int lcd_pin_D6 = 11;
const int lcd_pin_D7 = 12;

// Hardware connections
LiquidCrystal lcd(lcd_pin_RS,
                  lcd_pin_E,
                  lcd_pin_D4,
                  lcd_pin_D5,
                  lcd_pin_D6,
                  lcd_pin_D7);

OneWire oneWire(water_sensor_pin);

DallasTemperature waterSensor(&oneWire);

DHT airSensor(air_sensor_pin, DHT11); //DHT.h library version
//dht airSensor; //dht.h version

String calculateTempOutOfRange(float temperature){
  float tempDiff = 0;
  if(temperature > max_temp){
     tempDiff = temperature - max_temp;
  }else if(temperature < min_temp){
     tempDiff = temperature - min_temp;
  }
  return String(tempDiff);
}

void setup() {
  // start serial port
  Serial.begin(9600); 

  // start library
  waterSensor.begin();
  airSensor.begin(); // for DHT.h version

  // start lcd 
  lcd.begin(16,2); // (columns,rows)
}

void loop() {

  waterSensor.requestTemperatures();
  delay(1000);

  // Convert to Fahrenheit
  float celcius = waterSensor.getTempCByIndex(0);
  float fahrenheit = waterSensor.toFahrenheit(celcius);

  Serial.print("Water sensor temperature : ");
  Serial.print(fahrenheit);
  Serial.println(" F ");

  // LCD Line 1 : 
  lcd.setCursor(0,0);
  lcd.print(String(fahrenheit) + " F    ");

  // Temperature Range LCD Line 2 :
  if(fahrenheit < min_temp){
//    Serial.println("Your axolotl is freezing to death!");
    lcd.setCursor(0,1);
    lcd.print("TOO COLD!  -" + calculateTempOutOfRange(fahrenheit));   
  }

  if(fahrenheit >= min_temp & fahrenheit <= max_temp ){
//    Serial.println("Ideal temperature");
    lcd.setCursor(0,1);
    lcd.print("JUST RIGHT!     ");
  }
  
  if(fahrenheit > max_temp) {
//    Serial.println("Your axolotl is boiling alive!");
    lcd.setCursor(0,1);
    lcd.print("TOO HOT!   +" + calculateTempOutOfRange(fahrenheit));

  }

  delay(1000);
//  int chk = airSensor.read11(air_sensor_pin);
  float airTemp = airSensor.readTemperature(true); //true = fahrenheit
//  float airTemp = airSensor.temperature;
  delay(2000); // sensor read takes ~ 250 ms 
  Serial.println(airTemp);
  Serial.println("air temp: " + String(airTemp));
  float airHumidity = airSensor.readHumidity();
//  float airHumidity = airSensor.humidity;
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("air: ");
  lcd.print(String(airTemp) + "   ");
  lcd.setCursor(0,1);
  lcd.print("humid: ");
  lcd.print(String(airHumidity) + "     ");


  delay(1000);
}
