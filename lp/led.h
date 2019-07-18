#pragma once
#include "SerialPort.h"
class LED {
public:
	void show();
	void setad();
	std::string StringToHex(std::string str);
	std::string HexToStr(std::string str);
	unsigned char* AssBefore();
	unsigned char* AssAfter();
	unsigned short crc16(unsigned char* ass);
private:
	const unsigned char command[10] =
	{
		0x10,0x25,					//0 - 设置时间	1 - 设置广告
		0x26,0x21,					//2 - 彩色显示	3 - 取消显示
		0x27,0xF6,					//4 - 定时显示	5 - 时间显示
		0x51,0x53,					//6 - 广告换页	7 - 字符颜色
		0x54,0x55					//8 - 行色变换	9 - 字色变换
	};
	const unsigned char head[2] = {0xAA,0x55};
	const unsigned char reserved[3] = { 0x03,0x64,0x00 };
	unsigned char com;
	unsigned char len[2];
	unsigned char *data;
	unsigned char checksum[2];
	const unsigned char end = 0xAF;

};