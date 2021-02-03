#include "Sheets.h"

static HTTPSRedirect* client = nullptr;
static bool flag = false;
static int errorCounter = 0;
static int connectCounter = 0;

Sheets::Sheets(char* host, char* GScriptId) : _host(host), _GScriptId(GScriptId) {
  _url1 = String("/macros/s/") + GScriptId + "/exec?value=Temperature";
  _url2 = String("/macros/s/") + GScriptId + "/exec?cal";

  client = new HTTPSRedirect();
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
}

void Sheets::connect() {
  bool flag = false;
  for (int i = 0; i < 5; i++){
    int retval = client->connect(_host, HTTPS_PORT);

    if (retval == 1) break;
    else Serial.println("Connection failed. Retrying...");
  }

  if (!client->connected()) {
    Serial.println("Could not connect to Google Sheets");
    return;
  }

  Serial.println("Connected to Google Sheets");

  delete client;
  client = nullptr;
}

void Sheets::writeRow(String commaSeparatedData) {
  String payloadBase =  "{\"command\": \"appendRow\", \"sheet_name\": \"data\", \"values\": \"";
  String payload = payloadBase + commaSeparatedData + "\"}";

  if (!flag){
    client = new HTTPSRedirect();
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  
  if (client == nullptr) { 
    Serial.println("Error creating client object!");
    errorCounter = 5;
  } else if (!client->connected()){
    client->connect(_host, HTTPS_PORT);
  }

  if (connectCounter > MAX_CONNECT) {
    connectCounter = 0;
    flag = false;
    delete client;
    return;
  }

  if (errorCounter > 3) {
    delete client;
    client = nullptr;

    Serial.printf("Final free heap: %u\n", ESP.getFreeHeap());
    Serial.printf("Final stack: %u\n", ESP.getFreeContStack());

    ESP.deepSleep(0);
  }
  
  if (client->POST(_url2, _host, payload, false)) Serial.println("Sent : " + payload);
  else Serial.println("Error sending data to Google Sheets");
}
