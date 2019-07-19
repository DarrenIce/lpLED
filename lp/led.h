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
		0x10,0x25,					//0 - 设置时间	1 - 设置广告
		0x26,0x21,					//2 - 彩色显示	3 - 取消显示
		0x27,0xF6,					//4 - 定时显示	5 - 时间显示
		0x51,0x53,					//6 - 广告换页	7 - 字符颜色
		0x54,0x55					//8 - 行色变换	9 - 字色变换
	};
	string head;
	string reserved;
	string com;
	string len;
	string data;
	string checksum;
	string end;

};