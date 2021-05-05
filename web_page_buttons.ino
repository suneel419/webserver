#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
WebServer server(80);

#define LED1 2

const char *ssid = "sunil";
const char *password = "8790225440";

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1 style="color:red">My Home Automation</h1>
<h3> LED 1 </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led1/on'">On</button><button onclick="window.location = 'http://'+location.hostname+'/led1/off'">Off</button>

</center>
</body>
</html>
)=====";

// ipaddress/led1/on
//ipaddress/led1/off





void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  
  /*WiFi.softAP("Esp32", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());*/

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());



  //server.on("/", webpage);

   server.on("/",[]
  { 
   
  server.send_P(200, "text/html", webpage);
  });

   server.on("/led1/on",[]()
  { 
    digitalWrite(LED1,HIGH);
  server.send_P(200, "text/html", webpage);
  });

  server.on("/led1/off",[]()
  { 
    digitalWrite(LED1,LOW);
  server.send_P(200, "text/html", webpage);
  });


  server.begin();  // it will start webserver
}


void loop(void)
{
  server.handleClient();
}
