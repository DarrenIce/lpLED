#pragma once
#include "SerialPort.h"
class LED {
public:
	LED()
	{
		char h[2] = { 0xAA,0x55 };
		head.assign(h,0,2);
		char r[2] = { 0x03,0x64};
		reserved.assign(r,0,2);
		char t = 0x00;
		reserved.push_back(t);
		char e[] = { 0xAF };
		end.assign(e,0,1);
	}
	void ShowCommand();
	void SetTime();
	void SetAd();
	void Init();
	void ColoredDisplay();
	void CancelDisplay();
	void TimeDisplay();
	std::string StringToHex(std::string str);
	std::string HexToStr(std::string str);
	std::string Assemble();
	void Crc16();
	std::string ToHex(int dec);
private:
	unsigned char command[10] =
	{
		0x10,0x25,					//0 - ����ʱ��	1 - ���ù��
		0x26,0x21,					//2 - ��ɫ��ʾ	3 - ȡ����ʾ
		0x27,0xF6,					//4 - ��ʱ��ʾ	5 - ʱ����ʾ
		0x51,0x53,					//6 - ��滻ҳ	7 - �ַ���ɫ
		0x54,0x55					//8 - ��ɫ�任	9 - ��ɫ�任
	};
	string head;
	string reserved;
	string com;
	string len;
	string data;
	string checksum;
	string end;

};