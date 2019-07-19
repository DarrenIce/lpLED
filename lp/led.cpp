#include "led.h"
using namespace std;

void LED::SetAd()
{
	Init();
	com.assign((char*)command,1,1);
	string temp;
	stringstream ss;
	cout << "�������к�: ";
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
	ss << setw(4) << setfill('0') << data.size();
	temp = ss.str();
	len = HexToStr(temp);
	Crc16();
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

void LED::ColorDisplay()
{
	Init();
	com.assign((char*)command, 2, 1);
	string temp;
	stringstream ss;
	cout << "�������к�: ";
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
	ss << setw(4) << setfill('0') << ToHex(data.size());
	temp = ss.str();
	len = HexToStr(temp);
	Crc16();
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
	cout << "������Ҫȡ�����к�: ";
	int i;
	cin >> i;
	unsigned char line[] = { 0x00,0x01,0x02,0x04,0x08 };
	while (i < 2 || i>5)
	{
		cout << "��Ч���к�, ����������: ";
		cin >> i;
	}
	data.push_back(line[i]);
	string temp;
	stringstream ss;
	ss << setw(4) << setfill('0') << data.size();
	temp = ss.str();
	len = HexToStr(temp);
	Crc16();
}

void LED::Init()
{
	com.clear();
	len.clear();
	data.clear();
	checksum.clear();
}