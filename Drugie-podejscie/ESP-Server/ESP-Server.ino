#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "HP-Laser-Jet-Pro-2400XD";
const char* password = "i2137Carly";

const char* PARAM_INPUT = "value";

AsyncWebServer server(80);

IPAddress local_IP(192, 168, 0, 184);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

#include "wifi.h"

void setup() {
    Serial.begin(115200);
    WiFi.config(local_IP,gateway,subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", index_html);
        });

    server.on("/data", HTTP_GET, [](AsyncWebServerRequest* request) {
        String inputMessage;
        if (request->hasParam(PARAM_INPUT)) {
            inputMessage = request->getParam(PARAM_INPUT)->value();
        }
        else {
            inputMessage = "No message sent";
        }
        Serial.println(inputMessage);
        request->send(200, "text/plain", "OK");
        });
    server.begin();
}
void loop() {
}
