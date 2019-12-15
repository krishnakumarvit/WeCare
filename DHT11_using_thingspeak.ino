
#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 
String apiKey = "I4B3XIWU6TKJVOZ8";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ASUS07";     // replace with your wifi ssid and wpa2 key
const char *pass =  "iothackoff";
const char* server = "api.thingspeak.com";

#define DHTPIN 0          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);

WiFiClient client;

int outputpin = A0;

void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
      int analogValue = analogRead(outputpin);
      float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
      float celsius = millivolts/10;
      float fahrenheit = ((celsius * 9)/5 + 32);

      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(fahrenheit);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celsius, Humidity: ");
                             Serial.print(h);
                             Serial.print(" in Farenheit=   ");
                             Serial.println(fahrenheit);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  delay(10000);
}
