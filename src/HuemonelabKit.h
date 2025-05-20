/* 
 * last updated By HuemoneLab, May 2024
 */

#ifndef HUEMONELAB_KIT_H
#define HUEMONELAB_KIT_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DallasTemperature.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <MD_Parola.h>
#include <Wire.h>

#define DEBUG_PRINTER Serial
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }

// envs for Numpad
#define DEFAULT_KEYPAD_COL_SIZE 4
#define DEFAULT_KEYPAD_ROW_SIZE 4

// envs for LCD
#define LCD_COLS 16
#define LCD_ROWS 2

/* LED */
class Led
{
public:
  Led(uint8_t pin);          // pin 설정
  void on(int = 255); // Led 켜기
  void off();                // Led 끄기
  void blink(int time);      // Led 켜고 끄기 (time: 간격(ms))

private:
  uint8_t _pin;
};

/* RGB LED */
class RGBLed
{
public:
  RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin); // pin 설정
  void setColor(int r, int g, int b);                        // rgb 색상값 지정
  void touchSwitch(int value);

private:
  int _state;
  uint8_t _redPin;
  uint8_t _greenPin;
  uint8_t _bluePin;
};

/* 터치센서 */
class TouchSensor
{
public:
  TouchSensor(uint8_t pin);                        // pin 설정
  int read();                                      // 터치센서 값 읽기
  int count(int  = 30, int  = 50); // 터치 센서 값 카운트세기(`duration`: 카운트 세는 간격, `maxCount`: 최대 카운트 수 )

private:
  uint8_t _pin;
  int _count;
};

/* 음성감지센서 */
class SoundSensor
{
public:
  SoundSensor(uint8_t pin);      // pin 설정
  int read();                    // 소리감지센서 값 읽기
  int count(int  = 150); // 소리감지 카운트세기(`duration`: 카운트 세는 간격)
  void resetCount();             // 카운트 0으로 reset

private:
  uint8_t _pin;
  int _count;
  int _tuner;
  int _lowValue;
};

/* 초음파센서(거리감지) */
class SonarSensor
{
public:
  SonarSensor(uint8_t trig, uint8_t echo); // pin 설정
  float read();                            // 거리값 읽기(단위: cm)

private:
  uint8_t _trig;
  uint8_t _echo;
  float _getDistance();
};

/* 빛감지센서 */
class LightSensor
{
public:
  LightSensor(uint8_t pin);              // pin 설정
  int read(int  = 0, int = 1023); // 빛감지센서값 읽기(analog)
  int readDigital();                     // 빛감지센서값 읽기(digital)

private:
  uint8_t _pin;
};

/* 먼지센서 */
class DustSensor
{
public:
  DustSensor(uint8_t measurePin, uint8_t ledPin);
  int read();

private:
  uint8_t _measurePin;
  uint8_t _ledPin;

  // time constants to measure
  unsigned int _samplingTime = 280;
  unsigned int _deltaTime = 40;
  unsigned int _sleepTime = 9680;
};

/* 서보모터 */
class ServoMotor
{
public:
  ServoMotor();

  uint8_t attach(uint8_t pin); // pin 설정
  void write(int angle);       // 모터 각도 조정

  /* from Servo.h */
  void detach();
  void writeMicroseconds(int angle);
  int read();
  int readMicroseconds();
  bool attached();
private:
    Servo* _sv;
};

/* 조이스틱 모듈 */
class JoyStick
{
public:
  JoyStick(uint8_t vrX, uint8_t vrY); // x, y 축 pin 설정
  void attach(uint8_t button);        // 버튼 pin 설정
  int read(char dir);                 // vrx, vry 값 읽기
  int isPushed();                     // 버튼 값 읽기
  int direction(bool toggle = true);
private:
  uint8_t _vrX;
  uint8_t _vrY;
  uint8_t _button;
  uint8_t _prev_state;
};

/* Bluetooth */
class Bluetooth
{
public:
  Bluetooth(uint8_t tx, uint8_t rx); // pin 설정

  void setName();          // 블루투스 이름 설정 모드
  void begin(long speed);  // 블루투스 시리얼 (in `setup`)
  virtual int read();      // 블루투스에서 보내는 값 읽기
  String readString();     // 블루투스에서 보내는 문장(string) 읽기
  virtual int available(); // 블루투스에서 보낸 값이 있는지 감지


  void end();
  bool listen();
  bool isListening();
  bool stopListening();
  bool overflow();

  template <typename T>
  size_t print(T val) {
      return _serial->print(val);
  }

  int peek();
  virtual size_t write(uint8_t byte);
  virtual void flush();

private:
  SoftwareSerial* _serial;
  uint8_t _tx;
  uint8_t _rx;
};

/* Added - 1 July, 2019
 * Updated - 12 December, 2019 
 *  - Update read function
 * Microphone Amplifier */
class MicroAmp
{
public:
  MicroAmp(uint8_t pin);                   // pin 설정 (analog)
  float read(int  = 0, int = 1023); // read during sampling time

private:
  uint8_t _pin;
};

/*
 * Added - 12 December, 2019
 * Pressure Sensor
 */
class PressureSensor
{
public:
  PressureSensor(uint8_t pin);
  int read(int  = 0, int  = 1023);

private:
  uint8_t _pin;
};

class DHT 
{
public:
  DHT(uint8_t pin);
  float readT();
  float readH();

private:
  boolean read();
  uint32_t expectPulse(bool level);

  uint8_t data[5];
  uint8_t _pin;
  uint32_t _lastReadTime, _maxCycles;  
  bool _lastResult;
};

class InterruptLock {
public:
InterruptLock() {
  noInterrupts();
}
~InterruptLock() {
  interrupts();
}
};

/*
 * Added - 13 April, 2020
 * Tilt Sensor
 */
class TiltSensor
{
public:
  TiltSensor(uint8_t pin);
  int read(); // 기울기 센서 값 읽기

private:
  uint8_t _pin;
};

class Stepper
{
public:
  Stepper(uint8_t pin4, uint8_t pin2, uint8_t pin3, uint8_t pin1);
  void setTimer(int second);
  void setDir(int dir); // 1 = 시계, 0 = 반시계
  void move(long degree);

  // original in Stepper.h
  void setSpeed(long rpm);
  void step(int stepsToMove);

private:
  uint8_t _pin1;
  uint8_t _pin2;
  uint8_t _pin3;
  uint8_t _pin4;

  int _direction; // default is 1 (시계방향)
  unsigned long _delay;
  int _stepNumber;
  unsigned long _lastStepTime;

  void stepMotor(int step);
};

class Buzzer
{
public:
  Buzzer(uint8_t pin);
  void note(char key, unsigned long  = 1000);
  void play(int  = 1, int  = 180);
  void stop();
private:
  uint8_t _pin;
};

/**
 * Updated at 2023.5.11
*/
enum callibrateLevel 
{
  low = 5,
  high = 10  
};

class ShockSensor
{
public:
  ShockSensor(uint8_t pin);
  void callibrate(bool callibrated);
  void setCallibrateLevel(callibrateLevel level);
  int read(); // read value with digitalWrite (if shocked, HIGH value returned)
  
private: 
  bool _callibrated; // 0 - false, 1 - true
  int _count; // 0 - default;
  uint8_t _pin;
  callibrateLevel _level;

  int readRaw();
};

/**
 * Updated at 2023.5.11
*/
class IRSensor
{
public:
  IRSensor(uint8_t pin);
  int read();

private:
  uint8_t _pin;
};

/**
 * Updated at 23.5.16
*/
class PotSensor
{
public:
  PotSensor(uint8_t pin);
  int read(int from = 0, int to = 1023); 
  
private:
  uint8_t _pin;
};

/* 
 * Updataed at 24.2.22
 */

class FAN {
public:
	FAN(uint8_t pin);
	void on();
	void off();
private:
	uint8_t _pin;
};


/*
 * Updated at 24.2.23
 */

class Motor {
public:
    Motor(uint8_t LN1, uint8_t LN2);
    void on(int dir = 0, int ms = 3000);
    void off();
private:
    uint8_t _LN1;
    uint8_t _LN2;
};

class WaterPumpMotor : public Motor {
public:
    WaterPumpMotor(uint8_t LN1, uint8_t LN2) : Motor(LN1, LN2) {}
};

class DCMotor : public Motor {
public:
    DCMotor(uint8_t LN1, uint8_t LN2) : Motor(LN1, LN2) {}
};

class SoilMoistureSensor {
public:
    SoilMoistureSensor(uint8_t pin) {
        _pin = pin;
    }
    inline int read() { return analogRead(_pin); }
private:
    uint8_t _pin;
};

/**
 * Updated at 24.3.21
 */

class Servo360
{
public:
    Servo360();
    uint8_t attach(uint8_t pin);
    void write(int angle, int time = 0);
    void stop();
    void detach();
    void writeMicroseconds(int angluar_speed);
    int read();
    int readMicroseconds();
    bool attached();
private:
    int _angle;
    Servo* _sv;
};


/*
 * Updated at 24.4.1
 */
class Numpad {
public:
    Numpad();
    void setKeys(char keys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE]);
    void setRows(byte r1, byte r2, byte r3, byte r4);
    void setCols(byte c1, byte c2, byte c3, byte c4);
    char getKey();
    bool getKeys();

private:
    Keypad* _pad;
    char _defaultKeys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE];
    byte _defaultRowPins[DEFAULT_KEYPAD_ROW_SIZE];
    byte _defaultColPins[DEFAULT_KEYPAD_COL_SIZE];
};

class WireTempSensor
{
public:
    WireTempSensor(uint8_t pin);
    float read();

private:
    OneWire _oneWire;
    DallasTemperature _dallasTemp;
    uint8_t _pin;
};

class lcdAddress {
public:
    lcdAddress(void);
};

class Lcd : public Print {
public:
    Lcd(uint8_t lcd_Addr, uint8_t lcd_cols = LCD_COLS, uint8_t lcd_rows = LCD_ROWS)
        : _Addr(lcd_Addr), _cols(lcd_cols), _rows(lcd_rows), _backlightval(0) { }
    size_t write(uint8_t value);
    void clear();
    void send(uint8_t value);
    void write4bits(uint8_t value);
    void expanderWrite(uint8_t _data);
    void begin();
    void backlight();
    void setCursor(uint8_t row, uint8_t col);
    void scrollLeft(unsigned long ms = 300);
    void scrollRight(unsigned long ms = 300);
    void screens(int n, int val_1 = 0, int val_2 = 0);
private:
    uint8_t _Addr;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
};

enum textEffect
{
    left = 0,
    right = 1
};

class DotMatrix {
public:
    DotMatrix(uint8_t dataPin, uint8_t csPin, uint8_t clkPin, uint8_t maxDevices = 1)
        : _mx(MD_MAX72XX::GENERIC_HW, dataPin, clkPin, csPin, maxDevices)
    {
        _mx.begin();
        _mx.clear();
    }

    inline void clear() { _mx.clear(); }
    void print(char val);
    void printScroll(const char* pText, textEffect dir = left);
    void print(const char* pText);
    inline void print(int val) { print((char)(val + 48)); }
    void printImage(const byte images[8]);
    void printEmoji(int num);
    inline void setIntensity(uint8_t intensity) { _mx.control(MD_MAX72XX::INTENSITY, intensity); }
private:
    MD_MAX72XX _mx;
};

class GCube
{
public:
    // Bluetooth tx rx 설정하는 함수와 같이 프로그램의 맨 처음 루프 밖에서 호출 되어야 하는 함수. 
    GCube(int rx, int tx, byte CubeNum);
    // setup 루프 에서 호출 되어야 하는 함수
    void begin();

    //sensors
        //0번 큐브가 아닌 1번 큐브 이상부터 요청 할 수 있는 함수들
        // echo 값을 읽는 함수. 구현은 했지만 말 그대로 0값 echo 하는 기능 인 것 같습니다.
    void get_cube_echo_value(byte mdata[]);
    // 해당 큐브의 가속도 x값을 1바이트로 반환하는 함수
    int8_t get_cube_accX_value(byte c_number);
    // 해당 큐브의 가속도 y값을 1바이트로 반환하는 함수
    int8_t get_cube_accY_value(byte c_number);
    // 해당 큐브의 근접 센서 값을 1 바이트로 반환하는 함수
    byte get_cube_proxi_value(byte c_number);
    // 해당 큐브의 버튼 값을 1 바이트로 반환하는 함수
    byte get_cube_button_value(byte c_number);

    //DotMatrix
    //!0번 큐브에는 메트릭스를 사용할 수 없습니다.
    //Still image 전송하는 함수
    void send_matrix_still_image(byte cube_index, byte m[]);
    //설정한 Blink rate 에 맞게 Image 깜빡이는 효과 함수
    //!추후 기능 업데이트 될 것 같습니다. 현재 구현되어 있지 않음.
    void set_matrix_blink_rate(byte cube_index, byte blinkrate);
    //전광판과 같이 옆 ID의 도트매트릭스에 이미지를 연결시켜 이동하는 함수
    void start_matrix_roll_image(byte GCUBE_TOTAL, byte m[], int duration);
    //한개의 도트 매트릭스 내에서 이미지를 xp, yp 만큼 이동시키는 함수
    void start_matrix_shift_image(byte cubeIndex, byte GCUBE_TOTAL, byte rollImage[], int8_t xp, int8_t yp);
    //도트매트릭스 중 x, y 에 해당하는 pixel 값을 설정하는 함수 - 사용 빈도 하 예상 (Byte array 사용)
    void set_matrix_pixel_data(byte cube_index, byte x, byte y, byte onoff);
    //도트매트릭스의 값을 byte string 으로 설정하는 함수 - 사용 빈도 하 예상 (Byte array 사용)
    void set_matrix_string_data(byte cube_index, byte s0, byte s1, byte s2, byte s3, byte s4, byte s5, byte s6, byte s7);

    //actuators
        //2개 이상의 큐브가 있어야 작동하는 함수들
        // 해당 큐브의 모터 값을 설정하는 함수
    void send_a_cube_speed(byte cube_number, char cube_speed);
    // 모든 큐브의 모터 값을 설정하는 함수
    void send_multi_cube_speed(byte GCUBE_TOTAL, char s0, char s1, char s2, char s3, char s4, char s5, char s6, char s7);
    // 모든 큐브의 모터 값을 0으로 설정하는 함수
    void stop_all_cube_motor(byte GCUBE_TOTAL);
    //  해당 큐브의 각도를 설정하는 함수
    void send_a_cube_angle(byte cube_number, int cube_angle);
    //  모든 큐브의 각도를 설정하는 함수
    void send_multi_cube_angle(byte cube_range, int s0, int s1, int s2, int s3);
    
    
    //pingpong robots
    //핑퐁교과와 연관 있는 함수들
        // 로봇의 종류에 따라 (기어 유무) 거리를 움직이는 함수
    void move_pingpong_robot(byte gear_flag, int distance);
    // 로봇의 종류에 따라 (기어 유무) 각도를 움직이는 함수
    void rotate_pingpong_robot(byte gear_flag, int angle);
    // 로봇 팔 관련 함수들
    void pen_up();
    void pen_down();
    void lever_up();
    void lever_down();
    void gripper_open();
    void gripper_close();

private:
    void send_gcube(byte x0, byte x1, byte x2, byte x3, byte x4, byte x5, byte x6, byte x7, byte x8, byte x9, SoftwareSerial& cubeSerial);
    void wait_for_first_cube_connected(SoftwareSerial& cubeSerial);
    void wait_for_all_cube_connected(byte GCUBE_TOTAL, SoftwareSerial& cubeSerial);
    byte get_iv(byte a);
    void get_cube_echo_value(uint8_t mdata[], SoftwareSerial& cubeSerial);
    void get_cube_acc_value(int8_t mdata[], byte c_number, SoftwareSerial& cubeSerial);
    void get_cube_proxi_value(uint8_t mdata[], byte c_number, SoftwareSerial& cubeSerial);
    void get_cube_button_value(uint8_t mdata[], byte c_number, SoftwareSerial& cubeSerial);
    int _rx;
    int _tx;
    SoftwareSerial* _serial;
    byte _CubeNum;

};

#endif