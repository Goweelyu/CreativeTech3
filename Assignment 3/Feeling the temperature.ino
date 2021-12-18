#include "config.h"
#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int FAN = 23;
// the Adafruit IO username of whomever owns the feed
#define FEED_OWNER "pleasework"

AdafruitIO_Feed *sharedFeed = io.feed("Beijing humidity", FEED_OWNER);
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *humidity = io.feed("humidity");

void setup() {
Serial.begin(115200); 
dht.begin();

pinMode(FAN,OUTPUT);

Serial.print("Connecting to Adafruit IO"); 
io.connect();

sharedFeed->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
 }

Serial.println(); 
Serial.println(io.statusText());
sharedFeed->get();
}

void loop() 
{ io.run(); delay(2000);
float humi = dht.readHumidity();
float tempC = dht.readTemperature();
float tempF = dht.readTemperature(true);
if (isnan(humi) || isnan(tempC) || isnan(tempF))
{
Serial.println("Failed to read from DHT sensor!");
} else
{
//Serial.print("Humidity: "); Serial.print(humi);
//Serial.print("%"); Serial.print(" | ");
Serial.print("Temperature: "); 
Serial.print(tempC); 
Serial.print("°C "); 
//Serial.print(tempF); 
//Serial.println("°F");
}
temperature->save(tempC); 
humidity->save(humi); 

delay(5000);
}

void handleMessage(AdafruitIO_Data *data) {

// convert the data to integer
  int reading = data->toInt();

  Serial.print("received =");
  Serial.println(reading);
 
  // write the current 'reading' to the led
  if(reading > 32){
    digitalWrite(FAN, HIGH);
    Serial.println("FANisOn");
    }
   else{
    digitalWrite(FAN, LOW);
    Serial.println("FANisOff");
    }
  //#if defined(ARDUINO_ARCH_ESP32)
  //  ledcWrite(1, reading); // ESP32 analogWrite()
  //#else
  //  analogWrite(LED_PIN, reading);
  //#endif
}
