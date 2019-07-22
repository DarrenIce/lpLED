#include "led.h"
using namespace std;

static const unsigned char aucCRCHi[] =
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40
};
static const unsigned char aucCRCLo[] =
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
	0x41, 0x81, 0x80, 0x40
};

void LED::Init()
{
	length = 0;
	cursor = 0;
	data = new BYTE[MAX_DATA_LEN];
}

bool LED::ShowCommand()
{
	int i = 0;
	system("cls");
	cout << "������Ҫִ�е�����: " << endl
		<< "0 - ����ʱ��	1 - ���ù��" << endl
		<< "2 - ��ɫ��ʾ	3 - ȡ����ʾ" << endl
		<< "4 - ��ʱ��ʾ	5 - ʱ����ʾ" << endl
		<< "6 - ��滻ҳ	7 - �ַ���ɫ" << endl
		<< "8 - ��ɫ�任	9 - ��ɫ�任" << endl
		<< "10 - �˳�" << endl;
	cin >> i;
	switch (i)
	{
	case 0:
		SetTime();
		return true;
	case 1:
		SetAd();
		return true;
	case 2:
		ColoredDisplay();
		return true;
	case 3:
		CancelDisplay();
		return true;
	case 4:
		TimingDisplay();
		return true;
	case 5:
		TimeDisplay();
		return true;
	case 6:
		SetAdChangeMode();
		return true;
	case 7:
		SetCharColor();
		return true;
	case 8:
		LineColorTrans();
		return true;
	case 9:
		CharColorTrans();
		return true;
	default:
		return false;
	}
}

void LED::SetAd()
{
	Init();
	com = COM_SET_AD;
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	//ss << setw(2) << setfill('0') << temp;
	//temp=HexToStr(ss.str());
	data[cursor++] = temp[0]-'0';
	//ss.clear();
	//temp.clear();
	//ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	//ss << setw(2) << setfill('0') << temp << "01";
	//temp = HexToStr(ss.str());
	//for (int i = 0; i < 2; i++)
		//data[cursor++] = temp[i];
	data[cursor++] = temp[0] - '0';
	data[cursor++] = 0x00;
	//ss.clear();
	//ss.str("");
	cout << "1 - ����������, 2 - ������ : ";
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		cout << "������������: ";
		BYTE* context = new BYTE[MAX_DATA_LEN];
		cin >> context;
		for (int j = 0; j < strlen((char*)context);j++)
		{
			data[cursor++] = context[j];
		}
		delete[]context;
	}
	LengthAndCrc(cursor);
}

string LED::StringToHex(string str)
{
	const string hex = "0123456789ABCDEF";
	stringstream ss;
	for (int i = 0; i< str.size(); i++)
	{
		ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf];
	}
	return ss.str();
}

string LED::HexToStr(string str)
{
	std::string result;
	for (size_t i = 0; i<str.length(); i += 2)
	{
		std::string byte = str.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		result.push_back(chr);
	}
	return result;
}

void LED::Crc16()
{
	BYTE *temp = new BYTE[MAX_DATA_LEN];
	int lent = 0;
	for (int i = 0; i < 3; i++)
		temp[lent++] = CTRL_RESERVED[i];
	temp[lent++] = com;
	for (int i = 0; i < 2; i++)
		temp[lent++] = len[i];
	for (int i = 0; i < length-11; i++)
		temp[lent++] = data[i];
	for (int i = 0; i < 2; i++)
		temp[lent++] = 0x00;
	unsigned char temp_high = 0xFF,temp_low=0xFF;
	int index = 0;
	for (int i = 0; i < lent; i++)
	{
		index = (unsigned char)temp[i]^temp_low;
		temp_low = temp_high ^ aucCRCHi[index];
		temp_high = aucCRCLo[index];
	}
	checksum[0] = temp_high;
	checksum[1] = temp_low;
	delete []temp;
}

BYTE* LED::Assemble()
{
	BYTE *temp = new BYTE[MAX_DATA_LEN];
	int lent = 0;
	for (int i = 0; i < 2; i++)
		temp[lent++] = CTRL_HEADER[i];
	for (int i = 0; i < 3; i++)
		temp[lent++] = CTRL_RESERVED[i];
	temp[lent++] = com;
	for (int i = 0; i < 2; i++)
		temp[lent++] = len[i];
	for (int i = 0; i < length-11; i++)
		temp[lent++] = data[i];
	for (int i = 0; i < 2; i++)
		temp[lent++] = checksum[i];
	temp[lent++] = CTRL_END;
	//length = lent;
	return temp;
}

string LED::ToHex(int dec)
{
	string res;
	const string hex = "0123456789ABCDEF";
	res.push_back(hex[dec / 16]);
	res.push_back(hex[dec % 16]);
	return res;
}

void LED::LengthAndCrc(int Len)
{
	length = Len + 11;
	string temp;
	stringstream ss;
	ss << setw(4) << setfill('0') << ToHex(Len);
	temp = HexToStr(ss.str());
	for (int i = 0; i < 2; i++)
		len[i] = temp[i];
	Crc16();
}

int LED::getlen()
{
	return length;
}

void LED::ColoredDisplay()
{
	Init();
	com = COM_COLORED_DISPLAY;
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	ss.clear();
	ss.str("");
	cout << "��������ʾʱ�� (0-255) : ";
	int time;
	cin >> time;
	temp = HexToStr(ToHex(time));
	data[cursor++] = temp[0];
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp<<"00";
	temp = HexToStr(temp);
	for (int i = 0; i < 2; i++)
		data[cursor++] = temp[i];
	ss.clear();
	ss.str("");
	cout << "��������ʾ����: ";
	BYTE* context = new BYTE[MAX_DATA_LEN];
	cin >> context;
	for (int j = 0; j < strlen((char*)context); j++)
	{
		data[cursor++] = context[j];
	}
	delete[]context;
	LengthAndCrc(cursor);
}

void LED::CancelDisplay()
{
	Init();
	com = COM_CANCEL_DISPLAY;
	cout << "������Ҫȡ�����к�: (3/4)";
	int i;
	cin >> i;
	unsigned char line[] = { 0x00,0x01,0x02,0x04,0x08 };
	while (i < 2 || i>5)
	{
		cout << "��Ч���к�, ����������: ";
		cin >> i;
	}
	data[cursor++] = line[i];
	LengthAndCrc(cursor);
}

void LED::TimeDisplay()
{
	Init();
	com = COM_TIME_DISPLAY;
	string temp;
	stringstream ss;
	cout << "�������к� (0/3/4, 0Ϊ����ʾʱ��) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp << "00";
	temp = HexToStr(ss.str());
	for (int i = 0; i < 2; i++)
		data[cursor++] = temp[i];
	LengthAndCrc(cursor);
}

void LED::SetTime()
{
	Init();
	com = COM_SET_TIME;
	int date[6];
	cout << "���������� (������ʱ����, ��+2000��Ϊ���) : ";
	for (int i = 0; i < 6; i++)
	{
		cin >> date[i];
		string temp = HexToStr(ToHex(date[i]));
		data[cursor++] = temp[0];
	}
	LengthAndCrc(cursor);
}

void LED::SetCharColor()
{
	Init();
	com = COM_CHAR_COLOR;
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	int color[8];
	cout << "������ÿ���ֽڵ���ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) : ";
	for (int i = 0; i < 8; i++)
	{
		cin >> color[i];
		temp = HexToStr(ToHex(color[i]));
		data[cursor++] = temp[0];
	}
	LengthAndCrc(cursor);
}

void LED::LineColorTrans()
{
	Init();
	com = COM_LINE_COLOR;
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	LengthAndCrc(cursor);
}

void LED::CharColorTrans()
{
	Init();
	com = COM_COLOR_CHANGE;
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	int color[2];
	cout << "������ǰ��ɫ�ͱ���ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) : ";
	for (int i = 0; i < 2; i++)
	{
		cin >> color[i];
		temp = HexToStr(ToHex(color[i]));
		data[cursor++] = temp[0];
	}
	LengthAndCrc(cursor);
}

void LED::TimingDisplay()
{
	Init();
	com = COM_TIMING_DISPLAY;
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	ss.clear();
	ss.str("");
	cout << "��������ʾʱ�� (0-255) : ";
	int time;
	cin >> time;
	temp = HexToStr(ToHex(time));
	data[cursor++] = temp[0];
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp<<"00";
	temp = HexToStr(ss.str());
	for (int i = 0; i < 2; i++)
		data[cursor++] = temp[i];
	ss.clear();
	ss.str("");
	cout << "��������ʾ����: ";
	BYTE* context = new BYTE[MAX_DATA_LEN];
	cin >> context;
	for (int j = 0; j < strlen((char*)context); j++)
	{
		data[cursor++] = context[j];
	}
	delete[]context;
	LengthAndCrc(cursor);
}

void LED::SetAdChangeMode()
{
	Init();
	com = COM_ADPAGE_CHANGE;
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = HexToStr(ss.str());
	data[cursor++] = temp[0];
	char mode[] = {
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13
	};
	cout << "�����뻻ҳģʽ" << endl
		<< "0 - �����������ģʽ" << endl
		<< "1 - �·�ҳ(�ƶ�)" << endl
		<< "2 - �·�ҳ(����)" << endl
		<< "3 - �·�ҳ(���)" << endl
		<< "4 - �·�ҳ(�հ�)" << endl
		<< "5 - �Ϸ�ҳ(�ƶ�)" << endl
		<< "6 - �Ϸ�ҳ(����)" << endl
		<< "7 - �Ϸ�ҳ(���)" << endl
		<< "8 - �Ϸ�ҳ(�հ�)" << endl
		<< "9 - ��ˢ(����)" << endl
		<< "10 - ��ˢ(���)" << endl
		<< "11 - �һ�ˢ(����)" << endl
		<< "12 - �һ�ˢ(���)" << endl
		<< "13 - ����ʽ(����)" << endl
		<< "14 - ����ʽ(���)" << endl
		<< "15 - ����ʽ(����)" << endl
		<< "16 - ����ʽ(���)" << endl
		<< "17 - ҳ�л�ģʽ" << endl
		<< "18 - ���ҽ����ҳ�л�ģʽ" << endl
		<< "19 - ����ģʽ" << endl;
	int i;
	cin >> i;
	data[cursor++] = mode[i];
	LengthAndCrc(cursor);
}