/*
 * esp8266-serial-to-googlesheets.ino
 * Copyright (C) João Melga <joaolucasfm@gmail.com>
 * 
 * Version 1.0
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
 * 
 * This software is designed to run under Arduino IDE.
 * To run the project you should:
 *  - Copy all files from ".../esp8266-serial-to-googlesheets/libraries" folder 
 *    to your Arduino IDE "libraries" folder
 *  - Install the ESP8266 board in your Arduino IDE. You can follow the tutotial above:
 *    Available on: https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/
 *  - Configure a spreadsheet in Google Sheets. You can follow the tutotial above:
 *    Available on: https://circuitdigest.com/microcontroller-projects/log-temperature-sensor-data-to-google-sheet-using-nodemcu-esp8266
 */

#include "Sheets.h"
#include "Network.h"

Network network("NET-NAME", "NET-PASS");
Sheets sheets("script.google.com", "YOUR-SHEET-CODE");

void setup() 
{
  Serial.begin(9600);
  network.connect();
  sheets.connect();
}

void loop() 
{
  if (Serial.available()) {
    Serial.println("Data received");
    delay(100);

    if (!network.isConnected()) network.connect();

    String commaSeparatedData  = Serial.readStringUntil('\0');
    commaSeparatedData.remove(commaSeparatedData.length() - 1);

    sheets.writeRow(commaSeparatedData);

    while (Serial.available() > 0) Serial.read();
  }
}
