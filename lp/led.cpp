#include "led.h"
using namespace std;

void LED::SetAd()
{
	Init();
	com.assign((char*)command,1,1);
	string temp;
	stringstream ss;
	cout << "请输入行号: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data=HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str()+"00";
	data=data+HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "1 - 输入广告内容, 2 - 清除广告 : ";
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		cout << "请输入广告内容: ";
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
	cout << "请输入行号: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "请输入显示时间 (0-255) : ";
	int time;
	cin >> time;
	data += HexToStr(ToHex(time));
	ss.clear();
	ss.str("");
	cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str() + "00";
	data = data + HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "请输入显示内容: ";
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
	cout << "请输入要取消的行号: (3/4)";
	int i;
	cin >> i;
	unsigned char line[] = { 0x00,0x01,0x02,0x04,0x08 };
	while (i < 2 || i>5)
	{
		cout << "无效的行号, 请重新输入: ";
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
	cout << "请输入行号 (0/3/4, 0为不显示时间) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
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
	cout << "请输入日期 (年月日时分秒, 年+2000即为年份) : ";
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
	cout << "请输入要执行的命令: " << endl
		<< "0 - 设置时间	1 - 设置广告" << endl
		<< "2 - 彩色显示	3 - 取消显示" << endl
		<< "4 - 定时显示	5 - 时间显示" << endl
		<< "6 - 广告换页	7 - 字符颜色" << endl
		<< "8 - 行色变换	9 - 字色变换" << endl
		<< "10 - 退出" << endl;
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
	cout << "请输入行号 (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	int color[8];
	cout << "请输入每个字节的颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) : ";
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
	cout << "请输入行号 (3/4) : ";
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
	cout << "请输入行号 (3/4) : ";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	int color[2];
	cout << "请输入前景色和背景色 (1 - 红色, 2 - 绿色, 3 - 黄色) : ";
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
	cout << "请输入行号: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	ss.clear();
	ss.str("");
	cout << "请输入显示时间 (0-255) : ";
	int time;
	cin >> time;
	data += HexToStr(ToHex(time));
	ss.clear();
	ss.str("");
	cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	temp = ss.str() + "00";
	data = data + HexToStr(temp);
	ss.clear();
	ss.str("");
	cout << "请输入显示内容: ";
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
	cout << "请输入行号: (3/4)";
	cin >> temp;
	ss << setw(2) << setfill('0') << temp;
	data = HexToStr(ss.str());
	char mode[] = {
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13
	};
	cout << "请输入换页模式" << endl
		<< "0 - 从右往左滚动模式" << endl
		<< "1 - 下翻页(移动)" << endl
		<< "2 - 下翻页(覆盖)" << endl
		<< "3 - 下翻页(清除)" << endl
		<< "4 - 下翻页(空白)" << endl
		<< "5 - 上翻页(移动)" << endl
		<< "6 - 上翻页(覆盖)" << endl
		<< "7 - 上翻页(清除)" << endl
		<< "8 - 上翻页(空白)" << endl
		<< "9 - 左画刷(覆盖)" << endl
		<< "10 - 左画刷(清除)" << endl
		<< "11 - 右画刷(覆盖)" << endl
		<< "12 - 右画刷(清除)" << endl
		<< "13 - 开门式(覆盖)" << endl
		<< "14 - 开门式(清除)" << endl
		<< "15 - 关门式(覆盖)" << endl
		<< "16 - 关门式(清除)" << endl
		<< "17 - 页切换模式" << endl
		<< "18 - 从右进入的页切换模式" << endl
		<< "19 - 定屏模式" << endl;
	int i;
	cin >> i;
	data.push_back(mode[i]);
	LengthAndCrc();
}