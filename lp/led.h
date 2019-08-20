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
constexpr unsigned char kCtrlHeader[2] = { 0xAA, 0x55 };            // 传输头
constexpr unsigned char kCtrlReserved[3] = { 0x01, 0x02, 0x03 };    // 保留字
constexpr unsigned char kCtrlEnd = 0xAF;                            // 结束标志符
constexpr unsigned int kMaxDataLen = 1040;                          // 报文最大长度

enum kCommand {                   // 报文命令
  COM_SET_TIME = 0x10,            // 0x10 - 设置时间
  COM_SET_AD = 0x25,              // 0x25 - 设置彩色广告
  COM_COLORED_DISPLAY = 0x26,     // 0x26 - 彩色显示
  COM_CANCEL_DISPLAY = 0x21,      // 0x21 - 取消显示
  COM_TEXT_TO_SPEECH = 0x22,      // 0x22 - 语音播报
  COM_TIMING_DISPLAY = 0x27,      // 0x27 - 带定时的彩色显示
  COM_TIME_DISPLAY = 0xF6,        // 0xF6 - 设置时间显示模式
  COM_ADPAGE_CHANGE = 0x51,       // 0x51 - 设置广告换页模式
  COM_DISPLAY_CHANGE = 0x52,      // 0x52 - 设置临时信息换页模式
  COM_CHAR_COLOR = 0x53,          // 0x53 - 设置字符颜色
  COM_LINE_COLOR = 0x54,          // 0x54 - 设置行颜色变换
  COM_COLOR_CHANGE = 0x55         // 0x55 - 设置字符颜色变换
};

enum kMode {                      // 广告翻页模式
  SCOLL_RIGHT_TO_LEFT = 0x00,     // 0x00 - 从右往左滚动模式
  PAGE_DOWN_MOVE = 0x01,          // 0x01 - 下翻页(移动)
  PAGE_DOWN_COVER = 0x02,         // 0x02 - 下翻页(覆盖)
  PAGE_DOWN_CLEAR = 0x03,         // 0x03 - 下翻页(清除)
  PAGE_DOWN_BLANK = 0x04,         // 0x04 - 下翻页(空白)
  PAGE_UP_MOVE = 0x05,            // 0x05 - 上翻页(移动)
  PAGE_UP_COVER = 0x06,           // 0x06 - 上翻页(覆盖)
  PAGE_UP_CLEAR = 0x07,           // 0x07 - 上翻页(清除)
  PAGE_UP_BLANK = 0x08,           // 0x08 - 上翻页(空白)
  LEFT_BRUSH_COVER = 0x09,        // 0x09 - 左画刷(覆盖)
  LEFT_BRUSH_CLEAR = 0x0A,        // 0x0A - 左画刷(清除)
  RIGHT_BRUSH_COVER = 0x0B,       // 0x0B - 右画刷(覆盖)
  RIGHT_BRUSH_CLEAR = 0x0C,       // 0x0C - 右画刷(清除)
  OPEN_DOOR_COVER = 0x0D,         // 0x0D - 开门式(覆盖)
  OPEN_DOOR_CLEAR = 0x0E,         // 0x0E - 开门式(清除)
  CLOSE_DOOR_COVER = 0x0F,        // 0x0F - 关门式(覆盖)
  CLOSE_DOOR_CLEAR = 0x10,        // 0x10 - 关门式(清除)
  PAGE_CHANGE = 0x11,             // 0x11 - 页切换模式
  RIGHT_PAGE_CHANGE = 0x12,       // 0x12 - 从右进入的页切换模式
  STOP = 0x13                     // 0x13 - 定屏模式
};

enum kDisplayLine {
  LINE_FIR = 0x01,    // 第一行显示
  LINE_SEC = 0x02,    // 第二行显示
  LINE_THI = 0x04,    // 第三行显示
  LINE_FOU = 0x08     // 第四行显示
};

enum kColor {
  RED = 0x01,     // 红色
  GREEN = 0x02,   // 绿色
  YELLOW = 0x03   // 黄色
};

// LED显示设备类
// 本类实现了文档中的部分功能
// 功能函数均为组装data字段并打包
// 例如调用SetTime()可以得到设置时间的报文，它被存储在_buffer(存储内容)和_size(存储长度)中
class Led {
 public:
  // 命令行操作函数
  // 
  // 负责与用户的交互
  // @return： bool 用户的输入有效则返回Ture
  bool CommandOperate();
  // 设置时间函数
  // 
  // @param： int datetime 用户输入的时间，格式为年 月 日 时 分 秒，均为2位数，年+2000为设置的年份
  void SetTime(int* datetime);
  // 设置彩色广告函数
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE color 广告颜色，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色
  // @param： std::string context 广告内容，为空则清除广告
  void SetAd(BYTE line_num, BYTE color, std::string context);
  // 彩色显示函数
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE time 显示时长或次数，如果内容长度大于字符，则为次数
  // @param： BYTE color 广告颜色，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色
  // @param： std::string context 广告内容
  void ColoredDisplay(BYTE line_num, BYTE time, BYTE color, std::string context);
  // 取消显示函数
  // 
  // @param： BYTE line_num 行号，bit0为1表示取消第一行显示，以此类推
  void CancelDisplay(BYTE line_num);
  // 带定时的彩色显示函数
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE time 显示时长
  // @param： BYTE color 广告颜色，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色
  // @param： std::string context 广告内容
  void TimingDisplay(BYTE line_num, BYTE time, BYTE color, std::string context);
  // 设置时间显示模式函数
  // 
  // @param： BYTE line_num 行号，取值范围0-4，0表示不显示时间
  // @param： BYTE color 广告颜色，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色
  void TimeDisplay(BYTE line_num, BYTE color);
  // 设置广告换页模式
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE mode 广告换页模式
  void SetAdChangeMode(BYTE line_num, BYTE mode);
  // 设置临时信息换页模式
  //
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE mode 临时信息换页模式
  void SetDisplayChangeMode(BYTE line_num, BYTE mode);
  // 设置字符颜色函数
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE* color 字符颜色，长度为8位，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色
  // @note： 该命令可以设置每一行的每一个字符的颜色
  void SetCharColor(BYTE line_num, BYTE* color);
  // 设置行颜色变换函数
  //
  // @param： BYTE line_num 行号，取值范围1-4
  // @note： 该命令设置后，指定的行颜色每0.5秒按照红、绿、黄的顺序变换
  void LineColorTrans(BYTE line_num);
  // 设置字符颜色变换函数
  // 
  // @param： BYTE line_num 行号，取值范围1-4
  // @param： BYTE* color 字符颜色，长度为2位，有效值1~3，1 = 红色，2 = 绿色，3 = 黄色。第一个字节为前景色，第二个字节为背景色
  // @note： 该命令用于设置指定行中每个汉字颜色变换，每0.5秒变换一次
  void CharColorTrans(BYTE line_num, BYTE* color);
  // 语音播报函数
  //
  // @param： std::string context 语音播报内容
  void TextToSpeech(std::string context);
  // 语音播报辅助函数
  //
  // 负责生成语音播报内容
  void TTSHelper();
  // 打包函数
  // 
  // @param： kCommond com 报文命令
  // @param： BYTE* data 报文的data字段
  // @param： int size data 字段的长度
  // @param： BYTE* buffer 打包报文存储的缓冲区
  // @param： int* length 打包后报文的长度
  void PackageCommand(kCommand com, BYTE* data, int size, BYTE* buffer, int* length);
  // Crc16校验函数
  // 
  // @param： BYTE* buffer 存储待校验的报文
  // @param： int size 待校验报文的长度
  // @param： BYTE* crc 存储计算好的校验和
  // @note： 采用查表法计算校验和
  void Crc16(BYTE* buffer, int size, BYTE* crc);
  // 发送函数
  // 
  // @param： BYTE* buffer 存储接收报文的缓冲区
  // @param： int* size 存储接收报文的长度
  void Send(BYTE* buffer, int* size);

 private:
  BYTE* buffer_;  //发送缓冲区
  int size_;      //缓冲区内数据长度

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
