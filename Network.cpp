#include "Network.h"

Network::Network(char* ssid, char* password) : _ssid(ssid), _password(password) {}

void Network::connect() {  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Trying to connect WiFI");
    WiFi.begin(_ssid, _password);
  }

  long unsigned int initialTimestamp = millis();
  long unsigned int currentTimestamp = millis();

  while (WiFi.status() != WL_CONNECTED || currentTimestamp - initialTimestamp < 5000) {
    currentTimestamp = millis();
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED) WiFi.disconnect();

  _ip = WiFi.localIP();
}

String Network::getStatusMessage() {
  switch (WiFi.status())
  {
    case WL_CONNECTED:
      return "Connected";
      break;

    case WL_NO_SSID_AVAIL:
      return "Network not availible";
      break;

    case WL_CONNECT_FAILED:
      return "Wrong password";
      break;

    case WL_IDLE_STATUS:
      return "Idle status";
      break;

    case WL_DISCONNECTED:
      return "Disconnected";
      break;

    default:
      return "Unknown";
      break;
  }
}
