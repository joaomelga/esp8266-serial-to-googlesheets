/*
 * Network.h
 * Copyright (C) João Melga <joaolucasfm@gmail.com>
 * 
 * Version 1.0 - API class with folowing implemented public functions:
 *  - Network(char*, char*);
 *  - void connect();
 *  - uint8_t isConnected();
 *  - uint8_t getStatus();
 *  - String getStatusMessage();
 * 
 * This software controls an ESP8266 microcontroller to receive comma 
 * separated data (ex: "first_data,another_one,etc") via UART and send
 * it to Google Sheets as a row with multiple columns.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the Licence, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Se the
 * GNU General Public Licence for more details.
 * 
 * Created on: feb-03-2020
 */


#ifndef NETWORK_H
#define NETWORK_H

#include <Wire.h>
#include <ESP8266WiFi.h>

class Network {
  private:
    const char* _ssid;
    const char* _password;
    IPAddress _ip;

  public:
    Network(char* ssid, char* password);
    void connect();
    uint8_t isConnected() { return WiFi.status() == WL_CONNECTED; };
    uint8_t getStatus() { return WiFi.status(); };
    String getStatusMessage();
};

#endif // NETWORK_H
