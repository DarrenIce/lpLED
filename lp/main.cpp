#include "led.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CSerialPort mySerialPort;//���Ƚ�֮ǰ�������ʵ����
	int length = 16;//���崫��ĳ���
	LED led;

	//unsigned char *temp = new unsigned char[length];//��̬����һ������
	string temp;
	led.setad();
	

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
	cout << mySerialPort.WriteData(led.AssAfter(), strlen((char*)led.AssAfter())) << endl;//����������Ǹ����ڷ������ݵĺ�����temp����Ҫ���͵����顣
	cout << mySerialPort.GetBytesInCOM() << endl;//�������������ʾ����ֵ����
	//delete temp;
	
	system("pause");
	return 0;
}