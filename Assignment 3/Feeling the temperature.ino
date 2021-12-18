#include "config.h"
#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//#define LED_PIN 5
int LED = 23;
// the Adafruit IO username of whomever owns the feed
#define FEED_OWNER "pleasework"

// set up the `sharedFeed`
AdafruitIO_Feed *sharedFeed = io.feed("Beijing humidity", FEED_OWNER);
AdafruitIO_Feed *temperature = io.feed("temperature");
//AdafruitIO_Feed *humidity = io.feed("Beijing humidity"); 
AdafruitIO_Feed *humidity = io.feed("humidity");

void setup() {
// start the serial connection 
Serial.begin(115200); 
dht.begin();

pinMode(LED,OUTPUT);
//digitalWrite(LED,LOW);

// wait for serial monitor to open 
Serial.print("Connecting to Adafruit IO"); 
io.connect();

// set up a message handler for the 'analog' feed.
// the handleMessage function (defined below)
// will be called whenever a message is
// received from adafruit io.
sharedFeed->onMessage(handleMessage);

// wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
 }

// temperature->onMessage(handleMessage); 
// humidity->onMessage(handleMessage);
Serial.println(); 
Serial.println(io.statusText());
sharedFeed->get();
}

void loop() 
{ io.run(); delay(2000);
// read humidity
float humi = dht.readHumidity();
// read temperature as Celsius
float tempC = dht.readTemperature();
// read temperature as Fahrenheit
float tempF = dht.readTemperature(true);
// check if any reads failed
if (isnan(humi) || isnan(tempC) || isnan(tempF))
{
Serial.println("Failed to read from DHT sensor!");
} else
{
Serial.print("Humidity: "); Serial.print(humi);
Serial.print("%"); Serial.print(" | ");
Serial.print("Temperature: "); 
Serial.print(tempC); 
Serial.print("°C ~ "); 
Serial.print(tempF); 
Serial.println("°F");
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
  if(reading < 32){
    digitalWrite(LED, HIGH);
    Serial.println("LEDisOn");
    }
   else{
    digitalWrite(LED, LOW);
    Serial.println("LEDisOff");
    }
  //#if defined(ARDUINO_ARCH_ESP32)
  //  ledcWrite(1, reading); // ESP32 analogWrite()
  //#else
  //  analogWrite(LED_PIN, reading);
  //#endif
}
