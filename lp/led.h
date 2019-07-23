#pragma once
#include "SerialPort.h"

typedef unsigned char BYTE;

const unsigned char CTRL_HEADER[2] = { 0xAA,0x55 };			//����ͷ
const unsigned char CTRL_RESERVED[3] = { 0x01,0x02,0x03 };	//������
const unsigned char CTRL_END = 0xAF;						//������־��

const unsigned char MAX_DATA_LEN = 255;						//������󳤶�

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
	bool ShowCommand(BYTE* buffer, int *size);			//��ʾ����
	void SetTime(BYTE* buffer, int *size);				//����ʱ��
	void SetAd(BYTE* buffer, int *size);				//���ò�ɫ���
	void ColoredDisplay(BYTE* buffer, int *size);		//��ɫ��ʾ
	void CancelDisplay(BYTE* buffer, int *size);		//ȡ����ʾ
	void TimingDisplay(BYTE* buffer, int *size);		//����ʱ�Ĳ�ɫ��ʾ
	void TimeDisplay(BYTE* buffer, int *size);			//����ʱ����ʾģʽ
	void SetAdChangeMode(BYTE* buffer, int *size);		//���ù�滻ҳģʽ
	void SetCharColor(BYTE* buffer, int *size);			//�����ַ���ɫ
	void LineColorTrans(BYTE* buffer, int *size);		//��������ɫ�任
	void CharColorTrans(BYTE* buffer, int *size);		//�����ַ���ɫ�任
	std::string HexToStr(std::string str);
	void PackageCommand(Command com, BYTE* data, int cursor, BYTE* buffer, int *size);	//�������
	BYTE* Crc16(BYTE* buffer,int size);					//crc16У��
	std::string ToHex(int dec);
};

