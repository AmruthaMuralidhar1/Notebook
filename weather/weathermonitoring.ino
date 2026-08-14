#include "thingProperties.h"
#include "DHT.h"
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTpin 0 // D3 on the nodemcu ESP8266
#define DHTTYPE DHT11
DHT dht(DHTpin,DHTTYPE);

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

#define LDR_PIN 16 // D0 on the nodemcu ESP8266

#define RAIN_PIN A0 // Analog pin connected to rain sensor

Adafruit_BMP280 bmp; // I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
   bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

    // Initialize LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  //lcd.print("Initializing...");

  lcd.setCursor(3,0);
  lcd.print("Tech Trends  ");
  lcd.setCursor(0,0);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
    float h= dht.readHumidity();
    Serial.print("Humidity ");
    Serial.println(h);
    float t=dht.readTemperature();
    Serial.print("Temperature ");
    Serial.println(t);
    humidity=h;
    temperature=t;
    //message="Temperature = " + String (temperature)+"  Humidity = " + String(humidity);

    float p = bmp.readPressure();
    Serial.print("Pressure ");
    Serial.println(p);
    pressure=p;

    bool lightvalue = digitalRead(LDR_PIN);
    light = lightvalue;
    Serial.print("Light Value");
    Serial.println(lightvalue);
    if (light == 0) 
    {
        digitalWrite(LDR_PIN, HIGH);
        Serial.print("LED ON");
    } 
    else 
    {
        digitalWrite(LDR_PIN, LOW);
        Serial.print("LED OFF");
    }

    int rainvalue = analogRead(RAIN_PIN);
    rain = map(rainvalue, 400, 1023, 100, 0);
    Serial.print("Rain Value ");
    Serial.println(rain);
  
}
