#include "led.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CSerialPort mySerialPort;//���Ƚ�֮ǰ�������ʵ����
	BYTE* buffer = new BYTE[MAX_DATA_LEN];
	int size = 0;
	LED led;
	string temp;

	if (!mySerialPort.InitPort(3, CBR_9600, 'N', 8, 1, EV_RXCHAR))//�Ƿ�򿪴��ڣ�3�������������ӵ��Ե�com�ڣ��������豸�������鿴��Ȼ������������
	{
		std::cout << "initPort fail !" << std::endl;
	}
	else
	{
		std::cout << "initPort success !" << std::endl;
	}
	if (!mySerialPort.OpenListenThread())//�Ƿ�򿪼����̣߳������߳��������䷵��ֵ
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
		cout << mySerialPort.WriteData(buffer, size) << endl;//����������Ǹ����ڷ������ݵĺ�����temp����Ҫ���͵����顣
		cout << mySerialPort.GetBytesInCOM() << endl;//�������������ʾ����ֵ����
	}
	delete[]buffer;
	system("pause");
	return 0;
}