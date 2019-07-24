#include "led.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CSerialPort mySerialPort;//首先将之前定义的类实例化
	BYTE* buffer = new BYTE[MAX_DATA_LEN];
	int size = 0;
	LED led;
	string temp;

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
	while (led.ShowCommand())
	{
		led.Send(buffer,&size);
		cout << mySerialPort.WriteData(buffer, size) << endl;//这个函数就是给串口发送数据的函数，temp就是要发送的数组。
		cout << mySerialPort.GetBytesInCOM() << endl;//这个函数就是显示返回值函数
	}
	delete[]buffer;
	system("pause");
	return 0;
}