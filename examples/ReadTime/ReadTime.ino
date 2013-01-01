/********************************************************************************
* DS1307 Library Examples- setAndReadTime.ino                                   *
*                                                                               *
* Copyright (C) 2013 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <Wire.h>
#include <DS1307.h>

DS1307 clock;

void setup()
{
	// Initialize Serial
	Serial.begin(9600);
	
	// Initialize clock
	clock.begin();
}

void loop()
{
	DS1307::time data;
	clock.read(data);

	// Print date
	if (data.date < 10)
	{
		Serial.print("0");
	}
	Serial.print(data.date);
	Serial.print("/");

	// Print month
	if (data.month < 10)
	{
		Serial.print("0");
	}
	Serial.print(data.month);
	Serial.print("/");
	
	// Print year
	Serial.print(data.year);
	Serial.print(" ");

	// Print hour
	if (data.hour < 10)
	{
	Serial.print("0");
	}
	Serial.print(data.hour);
	Serial.print(":");

	// Pirnt minutes
	if (data.minutes < 10)
	{
		Serial.print("0");
	}
	Serial.print(data.minutes);
	Serial.print(":");

	// Print seconds
	if (data.seconds < 10)
	{
		Serial.print("0");
	}
	Serial.println(data.seconds);
	
	delay(1000);
}

