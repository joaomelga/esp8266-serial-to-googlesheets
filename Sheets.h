/*
 * Sheets.h
 * Copyright (C) João Melga <joaolucasfm@gmail.com>
 * 
 * Version 1.0 - API class with folowing implemented public functions:
 *  - Sheets(char*, char*);
 *  - void connect();
 *  - void writeRow(String);
 *  
 * Based on ESP8266_temprature_logging_to_Google_Sheet.ino simplementation accessed at:
 * https://circuitdigest.com/microcontroller-projects/log-temperature-sensor-data-to-google-sheet-using-nodemcu-esp8266
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

#ifndef SHEETS_H
#define SHEETS_H

#include <Wire.h>
#include <HTTPSRedirect.h>
#include <DebugMacros.h>

#define SHEETS_ERROR_STATE 0
#define SHEETS_CONNECTED_STATE 0

#define HTTPS_PORT 443
#define MAX_CONNECT 20

class Sheets {
  private:
    const char* _host;
    const char *_GScriptId;
    String _url1;
    String _url2;

  public:
    Sheets(char* host, char* GScriptId);
    void connect();
    void writeRow(String commaSeparatedData);
};

#endif // SHEETS_H
