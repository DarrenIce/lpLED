#pragma once
#include "SerialPort.h"

typedef unsigned char BYTE;

const unsigned char CTRL_HEADER[2] = { 0xAA,0x55 };			//传输头
const unsigned char CTRL_RESERVED[3] = { 0x01,0x02,0x03 };	//保留字
const unsigned char CTRL_END = 0xAF;						//结束标志符

const unsigned int MAX_DATA_LEN = 1040;						//报文最大长度

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
	LED();
	bool ShowCommand();																	//显示命令
	void SetTime(int* date);															//设置时间
	void SetAd(BYTE line_num, BYTE color, BYTE* context);								//设置彩色广告
	void ColoredDisplay(BYTE line_num, BYTE time, BYTE color, BYTE* context);			//彩色显示
	void CancelDisplay(BYTE line_num);													//取消显示
	void TimingDisplay(BYTE line_num, BYTE time, BYTE color, BYTE* context);			//带定时的彩色显示
	void TimeDisplay(BYTE line_num, BYTE color);										//设置时间显示模式
	void SetAdChangeMode(BYTE line_num,BYTE mode);										//设置广告换页模式
	void SetCharColor(BYTE line_num, int *color);										//设置字符颜色
	void LineColorTrans(BYTE line_num);													//设置行颜色变换
	void CharColorTrans(BYTE line_num, int *color);										//设置字符颜色变换
	void PackageCommand(Command com, BYTE* data, int cursor, BYTE* buffer, int *size);	//打包函数
	BYTE* Crc16(BYTE* buffer,int size);													//Crc16校验，查表法计算校验和
	void Send(BYTE* buf,int* len);
	~LED();
private:
	BYTE* buffer;
	int size;
};

