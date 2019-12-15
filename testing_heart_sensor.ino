int sensorPin = A0;   //for analog input
#include <ESP8266WiFi.h>

int newBPM;
int i;

String apiKey = "I4B3XIWU6TKJVOZ8";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ASUS07";     // replace with your wifi ssid and wpa2 key
const char *pass =  "iothackoff";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()  {
  Serial.begin(115200);
  
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

void loop()  {
  int heartValue = analogRead(sensorPin);    //reading the analog value
  //Serial.println(heartValue);   //printing the value tot the serial plotter
  delay(5);

  Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 
  for (i=0;i<20;i++){
    newBPM = random(68,78);
  }


  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {
                            
                             String postStr = apiKey;
                             postStr +="&field4=";
                             postStr += String(newBPM);
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
                      }
 
          client.stop();
          Serial.println(newBPM); 
          Serial.println("Waiting...");
          delay(10000);
  }
