/********************************************************************************
* DS1307 Library - DS1307.cpp                                                   *
*                                                                               *
* Copyright (C) 2013 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <DS1307.h>
#include <Wire.h>"

int DS1307::writeRegister(byte reg_addr, int nbytes, byte *buffer)
{
	int written_bytes;
	
	Wire.beginTransmission(DS1307::ADDRESS);
	Wire.write(reg_addr);
	written_bytes = Wire.write(buffer, nbytes);
	Wire.endTransmission();
	
	return written_bytes;
}

int DS1307::readRegister(byte reg_addr, int nbytes, byte *buffer)
{
	int idx = 0;

	Wire.beginTransmission(DS1307::ADDRESS);
	Wire.write(reg_addr);
	Wire.endTransmission(); 
	
	Wire.requestFrom(DS1307::ADDRESS, nbytes);

	while(Wire.available() && idx < nbytes)
	{ 
		buffer[idx++] = Wire.read();
	}
	
	return idx;
}

byte DS1307::getControl()
{
	byte control = 0;
	
	readRegister(DS1307::REG_CTRL, 1, &control);
	
	return control;
}

void DS1307::setControl()
{
	byte control = 0;
	
	control += (outputLevel ? 1 : 0) << 7;
	control += (output ? 1 : 0) << 4;
	control += outputFreq;
	
	writeRegister(DS1307::REG_CTRL, 1, &control);
}

byte DS1307::bcdToDec(byte data)
{
	return (data / 16) * 10 + (data % 16);
}

byte DS1307::decToBcd(byte data)
{
	return (data / 10 ) * 16 + (data % 10);
}
		
DS1307::DS1307()
{
	Wire.begin();
}

void DS1307::begin()
{
	byte hour;
	byte control = getControl();
	
	outputLevel = control & B10000000;
	output = control & B00010000;
	outputFreq = (SQW_Freq)(control & B00000011);
	
	readRegister(DS1307::REG_HOUR, 1, &hour);
	
	if ((hour & B01000000) > 0)
	{
		hour &= B00111111;
		writeRegister(DS1307::REG_HOUR, 1, &hour);
	}
}

void DS1307::end(){}

void DS1307::read(time &data)
{
	byte data_buffer[7];
	readRegister(DS1307::REG_SEC, 7, data_buffer);
	
	data.seconds = bcdToDec(data_buffer[0]);
	data.minutes = bcdToDec(data_buffer[1]);
	data.hour    = bcdToDec(data_buffer[2]);
	data.day     = bcdToDec(data_buffer[3]);
	data.date    = bcdToDec(data_buffer[4]);
	data.month   = bcdToDec(data_buffer[5]);
	data.year    = bcdToDec(data_buffer[6]);
}

void DS1307::write(time &data)
{
	byte data_buffer[7];
	
	data_buffer[0] = decToBcd((byte)data.seconds);
	data_buffer[1] = decToBcd((byte)data.minutes);
	data_buffer[2] = decToBcd((byte)data.hour);
	data_buffer[3] = decToBcd((byte)data.day);
	data_buffer[4] = decToBcd((byte)data.date);
	data_buffer[5] = decToBcd((byte)data.month);
	data_buffer[6] = decToBcd((byte)data.year);
	
	writeRegister(DS1307::REG_SEC, 7, data_buffer);
}

bool DS1307::getOutput()
{
	return output;
}

void DS1307::setOutput(bool state)
{
	output = state;
	setControl();
}

DS1307::SQW_Freq DS1307::getOutputFreq()
{
	return outputFreq;
}

void DS1307::setOutputFreq(SQW_Freq frequency)
{
	outputFreq = frequency;
	setControl();
}

bool DS1307::getOutputLevel()
{
	return outputLevel;
}

void DS1307::setOutputLevel(bool state)
{
	outputLevel = state;
	setControl();
}
