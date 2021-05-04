/* 
 *  This example code will demonstrate the usage of webserver.
 *  It uses your wifi network and starts a server @ ip address given by your dns & dhcp.
 *  Steps.
 *  include wifi.h for wifi drivers.
 *  include wifi client to connect to accesspoints.
 *  include webserver for using webserver
 *  
 *  WebServer server(80); // define object and port for webserver.
 *  root(); contans your webpage content.parse it before using it.
 *  server.on("/inline", []() {}); // inline service methods for single line of webhosting. Param: path, string[parser]
 *  server.on("path",directory); // start server at path and define your server content using directory.
 *  server.begin(); //actually starts a server @ port
 *  server.handleClient(); //searches for client connections and handles the routing.
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include<ESPmDNS.h>

const char *ssid = "sunil";
const char *password = "8790225440";

WebServer server(80);

void root() {
  // set you code in string and parse it to the webserver
  String content = "<html><body><h1>webpage</h1><p> Hello World </p></body></html>";
  server.send(200, "text/html", content);
}
void message()
{
String msg = "welcome to the world"; 
  server.send(200, "text/plain", msg);
}
void setup() {
  Serial.begin(115200);

 /* 
  WiFi.softAP("techiesms", "");
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

  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }

  /* uncomment to use inline webpages
     For inline webservice use this

      server.on("/inline", []() {
      server.send(200, "text/plain", "this works as well");
    });
  */

//  uncomment to use specfic content into webpages
  //   for specific webservice callback methods use this
     //server.on("/", root);

     /* server.on("/", [](AsyncWebServerRequest * request)
  { 
   String message = "hello world"; 
  request->send(200, "text/plain", message);
  });

   server.on("/page1", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   String message = "Welcome to page1"; 
  request->send(200, "text/plain", message);
  });
  */

  //server.on("/",message);

  server.on("/",root);

  server.on("/inline", []() {
      server.send(200, "text/plain", "Welcome to page-1");
    });

  

  server.begin();
}

void loop()
{
  server.handleClient();
}
