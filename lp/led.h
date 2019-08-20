#ifndef F__CODING_CPP_LPLED_LP_LP_LED_H_
#define F__CODING_CPP_LPLED_LP_LP_LED_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>
namespace led {

typedef unsigned char BYTE;
constexpr unsigned char kCtrlHeader[2] = { 0xAA, 0x55 };            // ����ͷ
constexpr unsigned char kCtrlReserved[3] = { 0x01, 0x02, 0x03 };    // ������
constexpr unsigned char kCtrlEnd = 0xAF;                            // ������־��
constexpr unsigned int kMaxDataLen = 1040;                          // ������󳤶�

enum kCommand {                   // ��������
  COM_SET_TIME = 0x10,            // 0x10 - ����ʱ��
  COM_SET_AD = 0x25,              // 0x25 - ���ò�ɫ���
  COM_COLORED_DISPLAY = 0x26,     // 0x26 - ��ɫ��ʾ
  COM_CANCEL_DISPLAY = 0x21,      // 0x21 - ȡ����ʾ
  COM_TEXT_TO_SPEECH = 0x22,      // 0x22 - ��������
  COM_TIMING_DISPLAY = 0x27,      // 0x27 - ����ʱ�Ĳ�ɫ��ʾ
  COM_TIME_DISPLAY = 0xF6,        // 0xF6 - ����ʱ����ʾģʽ
  COM_ADPAGE_CHANGE = 0x51,       // 0x51 - ���ù�滻ҳģʽ
  COM_DISPLAY_CHANGE = 0x52,      // 0x52 - ������ʱ��Ϣ��ҳģʽ
  COM_CHAR_COLOR = 0x53,          // 0x53 - �����ַ���ɫ
  COM_LINE_COLOR = 0x54,          // 0x54 - ��������ɫ�任
  COM_COLOR_CHANGE = 0x55         // 0x55 - �����ַ���ɫ�任
};

enum kMode {                      // ��淭ҳģʽ
  SCOLL_RIGHT_TO_LEFT = 0x00,     // 0x00 - �����������ģʽ
  PAGE_DOWN_MOVE = 0x01,          // 0x01 - �·�ҳ(�ƶ�)
  PAGE_DOWN_COVER = 0x02,         // 0x02 - �·�ҳ(����)
  PAGE_DOWN_CLEAR = 0x03,         // 0x03 - �·�ҳ(���)
  PAGE_DOWN_BLANK = 0x04,         // 0x04 - �·�ҳ(�հ�)
  PAGE_UP_MOVE = 0x05,            // 0x05 - �Ϸ�ҳ(�ƶ�)
  PAGE_UP_COVER = 0x06,           // 0x06 - �Ϸ�ҳ(����)
  PAGE_UP_CLEAR = 0x07,           // 0x07 - �Ϸ�ҳ(���)
  PAGE_UP_BLANK = 0x08,           // 0x08 - �Ϸ�ҳ(�հ�)
  LEFT_BRUSH_COVER = 0x09,        // 0x09 - ��ˢ(����)
  LEFT_BRUSH_CLEAR = 0x0A,        // 0x0A - ��ˢ(���)
  RIGHT_BRUSH_COVER = 0x0B,       // 0x0B - �һ�ˢ(����)
  RIGHT_BRUSH_CLEAR = 0x0C,       // 0x0C - �һ�ˢ(���)
  OPEN_DOOR_COVER = 0x0D,         // 0x0D - ����ʽ(����)
  OPEN_DOOR_CLEAR = 0x0E,         // 0x0E - ����ʽ(���)
  CLOSE_DOOR_COVER = 0x0F,        // 0x0F - ����ʽ(����)
  CLOSE_DOOR_CLEAR = 0x10,        // 0x10 - ����ʽ(���)
  PAGE_CHANGE = 0x11,             // 0x11 - ҳ�л�ģʽ
  RIGHT_PAGE_CHANGE = 0x12,       // 0x12 - ���ҽ����ҳ�л�ģʽ
  STOP = 0x13                     // 0x13 - ����ģʽ
};

enum kDisplayLine {
  LINE_FIR = 0x01,    // ��һ����ʾ
  LINE_SEC = 0x02,    // �ڶ�����ʾ
  LINE_THI = 0x04,    // ��������ʾ
  LINE_FOU = 0x08     // ��������ʾ
};

enum kColor {
  RED = 0x01,     // ��ɫ
  GREEN = 0x02,   // ��ɫ
  YELLOW = 0x03   // ��ɫ
};

// LED��ʾ�豸��
// ����ʵ�����ĵ��еĲ��ֹ���
// ���ܺ�����Ϊ��װdata�ֶβ����
// �������SetTime()���Եõ�����ʱ��ı��ģ������洢��_buffer(�洢����)��_size(�洢����)��
class Led {
 public:
  // �����в�������
  // 
  // �������û��Ľ���
  // @return�� bool �û���������Ч�򷵻�Ture
  bool CommandOperate();
  // ����ʱ�亯��
  // 
  // @param�� int datetime �û������ʱ�䣬��ʽΪ�� �� �� ʱ �� �룬��Ϊ2λ������+2000Ϊ���õ����
  void SetTime(int* datetime);
  // ���ò�ɫ��溯��
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE color �����ɫ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ
  // @param�� std::string context ������ݣ�Ϊ����������
  void SetAd(BYTE line_num, BYTE color, std::string context);
  // ��ɫ��ʾ����
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE time ��ʾʱ���������������ݳ��ȴ����ַ�����Ϊ����
  // @param�� BYTE color �����ɫ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ
  // @param�� std::string context �������
  void ColoredDisplay(BYTE line_num, BYTE time, BYTE color, std::string context);
  // ȡ����ʾ����
  // 
  // @param�� BYTE line_num �кţ�bit0Ϊ1��ʾȡ����һ����ʾ���Դ�����
  void CancelDisplay(BYTE line_num);
  // ����ʱ�Ĳ�ɫ��ʾ����
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE time ��ʾʱ��
  // @param�� BYTE color �����ɫ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ
  // @param�� std::string context �������
  void TimingDisplay(BYTE line_num, BYTE time, BYTE color, std::string context);
  // ����ʱ����ʾģʽ����
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ0-4��0��ʾ����ʾʱ��
  // @param�� BYTE color �����ɫ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ
  void TimeDisplay(BYTE line_num, BYTE color);
  // ���ù�滻ҳģʽ
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE mode ��滻ҳģʽ
  void SetAdChangeMode(BYTE line_num, BYTE mode);
  // ������ʱ��Ϣ��ҳģʽ
  //
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE mode ��ʱ��Ϣ��ҳģʽ
  void SetDisplayChangeMode(BYTE line_num, BYTE mode);
  // �����ַ���ɫ����
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE* color �ַ���ɫ������Ϊ8λ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ
  // @note�� �������������ÿһ�е�ÿһ���ַ�����ɫ
  void SetCharColor(BYTE line_num, BYTE* color);
  // ��������ɫ�任����
  //
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @note�� ���������ú�ָ��������ɫÿ0.5�밴�պ졢�̡��Ƶ�˳��任
  void LineColorTrans(BYTE line_num);
  // �����ַ���ɫ�任����
  // 
  // @param�� BYTE line_num �кţ�ȡֵ��Χ1-4
  // @param�� BYTE* color �ַ���ɫ������Ϊ2λ����Чֵ1~3��1 = ��ɫ��2 = ��ɫ��3 = ��ɫ����һ���ֽ�Ϊǰ��ɫ���ڶ����ֽ�Ϊ����ɫ
  // @note�� ��������������ָ������ÿ��������ɫ�任��ÿ0.5��任һ��
  void CharColorTrans(BYTE line_num, BYTE* color);
  // ������������
  //
  // @param�� std::string context ������������
  void TextToSpeech(std::string context);
  // ����������������
  //
  // ��������������������
  void TTSHelper();
  // �������
  // 
  // @param�� kCommond com ��������
  // @param�� BYTE* data ���ĵ�data�ֶ�
  // @param�� int size data �ֶεĳ���
  // @param�� BYTE* buffer ������Ĵ洢�Ļ�����
  // @param�� int* length ������ĵĳ���
  void PackageCommand(kCommand com, BYTE* data, int size, BYTE* buffer, int* length);
  // Crc16У�麯��
  // 
  // @param�� BYTE* buffer �洢��У��ı���
  // @param�� int size ��У�鱨�ĵĳ���
  // @param�� BYTE* crc �洢����õ�У���
  // @note�� ���ò������У���
  void Crc16(BYTE* buffer, int size, BYTE* crc);
  // ���ͺ���
  // 
  // @param�� BYTE* buffer �洢���ձ��ĵĻ�����
  // @param�� int* size �洢���ձ��ĵĳ���
  void Send(BYTE* buffer, int* size);

 private:
  BYTE* buffer_;  //���ͻ�����
  int size_;      //�����������ݳ���

 public:
   static Led* GetInstance();
 private:
   Led();
   Led(const Led&);
   Led& operator =(const Led&);
   ~Led();
   static Led instance_;
};
}  // namespace led
#endif  // F__CODING_CPP_LPLED_LP_LP_LED_H_
