#pragma once
#include "SerialPort.h"

typedef unsigned char BYTE;

const unsigned char CTRL_HEADER[2] = { 0xAA,0x55 };			//����ͷ
const unsigned char CTRL_RESERVED[3] = { 0x01,0x02,0x03 };	//������
const unsigned char CTRL_END = 0xAF;						//������־��

const unsigned int MAX_DATA_LEN = 1040;						//������󳤶�

enum Command
{
	COM_SET_TIME = 0x10,			//0x10 - ����ʱ��
	COM_SET_AD = 0x25,				//0x25 - ���ò�ɫ���
	COM_COLORED_DISPLAY = 0x26,		//0x26 - ��ɫ��ʾ
	COM_CANCEL_DISPLAY = 0x21,		//0x21 - ȡ����ʾ
	COM_TIMING_DISPLAY = 0x27,		//0x27 - ����ʱ�Ĳ�ɫ��ʾ
	COM_TIME_DISPLAY = 0xF6,		//0xF6 - ����ʱ����ʾģʽ
	COM_ADPAGE_CHANGE = 0x51,		//0x51 - ���ù�滻ҳģʽ
	COM_CHAR_COLOR = 0x53,			//0x53 - �����ַ���ɫ
	COM_LINE_COLOR = 0x54,			//0x54 - ��������ɫ�任
	COM_COLOR_CHANGE = 0x55			//0x55 - �����ַ���ɫ�任
};

class LED {
public:
	LED();
	bool ShowCommand();																	//��ʾ����
	void SetTime(int* date);															//����ʱ��
	void SetAd(BYTE line_num, BYTE color, BYTE* context);								//���ò�ɫ���
	void ColoredDisplay(BYTE line_num, BYTE time, BYTE color, BYTE* context);			//��ɫ��ʾ
	void CancelDisplay(BYTE line_num);													//ȡ����ʾ
	void TimingDisplay(BYTE line_num, BYTE time, BYTE color, BYTE* context);			//����ʱ�Ĳ�ɫ��ʾ
	void TimeDisplay(BYTE line_num, BYTE color);										//����ʱ����ʾģʽ
	void SetAdChangeMode(BYTE line_num,BYTE mode);										//���ù�滻ҳģʽ
	void SetCharColor(BYTE line_num, int *color);										//�����ַ���ɫ
	void LineColorTrans(BYTE line_num);													//��������ɫ�任
	void CharColorTrans(BYTE line_num, int *color);										//�����ַ���ɫ�任
	void PackageCommand(Command com, BYTE* data, int cursor, BYTE* buffer, int *size);	//�������
	BYTE* Crc16(BYTE* buffer,int size);													//Crc16У�飬�������У���
	void Send(BYTE* buf,int* len);
	~LED();
private:
	BYTE* buffer;
	int size;
};

