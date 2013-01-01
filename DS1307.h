/********************************************************************************
* DS1307 Library - DS1307.h                                                     *
*                                                                               *
* Copyright (C) 2013 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#ifndef _DS1307_H
#define _DS1307_H

#include <Arduino.h>

class DS1307
{
	public:
		
		struct time
		{
			int seconds;
			int minutes;
			int hour;
			int day;
			int date;
			int month;
			int year;
		};
		
		enum SQW_Freq
		{
			SQW_1HZ   = 0,
			SQW_4kHZ  = 1,
			SQW_8kHZ  = 2,
			SQW_32kHZ = 3,
		};
		
	private:
		// Devices address
		static const int ADDRESS  = 0x68;
		
		// Calibration coefficients addresses
		static const int REG_SEC   = 0x00;
		static const int REG_MIN   = 0x01;
		static const int REG_HOUR  = 0x02;
		static const int REG_DAY   = 0x03;
		static const int REG_DATE  = 0x04;
		static const int REG_MONTH = 0x05;
		static const int REG_YEAR  = 0x06;
		static const int REG_CTRL  = 0x07;

		// Calibration coefficients variables
		bool output, outputLevel;
		SQW_Freq outputFreq;
		
		int readRegister(byte reg_addr, int nbytes, byte *buffer);
		int writeRegister(byte reg_addr, int nbytes, byte *buffer);
		
		void setControl();
		byte getControl();
		
		byte bcdToDec(byte data);
		byte decToBcd(byte data);
		
	public:
		
		DS1307();
	
		void begin();
		void end();
	
		void read(time &data);
		void write(time &data);
		
//		void set24hour(bool state);
		bool getOutput();
		void setOutput(bool state);
		
		SQW_Freq getOutputFreq();
		void setOutputFreq(SQW_Freq frequency);
		
		bool getOutputLevel();
		void setOutputLevel(bool state);
};

#endif // _DS1307_H
