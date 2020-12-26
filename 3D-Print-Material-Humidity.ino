#include "DHT.h"
#include "LiquidCrystal.h"

#define DHTPIN 6
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup() {
	Serial.begin(9600);
	Serial.println(F("DHTxx test!"));

	dht.begin();

	lcd.begin(16, 2);
	lcd.print("Temp:");
	lcd.setCursor(0, 1);
	lcd.print("Humi:");
	lcd.setCursor(11, 0);
	lcd.print("F.");
	lcd.setCursor(11, 1);
	lcd.print("%");

}

void loop () {
	delay(2000); // wait 2 seconds between measurements.

	  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;

     }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  lcd.setCursor(6, 0);
  lcd.print(f,1);
  lcd.setCursor(6, 1);
  lcd.print(h,1);
}
