#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char *www_username = "admin";
const char *www_password = "esp8266";

void setup()
{
  Serial.begin(115200);
  ConnectWiFi();
  ArduinoOTA.begin();
  server.on("/status", handleStatus);

  server.begin();

  Serial.println();
  Serial.print(WiFi.localIP());
}

void loop()
{
  ArduinoOTA.handle();
  server.handleClient();
}
