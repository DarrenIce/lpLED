#include "led.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CSerialPort mySerialPort;//首先将之前定义的类实例化
	int length = 16;//定义传输的长度
	LED led;

	//unsigned char *temp = new unsigned char[length];//动态创建一个数组
	string temp;
	led.setad();
	

	if (!mySerialPort.InitPort(3, CBR_9600, 'N', 8, 1, EV_RXCHAR))//是否打开串口，3就是你外设连接电脑的com口，可以在设备管理器查看，然后更改这个参数
	{
		std::cout << "initPort fail !" << std::endl;
	}
	else
	{
		std::cout << "initPort success !" << std::endl;
	}
	if (!mySerialPort.OpenListenThread())//是否打开监听线程，开启线程用来传输返回值
	{
		std::cout << "OpenListenThread fail !" << std::endl;
	}
	else
	{
		std::cout << "OpenListenThread success !" << std::endl;
	}
	/*
	temp[0] = 0xAA;
	temp[1] = 0x55;
	temp[2] = 0x03;
	temp[3] = 0x64;
	temp[4] = 0x00;
	temp[5] = 0x11;
	temp[6] = 0x00;
	temp[7] = 0x05;
	temp[8] = 0x04;
	temp[9] = 0x74;
	temp[10] = 0x65;
	temp[11] = 0x73;
	temp[12] = 0x74;
	temp[13] = 0xEA;
	temp[14] = 0xBE;
	temp[15] = 0xAF;
	*/
	//temp = "AA550364001100050474657374EABEAF";
	cout << mySerialPort.WriteData(led.AssAfter(), strlen((char*)led.AssAfter())) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
	cout << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
	//delete temp;
	
	system("pause");
	return 0;
}