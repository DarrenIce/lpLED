#pragma once
#include "SerialPort.h"

typedef unsigned char BYTE;

const unsigned char CTRL_HEADER[2] = { 0xAA,0x55 };
const unsigned char CTRL_RESERVED[3] = { 0x01,0x02,0x03 };
const unsigned char CTRL_END = 0xAF;

const unsigned char MAX_DATA_LEN = 255;

class LED {
public:
	bool ShowCommand();
	void SetTime();
	void SetAd();
	void Init();
	void ColoredDisplay();
	void CancelDisplay();
	void TimingDisplay();
	void TimeDisplay();
	void SetAdChangeMode();
	void SetCharColor();
	void LineColorTrans();
	void CharColorTrans();
	std::string StringToHex(std::string str);
	std::string HexToStr(std::string str);
	BYTE* Assemble();
	void Crc16();
	void LengthAndCrc(int Len);
	std::string ToHex(int dec);
	int getlen();
private:
	BYTE com;
	BYTE len[2];
	BYTE* data;
	BYTE checksum[2];
	int length;
	int cursor;
};

enum Command
{
	COM_SET_TIME			 = 0x10,
	COM_SET_AD				 = 0x25,
	COM_COLORED_DISPLAY		 = 0x26,
	COM_CANCEL_DISPLAY		 = 0x21,
	COM_TIMING_DISPLAY		 = 0x27,
	COM_TIME_DISPLAY		 = 0xF6,
	COM_ADPAGE_CHANGE		 = 0x51,
	COM_CHAR_COLOR			 = 0x53,
	COM_LINE_COLOR			 = 0x54,
	COM_COLOR_CHANGE		 = 0x55
};