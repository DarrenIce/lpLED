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
		0x10,0x25,					//0 - ����ʱ��	1 - ���ù��
		0x26,0x21,					//2 - ��ɫ��ʾ	3 - ȡ����ʾ
		0x27,0xF6,					//4 - ��ʱ��ʾ	5 - ʱ����ʾ
		0x51,0x53,					//6 - ��滻ҳ	7 - �ַ���ɫ
		0x54,0x55					//8 - ��ɫ�任	9 - ��ɫ�任
	};
	const unsigned char head[2] = {0xAA,0x55};
	const unsigned char reserved[3] = { 0x03,0x64,0x00 };
	unsigned char com;
	unsigned char len[2];
	unsigned char *data;
	unsigned char checksum[2];
	const unsigned char end = 0xAF;

};