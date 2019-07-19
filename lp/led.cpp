#include "led.h"
using namespace std;

void LED::SetAd()
{
	Init();
	com.assign((char*)command,1,1);
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data=HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str()+"00";
	data=data+HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "1 - ����������, 2 - ������ : ";
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		cout << "������������: ";
		cin >> temp;
		data = data + temp;
	}
	LengthAndCrc();
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
	string temp = reserved + com + len + data;
	char c = 0x00;
	temp.push_back(c);
	temp.push_back(c);
	unsigned int crc = 0xffff;
	unsigned char temp_low = 0x00;
	for (int i = 0; i < temp.size(); i++)
	{
		crc ^= (unsigned char)temp[i];
		for (int j = 0; j < 8; j++)
		{
			if (crc & 0x0001)
				crc = crc >> 1 ^ 0xa001;
			else
				crc >>= 1;
		}
		temp_low = crc >> 8;
	}
	unsigned char temp_high = (crc << 8)>>8;
	checksum.push_back(temp_low);
	checksum.push_back(temp_high);
}

string LED::Assemble()
{
	return head + reserved + com + len + data + checksum + end;
}

void LED::ColoredDisplay()
{
	Init();
	com.assign((char*)command, 2, 1);
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "��������ʾʱ�� (0-255) : ";
	int time;
	cin >> time;
	data += HexToStr(ToHex(time));
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str() + "00";
	data = data + HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "��������ʾ����: ";
	cin >> temp;
	data = data + temp;
	LengthAndCrc();
}

string LED::ToHex(int dec)
{
	string res;
	const string hex = "0123456789ABCDEF";
	res.push_back(hex[dec / 16]);
	res.push_back(hex[dec % 16]);
	return res;
}

void LED::CancelDisplay()
{
	Init();
	com.assign((char*)command, 3, 1);
	cout << "������Ҫȡ�����к�: (3/4)";
	int i;
	cin >> i;
	unsigned char line[] = { 0x00,0x01,0x02,0x04,0x08 };
	while (i < 2 || i>5)
	{
		cout << "��Ч���к�, ����������: ";
		cin >> i;
	}
	data.push_back(line[i]);
	LengthAndCrc();
}

void LED::Init()
{
	com.clear();
	len.clear();
	data.clear();
	checksum.clear();
}

void LED::TimeDisplay()
{
	Init();
	com.assign((char*)command, 5, 1);
	string temp;
	stringstream ss;
	cout << "�������к� (0/3/4, 0Ϊ����ʾʱ��) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str() + "00";
	data = data + HexToStr(temp);
	LengthAndCrc();
}

void LED::SetTime()
{
	Init();
	com.assign((char*)command, 0, 1);
	int date[6];
	cout << "���������� (������ʱ����, ��+2000��Ϊ���) : ";
	for (int i = 0; i < 6; i++)
	{
		cin >> date[i];
		data += HexToStr(ToHex(date[i]));
	}
	LengthAndCrc();
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

void LED::LengthAndCrc()
{
	string temp;
	stringstream ss;
	ss << setw(4) << setfill('0') << ToHex(data.size());
	temp = ss.str();
	len = HexToStr(temp);
	Crc16();
}

void LED::SetCharColor()
{
	Init();
	com.assign((char*)command, 7, 1);
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	int color[8];
	cout << "������ÿ���ֽڵ���ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) : ";
	for (int i = 0; i < 8; i++)
	{
		cin >> color[i];
		data += HexToStr(ToHex(color[i]));
	}
	LengthAndCrc();
}

void LED::LineColorTrans()
{
	Init();
	com.assign((char*)command, 8, 1);
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	LengthAndCrc();
}

void LED::CharColorTrans()
{
	Init();
	com.assign((char*)command, 9, 1);
	string temp;
	stringstream ss;
	cout << "�������к� (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	int color[2];
	cout << "������ǰ��ɫ�ͱ���ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) : ";
	for (int i = 0; i < 2; i++)
	{
		cin >> color[i];
		data += HexToStr(ToHex(color[i]));
	}
	LengthAndCrc();
}

void LED::TimingDisplay()
{
	Init();
	com.assign((char*)command, 4, 1);
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "��������ʾʱ�� (0-255) : ";
	int time;
	cin >> time;
	data += HexToStr(ToHex(time));
	ss.clear();
	ss.str("");
	cout << "������������ɫ (1 - ��ɫ, 2 - ��ɫ, 3 - ��ɫ) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str() + "00";
	data = data + HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "��������ʾ����: ";
	cin >> temp;
	data = data + temp;
	LengthAndCrc();
}

void LED::SetAdChangeMode()
{
	Init();
	com.assign((char*)command, 6, 1);
	string temp;
	stringstream ss;
	cout << "�������к�: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
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
	data.push_back(mode[i]);
	LengthAndCrc();
}