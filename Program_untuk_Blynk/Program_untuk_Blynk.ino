#define BLYNK_TEMPLATE_ID "TMPL6FgSOkCHU"
#define BLYNK_TEMPLATE_NAME "Mesh Network Air Monitoring System"
#define BLYNK_AUTH_TOKEN "Llzn0jPmN1Qo08hRgkqhuJJAiYkgTZkE"

#define DHTPIN 4
#define DHTTYPE DHT22
#define LIGHT_SENSOR_PIN 4
#include <GP2Y1010AU0F.h>

DHT dht(DHTPIN, DHTTYPE);
int Sensor_input = 4;
int measurePin = 2;
int ledPin     = 15;
GP2Y1010AU0F dustSensor(ledPin, measurePin); // Construct dust sensor global object
float dustDensity = 0;

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include "DHT.h"
#include <GP2Y1010AU0F.h>


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "KRISNADN";
char pass[] = "23mei2023";

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();
  pinMode(LED, OUTPUT);
  dustSensor.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, kirimData);  
}
void kirimData()
{
Blynk.virtualWrite(V0, temperature);
Blynk.virtualWrite(V1, humidity);
Blynk.virtualWrite(V2, mq2);
Blynk.virtualWrite(V2, dustdensity);
}
void loop()
{
  Blynk.run();  
  timer.run();
  delayMicroseconds(samplingTime);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
    Serial.println();
  delay(3000);
  int Sensor_input = analogRead(Sensor_input);
    Serial.print("Nilai MQ-2: ");
  delay(1000);
    Blynk.run();
  dustDensity = dustSensor.read();
    Serial.print("Kepadatan Debu = ");
    Serial.print(dustDensity);
    Serial.println(" ug/m3");
    Serial.println();  
  delay(3000);
}
