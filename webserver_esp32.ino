/*#include<WiFi.h>
#include<ESPmDNS.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

void notfound(AsyncWebServeRequest *request)
{
  request->send(404,"text/plain","Not found");
}
void setup() 
{
  Serial.begin(115200);
  WiFi.softAP("ESP32","");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

    server.on("/",[](AsyncWebServerRequest *request)
    {
      String message="Hello World";
      request->send(200,"text/html",message);
    });

    server.onNotFound(notfound);
    server.begin();
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}*/

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif



#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  
  WiFi.softAP("techiesms", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
   String message = "hello world"; 
  request->send(200, "text/plain", message);
  });

   server.on("/page1", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   String message = "Welcome to page1"; 
  request->send(200, "text/plain", message);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
}
