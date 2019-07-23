#pragma once
#include "SerialPort.h"

typedef unsigned char BYTE;

const unsigned char CTRL_HEADER[2] = { 0xAA,0x55 };			//传输头
const unsigned char CTRL_RESERVED[3] = { 0x01,0x02,0x03 };	//保留字
const unsigned char CTRL_END = 0xAF;						//结束标志符

const unsigned char MAX_DATA_LEN = 255;						//报文最大长度

enum Command
{
	COM_SET_TIME = 0x10,			//0x10 - 设置时间
	COM_SET_AD = 0x25,				//0x25 - 设置彩色广告
	COM_COLORED_DISPLAY = 0x26,		//0x26 - 彩色显示
	COM_CANCEL_DISPLAY = 0x21,		//0x21 - 取消显示
	COM_TIMING_DISPLAY = 0x27,		//0x27 - 带定时的彩色显示
	COM_TIME_DISPLAY = 0xF6,		//0xF6 - 设置时间显示模式
	COM_ADPAGE_CHANGE = 0x51,		//0x51 - 设置广告换页模式
	COM_CHAR_COLOR = 0x53,			//0x53 - 设置字符颜色
	COM_LINE_COLOR = 0x54,			//0x54 - 设置行颜色变换
	COM_COLOR_CHANGE = 0x55			//0x55 - 设置字符颜色变换
};

class LED {
public:
	bool ShowCommand(BYTE* buffer, int *size);			//显示命令
	void SetTime(BYTE* buffer, int *size);				//设置时间
	void SetAd(BYTE* buffer, int *size);				//设置彩色广告
	void ColoredDisplay(BYTE* buffer, int *size);		//彩色显示
	void CancelDisplay(BYTE* buffer, int *size);		//取消显示
	void TimingDisplay(BYTE* buffer, int *size);		//带定时的彩色显示
	void TimeDisplay(BYTE* buffer, int *size);			//设置时间显示模式
	void SetAdChangeMode(BYTE* buffer, int *size);		//设置广告换页模式
	void SetCharColor(BYTE* buffer, int *size);			//设置字符颜色
	void LineColorTrans(BYTE* buffer, int *size);		//设置行颜色变换
	void CharColorTrans(BYTE* buffer, int *size);		//设置字符颜色变换
	std::string HexToStr(std::string str);
	void PackageCommand(Command com, BYTE* data, int cursor, BYTE* buffer, int *size);	//打包函数
	BYTE* Crc16(BYTE* buffer,int size);					//crc16校验
	std::string ToHex(int dec);
};

