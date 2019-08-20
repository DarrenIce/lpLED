#include "led.h"
namespace led {

static constexpr unsigned char kCrcHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};
static constexpr unsigned char kCrcLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

Led Led::instance_;

Led* Led::GetInstance() {
  return &instance_;
}

Led::Led() {
  buffer_ = new BYTE[kMaxDataLen];
}

Led::~Led() {
  delete[]buffer_;
}
// 命令行操作函数
bool Led::CommandOperate() {
  int i = 0, t;
  char temp;
  BYTE line_num, color[8], time, mod;
  std::string context;
  int datetime[6];
  system("cls");
  std::cout << "请输入要执行的命令: " << std::endl
    << "0 - 设置时间	1 - 设置广告" << std::endl
    << "2 - 彩色显示	3 - 取消显示" << std::endl
    << "4 - 定时显示	5 - 时间显示" << std::endl
    << "6 - 广告换页	7 - 字符颜色" << std::endl
    << "8 - 行色变换	9 - 字色变换" << std::endl
    << "10 - 语音播报   11 - 显示换页" << std::endl
    << "12 - 退出" << std::endl;
  std::cin >> i;
  switch (i) {
    case 0:
      std::cout << "请输入日期 (年月日时分秒, 年+2000即为年份) : ";
      for (i = 0; i < 6; ++i) {
        std::cin >> datetime[i];
      }
      SetTime(datetime);
      return true;
    case 1:
      std::cout << "请输入行号: (3/4)";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
      std::cin >> temp;
      switch (temp) {
        case '1':
          color[0] = RED;
          break;
        case '2':
          color[0] = GREEN;
          break;
        case '3':
          color[0] = YELLOW;
          break;
      }
      std::cout << "1 - 输入广告内容, 2 - 清除广告 : ";
      std::cin >> i;
      context[0] = 0x00;
      if (i == 1) {
        std::cout << "请输入广告内容: ";
        std::cin >> context;
      }
      SetAd(line_num, color[0], context);
      return true;
    case 2:
      /*
      std::cout << "请输入行号: (3/4)";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入显示时间 (0-255) : ";
      std::cin >> t;
      time = t;
      std::cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
      std::cin >> temp;
      switch (temp) {
        case '1':
          color[0] = RED;
          break;
        case '2':
          color[0] = GREEN;
          break;
        case '3':
          color[0] = YELLOW;
          break;
      }
      */
      std::cout << "请输入显示内容: ";
      std::cin >> context;
      ColoredDisplay(3, 3, RED, context);
      //ColoredDisplay(line_num, time, color[0], context);
      return true;
    case 3:
      std::cout << "请输入要取消的行号: (3/4)";
      std::cin >> i;
      switch (i) {
        case 1:
          line_num = LINE_FIR;
          break;
        case 2:
          line_num = LINE_SEC;
          break;
        case 3:
          line_num = LINE_THI;
          break;
        case 4:
          line_num = LINE_FOU;
          break;
      }
      CancelDisplay(line_num);
      return true;
    case 4:
      std::cout << "请输入行号: (3/4)";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入显示时间 (0-255) : ";
      std::cin >> t;
      time = t;
      std::cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
      std::cin >> temp;
      switch (temp) {
        case '1':
          color[0] = RED;
          break;
        case '2':
          color[0] = GREEN;
          break;
        case '3':
          color[0] = YELLOW;
          break;
      }
      std::cout << "请输入显示内容: ";
      std::cin >> context;
      TimingDisplay(line_num, time, color[0], context);
      return true;
    case 5:
      std::cout << "请输入行号 (0/3/4, 0为不显示时间) : ";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入字体颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) :";
      std::cin >> temp;
      switch (temp) {
        case '1':
          color[0] = RED;
          break;
        case '2':
          color[0] = GREEN;
          break;
        case '3':
          color[0] = YELLOW;
          break;
      }
      TimeDisplay(line_num, color[0]);
      return true;
    case 6:
      std::cout << "请输入行号: (3/4)";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入换页模式" << std::endl
        << "0 - 从右往左滚动模式" << std::endl
        << "1 - 下翻页(移动)" << std::endl
        << "2 - 下翻页(覆盖)" << std::endl
        << "3 - 下翻页(清除)" << std::endl
        << "4 - 下翻页(空白)" << std::endl
        << "5 - 上翻页(移动)" << std::endl
        << "6 - 上翻页(覆盖)" << std::endl
        << "7 - 上翻页(清除)" << std::endl
        << "8 - 上翻页(空白)" << std::endl
        << "9 - 左画刷(覆盖)" << std::endl
        << "10 - 左画刷(清除)" << std::endl
        << "11 - 右画刷(覆盖)" << std::endl
        << "12 - 右画刷(清除)" << std::endl
        << "13 - 开门式(覆盖)" << std::endl
        << "14 - 开门式(清除)" << std::endl
        << "15 - 关门式(覆盖)" << std::endl
        << "16 - 关门式(清除)" << std::endl
        << "17 - 页切换模式" << std::endl
        << "18 - 从右进入的页切换模式" << std::endl
        << "19 - 定屏模式" << std::endl;
      std::cin >> i;
      switch (i) {
        case 0:
          mod = SCOLL_RIGHT_TO_LEFT;
          break;
        case 1:
          mod = PAGE_DOWN_MOVE;
          break;
        case 2:
          mod = PAGE_DOWN_COVER;
          break;
        case 3:
          mod = PAGE_DOWN_CLEAR;
          break;
        case 4:
          mod = PAGE_DOWN_BLANK;
          break;
        case 5:
          mod = PAGE_UP_MOVE;
          break;
        case 6:
          mod = PAGE_UP_COVER;
          break;
        case 7:
          mod = PAGE_UP_CLEAR;
          break;
        case 8:
          mod = PAGE_UP_BLANK;
          break;
        case 9:
          mod = LEFT_BRUSH_COVER;
          break;
        case 10:
          mod = LEFT_BRUSH_CLEAR;
          break;
        case 11:
          mod = RIGHT_BRUSH_COVER;
          break;
        case 12:
          mod = RIGHT_BRUSH_CLEAR;
          break;
        case 13:
          mod = OPEN_DOOR_COVER;
          break;
        case 14:
          mod = OPEN_DOOR_CLEAR;
          break;
        case 15:
          mod = CLOSE_DOOR_COVER;
          break;
        case 16:
          mod = CLOSE_DOOR_CLEAR;
          break;
        case 17:
          mod = PAGE_CHANGE;
          break;
        case 18:
          mod = RIGHT_PAGE_CHANGE;
          break;
        case 19:
          mod = STOP;
          break;
      }
      SetAdChangeMode(line_num, mod);
      return true;
    case 7:
      std::cout << "请输入行号 (3/4) : ";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入每个字节的颜色 (1 - 红色, 2 - 绿色, 3 - 黄色) : ";
      for (int i = 0; i < 8; ++i) {
        std::cin >> temp;
        switch (temp) {
          case '1':
            color[i] = RED;
            break;
          case '2':
            color[i] = GREEN;
            break;
          case '3':
            color[i] = YELLOW;
            break;
        }
      }
      SetCharColor(line_num, color);
      return true;
    case 8:
      std::cout << "请输入行号 (3/4) : ";
      std::cin >> temp;
      line_num = temp - '0';
      LineColorTrans(line_num);
      return true;
    case 9:
      std::cout << "请输入行号 (3/4) : ";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入前景色和背景色 (1 - 红色, 2 - 绿色, 3 - 黄色) : ";
      for (int i = 0; i < 2; ++i) {
        std::cin >> temp;
        switch (temp) {
          case '1':
            color[i] = RED;
            break;
          case '2':
            color[i] = GREEN;
            break;
          case '3':
            color[i] = YELLOW;
            break;
        }
      }
      CharColorTrans(line_num, color);
      return true;
    case 10:
      TTSHelper();
      return true;
    case 11:
      std::cout << "请输入行号: (3/4)";
      std::cin >> temp;
      line_num = temp - '0';
      std::cout << "请输入换页模式" << std::endl
        << "0 - 从右往左滚动模式" << std::endl
        << "1 - 下翻页(移动)" << std::endl
        << "2 - 下翻页(覆盖)" << std::endl
        << "3 - 下翻页(清除)" << std::endl
        << "4 - 下翻页(空白)" << std::endl
        << "5 - 上翻页(移动)" << std::endl
        << "6 - 上翻页(覆盖)" << std::endl
        << "7 - 上翻页(清除)" << std::endl
        << "8 - 上翻页(空白)" << std::endl
        << "9 - 左画刷(覆盖)" << std::endl
        << "10 - 左画刷(清除)" << std::endl
        << "11 - 右画刷(覆盖)" << std::endl
        << "12 - 右画刷(清除)" << std::endl
        << "13 - 开门式(覆盖)" << std::endl
        << "14 - 开门式(清除)" << std::endl
        << "15 - 关门式(覆盖)" << std::endl
        << "16 - 关门式(清除)" << std::endl
        << "17 - 页切换模式" << std::endl
        << "18 - 从右进入的页切换模式" << std::endl
        << "19 - 定屏模式" << std::endl;
      std::cin >> i;
      switch (i) {
        case 0:
          mod = SCOLL_RIGHT_TO_LEFT;
          break;
        case 1:
          mod = PAGE_DOWN_MOVE;
          break;
        case 2:
          mod = PAGE_DOWN_COVER;
          break;
        case 3:
          mod = PAGE_DOWN_CLEAR;
          break;
        case 4:
          mod = PAGE_DOWN_BLANK;
          break;
        case 5:
          mod = PAGE_UP_MOVE;
          break;
        case 6:
          mod = PAGE_UP_COVER;
          break;
        case 7:
          mod = PAGE_UP_CLEAR;
          break;
        case 8:
          mod = PAGE_UP_BLANK;
          break;
        case 9:
          mod = LEFT_BRUSH_COVER;
          break;
        case 10:
          mod = LEFT_BRUSH_CLEAR;
          break;
        case 11:
          mod = RIGHT_BRUSH_COVER;
          break;
        case 12:
          mod = RIGHT_BRUSH_CLEAR;
          break;
        case 13:
          mod = OPEN_DOOR_COVER;
          break;
        case 14:
          mod = OPEN_DOOR_CLEAR;
          break;
        case 15:
          mod = CLOSE_DOOR_COVER;
          break;
        case 16:
          mod = CLOSE_DOOR_CLEAR;
          break;
        case 17:
          mod = PAGE_CHANGE;
          break;
        case 18:
          mod = RIGHT_PAGE_CHANGE;
          break;
        case 19:
          mod = STOP;
          break;
      }
      SetDisplayChangeMode(line_num, mod);
      return true;
    default:
      return false;
  }
}
// 设置广告函数
void Led::SetAd(BYTE line_num, BYTE color, std::string context) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = color;
  data[size++] = 0x00;
  if (context[0] != 0x00) {
    memcpy(data + size, context.c_str(), context.size());
    size += context.size();
  }
  PackageCommand(COM_SET_AD, data, size, buffer_, &size_);
  delete[]data;
}
// 打包函数
void Led::PackageCommand(kCommand com, BYTE* data, int size, BYTE* buffer, int *length) {
  BYTE* cursor = buffer;
  BYTE len[2] = { size >> 8, size << 8 >> 8 };
  // 拼包头
  memcpy(cursor, kCtrlHeader, 2);
  // 拼保留字
  cursor += 2;
  memcpy(cursor, kCtrlReserved, 3);
  // 拼命令
  cursor += 3;
  *cursor = com;
  // 拼长度
  cursor += 1;
  memcpy(cursor, len, 2);
  // 拼数据
  cursor += 2;
  memcpy(cursor, data, size);
  // 拼校验和
  BYTE t[2] = { 0x00, 0x00 };
  cursor += size;
  memcpy(cursor, t, 2);
  Crc16(buffer + 2, size + 8, t);
  memcpy(cursor, t, 2);
  // 拼结束标志符
  cursor += 2;
  *cursor = kCtrlEnd;
  *length = size + 11;
}
// Crc16查表校验
void Led::Crc16(BYTE* buffer, int size, BYTE* crc) {
  unsigned char temp_high = 0xFF, temp_low = 0xFF;
  int index = 0;
  for (int i = 0; i < size; ++i) {
    index = (unsigned char)buffer[i] ^ temp_low;
    temp_low = temp_high ^ kCrcHi[index];
    temp_high = kCrcLo[index];
  }
  crc[0] = temp_high;
  crc[1] = temp_low;
}
// 彩色显示函数
void Led::ColoredDisplay(BYTE line_num, BYTE time, BYTE color, std::string context) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = time;
  data[size++] = color;
  data[size++] = 0x00;
  memcpy(data + size, context.c_str(), context.size());
  size += context.size();
  PackageCommand(COM_COLORED_DISPLAY, data, size, buffer_, &size_);
  delete[]data;
}
//取消显示函数
void Led::CancelDisplay(BYTE line_num) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  PackageCommand(COM_CANCEL_DISPLAY, data, size, buffer_, &size_);
  delete[]data;
}
// 设置时间显示模式函数
void Led::TimeDisplay(BYTE line_num, BYTE color) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = color;
  data[size++] = 0x00;
  PackageCommand(COM_TIME_DISPLAY, data, size, buffer_, &size_);
  delete[]data;
}
// 设置时间函数
void Led::SetTime(int* datetime) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  for (int i = 0; i < 6; ++i) {
    data[size++] = datetime[i];
  }
  PackageCommand(COM_SET_TIME, data, size, buffer_, &size_);
  delete[]data;
}
// 设置字符颜色函数
void Led::SetCharColor(BYTE line_num, BYTE *color) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  for (int i = 0; i < 8; ++i) {
    data[size++] = color[i];
  }
  PackageCommand(COM_CHAR_COLOR, data, size, buffer_, &size_);
  delete[]data;
}
// 设置行颜色变换函数
void Led::LineColorTrans(BYTE line_num) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  PackageCommand(COM_LINE_COLOR, data, size, buffer_, &size_);
  delete[]data;
}
// 设置字符颜色变换函数
void Led::CharColorTrans(BYTE line_num, BYTE *color) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  for (int i = 0; i < 2; ++i) {
    data[size++] = color[i];
  }
  PackageCommand(COM_COLOR_CHANGE, data, size, buffer_, &size_);
  delete[]data;
}
// 语音播报函数
void Led::TextToSpeech(std::string context)
{
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  memcpy(data, context.c_str(), context.size());
  size += context.size();
  PackageCommand(COM_TEXT_TO_SPEECH, data, size, buffer_, &size_);
  delete[]data;
}
// 语音播报辅助函数
void Led::TTSHelper()
{
  std::vector<std::string> text1 = { "欢迎光临","一路平安","请等待人工确认","余额不足",
    "此车已进场","此车已出场","此车无权限","此车已过期","此车黑名单","车位已满","请缴费",
    "有效期","音量","此卡","已过期","无效","有效","有效期","此车","请入场停车","黑名单",
    "记录","下载","成功","失败","已进场","已出场","无权限","删除","请等待","人工确认",
    "亲情车","临时车","约租车","储值车","免费车","未派车","谢谢","欢迎回家","请通行",
    "未授权","已挂失","禁止通行","扣款","金额","停车","小时",
    "0","1","2","3","4","5","6","7","8","9",
    "节日","快乐","新年","剩余","读卡","车卡不符","一路顺风",
    "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
    "单号","","二维码","非通行时段","","减速慢行","禁止通行","扫码","时间","双号","",
    "微信","无牌车","","","支付","","","本车位已停车","车未发行","车未入场","车未授权",
    "车已过期","车已入场","请按时入场","请充值交费","月租已过期","重复进入","重复外出" };
  /*
  system("cls");
  std::cout << "请输入需要播报的内容的序号, 仅支持以下内容" << std::endl
    << "---------------------------" << std::endl
    << "| " << std::setw(5) << std::left << "序号" <<" | "<< std::setw(15) << std::left << "语音内容" <<" |"<< std::endl;
  for (int i = 0; i < text1.size(); i++) {
    std::cout << "| " << std::setw(5) << std::left << i << " | " << std::setw(15) << std::left << text1[i] << " |" << std::endl;
  }
  */
  // std::cout << "仅支持以下汉字" << std::endl;
  // std::unordered_set<std::string> text2 = { "十","百","千","万","年","月","日","天","条","京","黑",
  //  "吉","辽","苏","鲁","皖","冀","豫","鄂","湘","赣","陕","晋","川","青","琼","粤","浙",
  //  "闽","甘","云","台","贵","渝","沪","津","新","桂","蒙","宁","军","学","警","点","圆",
  //  "元","您","好","分","空","海","北","沈","兰","济","南","广","成","甲","乙","丙","午",
  //  "未","申","庚","己","辛","壬","寅","戌","祝","藏","港","澳","领","使","请","宝" };
  // std::cout << "十, 百, 千, 万, 年, 月, 日, 天, 条, 京" << std::endl
  //  << "黑, 吉, 辽, 苏, 鲁, 皖, 冀, 豫, 鄂, 湘" << std::endl
  //  << "赣, 陕, 晋, 川, 青, 琼, 粤, 浙, 闽, 甘" << std::endl
  //  << "云, 台, 贵, 渝, 沪, 津, 新, 桂, 蒙, 宁" << std::endl
  //  << "军, 学, 警, 点, 圆, 元, 您, 好, 分, 空" << std::endl
  //  << "海, 北, 沈, 兰, 济, 南, 广, 成, 甲, 乙" << std::endl
  //  << "丙, 午, 未, 申, 庚, 己, 辛, 壬, 寅, 戌" << std::endl
  //  << "祝, 藏, 港, 澳, 领, 使, 请, 宝" << std::endl;
  std::string context;
  /*
  int flag = 1;
  //std::cout << "请选择输入类型" << std::endl
  //  << "1 - 提示音,2 - 车牌号" << std::endl;
  std::cin >> flag;
  if (flag == 1) {
    int a;
    std::cin >> a;
    while (a >= 1 && a <= 119) {
      context += a;
      std::cin >> a;
    }
  }
  else if (flag == 2) {
    std::cin >> context;
  }
  */
  std::unordered_map<std::string, int> m;
  for (int i = 0; i < text1.size(); i++) {
    m[text1[i]] = i + 1;
  }
  std::cin >> context;
  for (int i = context.size(); i >0; i--) {
    for (int j = 0; j < context.size() - i+1; j++) {
      auto it = m.find(context.substr(j, i));
      if (it != m.end()) {
        std::string s1 = context.substr(0, j);
        std::string s2 = i+j<context.size()?context.substr(i + j):"";
        context = s1 + (char)it->second + s2;
      }
    }
  }
  TextToSpeech(context);
}
// 带定时的彩色显示函数
void Led::TimingDisplay(BYTE line_num, BYTE time, BYTE color, std::string context) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = time;
  data[size++] = color;
  data[size++] = 0x00;
  memcpy(data + size, context.c_str(), context.size());
  size += context.size();
  PackageCommand(COM_TIMING_DISPLAY, data, size, buffer_, &size_);
  delete[]data;
}
// 设置广告换页模式
void Led::SetAdChangeMode(BYTE line_num, BYTE mode) {
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = mode;
  PackageCommand(COM_ADPAGE_CHANGE, data, size, buffer_, &size_);
  delete[]data;
}
// 设置临时信息换页模式
void Led::SetDisplayChangeMode(BYTE line_num, BYTE mode)
{
  int size = 0;
  BYTE* data = new BYTE[kMaxDataLen];
  data[size++] = line_num;
  data[size++] = mode;
  PackageCommand(COM_DISPLAY_CHANGE, data, size, buffer_, &size_);
  delete[]data;
}
// 发送函数
void Led::Send(BYTE* buffer, int* size) {
  memcpy(buffer, buffer_, size_);
  *size = size_;
}
bool Led::test()
{
  TTSHelper();
  return true;
}
}  // namespace led
