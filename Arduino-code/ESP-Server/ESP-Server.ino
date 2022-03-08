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

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <!-- disable zoom on safari -->
  <meta name="viewport" content="width=device-width, user-scalable=no" />

  <title>Remote Control</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
  <script src="https://kit.fontawesome.com/bbf2e2cb07.js" crossorigin="anonymous"></script>
  <style>
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }

    .container {
      background: #e5e5e5;
      border-radius: 30px;
      height: 650px;
      width: 350px;
    }

    div.menu-grid {
      display: grid;
      grid-template-columns: auto auto auto;
      border-bottom: 1px solid #c2c1c1;
      border-left: 1px solid #c2c1c1;
    }

    div.menu-grid>div {
      padding: 10px 35px;
      border-top: 1px solid #c2c1c1;
      border-right: 1px solid #c2c1c1;
    }

    div.menu-grid>div:hover {
      border-top: 1px solid #a10000;
    }

    div.menu-grid>div:active {
      background: #c2c1c1;
    }

    div.Round-button {
      border-top: 1px solid #e5e5e5;
      border-bottom: 1px solid #e5e5e5;
    }

    div.Round-button:hover {
      border-top: 1px solid #a10000;
      border-bottom: 1px solid #a10000;
    }

    div.Round-buttonalt>div:active {
      background: #c2c1c1;
    }

    span.label {
      font-size: 12px;
      color: #8e8e8e;
    }

    div.menu-grid>div>i {
      color: #2e2e2e;
      font-size: 1.2em;
      margin-bottom: 5px;
    }

    div.menu-grid>div>i.active {
      color: #d51600;
    }

    div.rounded-bg {
      background: #d9d9d9;
      border-radius: 50px;
    }

    div.grey-bg {
      background: #d9d9d9;
      border-radius: 50%;
    }

    i.home-icon {
      font-size: 24px;
      color: #a1a1a1;
    }

    i.control-icon {
      font-size: 24px;
      color: #2e2e2e;
    }


    div.circle {
      border: 1px solid #c2c1c1;
      border-radius: 50%;
    }

    div.ok-inner {
      padding: 30px;
    }

    div.ok-inner:hover {
      border-top: 1px solid #d51600;
      border-bottom: 1px solid #d51600;
    }

    div.ok-inner:active {
      background: #c2c1c1;
    }

    div.ok-outer {
      padding: 100px;
    }

    i.right {
      transform: translate(67px);
      font-size: 40px;
    }

    i.right:active {
      font-size: 32px;
    }

    i.bottom {
      transform: rotate(90deg) translate(67px);
      font-size: 40px;
    }

    i.bottom:active {
      font-size: 32px;
    }

    i.left {
      transform: rotate(180deg) translate(67px);
      font-size: 40px;
    }

    i.left:active {
      font-size: 32px;
    }

    i.top {
      transform: rotate(270deg) translate(67px);
      font-size: 40px;
    }

    i.top:active {
      font-size: 32px;
    }
  </style>
</head>

<body>
  <!--container-->
  <div class="container">
    <div class="d-flex flex-row justify-content-between px-3 py-4 align-items-center">
      <span>ESP8266 Remote</span>
    </div>

    <div class="d-flex flex-row justify-content-center">
      <div class="menu-grid">
        <div id="a" class="d-flex flex-column align-items-center" onclick="Clicked(this)">
          <i class="fas fa-power-off"></i>
          <span class="label">Power</span>
        </div>
        <div id="b" class="d-flex flex-column align-items-center" onclick="Clicked(this)">
          <i class="fas fa-volume-mute"></i>
          <span class="label">Mute</span>
        </div>
        <div id="c" class="d-flex flex-column align-items-center" onclick="Clicked(this)">
          <i class="fas fa-plug"></i>
          <span class="label">AC</span>
        </div>
      </div>
    </div>

    <div class="d-flex flex-row mt-4 justify-content-between px-2">

      <div class="Round-button d-flex flex-column rounded-bg py-3 px-4 justify-content-center align-items-center">
        <div id="d" onclick="Clicked(this)">
          <i class="fab py-3 control-icon fa-youtube"></i>
        </div>
        <span class="label py-3">Player</span>
        <div id="e" onclick="Clicked(this)">
          <i class="fas py-3 control-icon">N</i>
        </div>
      </div>

      <div class="Round-buttonalt d-flex flex-column align-items-center">
        <div id="f" class=" d-flex flex-row grey-bg justify-content-center align-items-center" onclick="Clicked(this)">
          <i class="fas fa-home p-3 home-icon"></i>
        </div>
        <span class="label">Home</span>
      </div>

      <div class="Round-button d-flex flex-column rounded-bg py-3 px-4 justify-content-center align-items-center">
        <div id="g" onclick="Clicked(this)">
          <i class="fas fa-plus py-3 control-icon"></i>
        </div>
        <span class="label py-3">Volume</span>
        <div id="h" onclick="Clicked(this)">
          <i class="fas fa-minus py-3 control-icon"></i>
        </div>
      </div>
    </div>

    <div class="mt-5 pt-4 position-relative d-flex flex-row justify-content-center align-items-center">
      <div class="circle ok-outer position-absolute"></div>
      <div id="i" class="position-absolute" onclick="Clicked(this)">
        <i class="fas fa-caret-right control-icon right"></i>
      </div>
      <div id="j" class="position-absolute" onclick="Clicked(this)">
        <i class="fas fa-caret-right control-icon bottom"></i>
      </div>
      <div id="k" class="position-absolute" onclick="Clicked(this)">
        <i class="fas fa-caret-right control-icon left"></i>
      </div>
      <div id="l" class="position-absolute" onclick="Clicked(this)">
        <i class="fas fa-caret-right control-icon top"></i>
      </div>
      <div id="m" onclick="Clicked(this)" class="circle ok-inner position-absolute">
        <span>OK</span>
      </div>
    </div>

    <div class="Round-buttonalt d-flex flex-row justify-content-between mt-5 pt-4 px-3">
      <div id="n" class="py-3 px-3 d-flex flex-row grey-bg" onclick="Clicked(this)">
        <i class="fas fa-undo"></i>
      </div>
      <div id="o" class="py-3 px-3 d-flex flex-row grey-bg" onclick="Clicked(this)">
        <i class="fas fa-door-open"></i>
      </div>
    </div>
  </div>
  <script>
    function Clicked(element) {
      window.navigator = window.navigator || {};
      if (window.navigator && window.navigator.vibrate) {
        navigator.vibrate(50);
      } else {
      }
      console.log(element.id);
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/data?value=" + element.id, true);
      xhr.send();
    }
  </script>
</body>

</html>
    )rawliteral";


void setup() {
    Serial.begin(115200);
    WiFi.config(local_IP,gateway,subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        //Serial.println("Connecting to WiFi..");
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
