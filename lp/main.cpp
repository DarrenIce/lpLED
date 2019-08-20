#include "led.h"
#include "SerialPort.h"

int _tmain(int argc, _TCHAR* argv[]) {
  serialport::CSerialPort mySerialPort;
  BYTE* buffer = new BYTE[led::kMaxDataLen];
  int size = 0;
  led::Led* led=led::Led::GetInstance();
  std::string temp;

  if (!mySerialPort.InitPort(3, CBR_9600, 'N', 8, 1, EV_RXCHAR)) {
    std::cout << "initPort fail !" << std::endl;
  }
  else {
    std::cout << "initPort success !" << std::endl;
  }
  if (!mySerialPort.OpenListenThread()) {
    std::cout << "OpenListenThread fail !" << std::endl;
  }
  else {
    std::cout << "OpenListenThread success !" << std::endl;
  }
  while (led->test()) {
    led->Send(buffer, &size);
    std::cout << mySerialPort.WriteData(buffer, size) << std::endl;
    std::cout << mySerialPort.GetBytesInCOM() << std::endl;
  }
  delete[]buffer;
  system("pause");
  return 0;
}
