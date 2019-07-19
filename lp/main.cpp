#include "led.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CSerialPort mySerialPort;//���Ƚ�֮ǰ�������ʵ����
	int length = 16;//���崫��ĳ���
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
	//while (1)
	//{
		led.ColorDisplay();
		cout << mySerialPort.WriteData((unsigned char*)led.Assemble().c_str(), led.Assemble().size()) << endl;//����������Ǹ����ڷ������ݵĺ�����temp����Ҫ���͵����顣
		cout << mySerialPort.GetBytesInCOM() << endl;//�������������ʾ����ֵ����
		led.CancelDisplay();
		cout << mySerialPort.WriteData((unsigned char*)led.Assemble().c_str(), led.Assemble().size()) << endl;//����������Ǹ����ڷ������ݵĺ�����temp����Ҫ���͵����顣
		cout << mySerialPort.GetBytesInCOM() << endl;//�������������ʾ����ֵ����
	//}
	
	
	system("pause");
	return 0;
}