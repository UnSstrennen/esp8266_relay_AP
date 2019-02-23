#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "Light" ;

WiFiServer server(80);

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";

String request = "";
int LED_Pin = 0;
bool state = true;

void setup()
{
  pinMode(LED_Pin, OUTPUT);
  digitalWrite(LED_Pin, state);
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();
}


void loop()
{

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)  {
    return;
  }

  // Read the first line of the request
  request = client.readStringUntil('\r');

  if (request.indexOf("off") > 0 ) {
    state = false;
  }
  else if  ( request.indexOf("on") > 0 ) {
    state = true;
  }

  client.flush();
  client.print(header);
  if (!state) {
    client.print("включен");
  }
  else {
    client.print("выключен");
  }

  digitalWrite(LED_Pin, state);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
} // void loop()
