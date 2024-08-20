#ifndef HUEMONELAB_GCUBE_CPP
#define HUEMONELAB_GCUBE_CPP

//#include "Arduino.h"
#include "HuemonelabKit.h"
//#include "SoftwareSerial.h"

#define GCUBE_GET_BOARD_ID 0x10 // 보드의 ID 값 확인 요청
#define GCUBE_CUBEINO_BOARD_ID 0x70 // 제조사 및 모델마다 고유 아이디 부여함, Cubeino : 0x70
#define GCUBE_GET_CUBE_NUMBER 0x21 // 연결된 큐브 개수 요청
#define GCUBE_SET_ALL_CUBES_CONNECTED 0x2A // 모든 큐브 연결됨

//Get GCube sensors
#define GCUBE_GET_CUBE_GYRO_BASE 0xA0 // 큐브의 기울기값(자이로센서) 요청
#define GCUBE_GET_CUBE_PROXI_BASE 0xAA // 큐브의 근접센서 요청
#define GCUBE_GET_CUBE_BUTTON_BASE 0xAB // 큐브의 버튼 상태 요청
#define GCUBE_GET_CUBE_EXT_ANALOG_2BYTE 0xB0 // 큐브의 확장포트 2바이트형 센서 값
#define GCUBE_GET_CUBE_ARDUINO_ANALOG_BASE 0xD0 // 큐브-아두이노의 아날로그값 요청
#define GCUBE_SET_CUBE_ARDUINO_ANALOG_START 0xD8 // 특정 큐브-아두이노의 아날로그 신호 보고 명령 전송
#define GCUBE_SET_CUBE_ARDUINO_DIGITAL_CONTROL 0xD9 // 특정 큐브-아두이노의 디지털 포트 제어 명령 전송

#define GCUBE_GET_CUBE_EXT_COLOR_KEY 0xE0 // 큐브의 확장포트 칼라센서 칼라키 값
#define GCUBE_GET_CUBE_EXT_COLOR_VALUE 0xE8 // 큐브의 확장포트 칼라센서 RGB 값 

#define GCUBE_GET_CUBE_ECHO_BASE 0xFF // 단순 Echo 메시지 받는 기능

//GCube motor & servo & dot-matrix control
#define GCUBE_SET_A_MOTOR_SPEED 0x30
#define GCUBE_SET_MULTI_MOTOR_SPEED 0x31
#define GCUBE_SET_A_MOTOR_ANGLE 0x38
#define GCUBE_SET_MULTI_MOTOR_ANGLE 0x39
#define GCUBE_SET_A_SERVO_ANGLE 0x40
#define GCUBE_SET_MULTI_SERVO_ANGLE 0x41

//Control PingPong robot model
#define PINGPONG_ANTBOT 2 // Gear가 장착된 자동차형 핑퐁로봇 모델
#define PINGPONG_BATTLEBOT 2 // Gear가 장착된 자동차형 핑퐁로봇 모델
#define PINGPONG_AUTOCAR 1 // Gear가 장착된 자동차형 핑퐁로봇 모델
#define PINGPONG_DRAWINGBOT 0 // Gear가 장착되지 않은 자동차형 핑퐁로봇 모델

//DotMatrix
#define GCUBE_SET_DOTMATRIX_IMAGE_DATA 0x51
#define GCUBE_SET_DOTMATRIX_BLINK_RATE 0x5A
#define GCUBE_SET_DOTMATRIX_PIXEL_DATA 0x60
#define GCUBE_SET_DOTMATRIX_STRING_DATA 0x61

GCube::GCube(int tx, int rx, byte CubeNum)
{
	_tx = tx;
	_rx = rx;
	_CubeNum = CubeNum;
	_serial = new SoftwareSerial(_tx, _rx);
}

void GCube::begin()
{
	(*_serial).begin(115200);
	if (_CubeNum == 1) {
		DEBUG_PRINTLN("ONLY A SINGLE GCUBE IS REQUIRED");
		wait_for_first_cube_connected(*_serial);
	}
	else {
		DEBUG_PRINTLN("MULTIPLE GCUBE IS REQUIRED");
		wait_for_first_cube_connected(*_serial);
		wait_for_all_cube_connected(_CubeNum, *_serial);
	}
}

void GCube::get_cube_echo_value(byte mdata[])
{
	get_cube_echo_value(mdata, (*_serial));
	DEBUG_PRINTLN(mdata[0]);
	DEBUG_PRINTLN(mdata[1]);
	DEBUG_PRINTLN(mdata[2]);
}


int8_t GCube::get_cube_accX_value(byte c_number)
{
	int8_t mdata[3];
	get_cube_acc_value(mdata, c_number, (*_serial));
	return mdata[1];
}

int8_t GCube::get_cube_accY_value(byte c_number)
{
	int8_t mdata[3];
	get_cube_acc_value(mdata, c_number, (*_serial));
	return mdata[2];
}

byte GCube::get_cube_proxi_value(byte c_number)
{
	int8_t mdata[3];
	get_cube_proxi_value(mdata, c_number, (*_serial));
	return mdata[2];
}

byte GCube::get_cube_button_value(byte c_number)
{
	int8_t mdata[3];
	get_cube_button_value(mdata, c_number, (*_serial));
	return mdata[2];
}

void GCube::send_matrix_still_image(byte cube_index, byte m[]) {
	cube_index = cube_index - 1;
	send_gcube(GCUBE_SET_DOTMATRIX_IMAGE_DATA + cube_index, get_iv(GCUBE_SET_DOTMATRIX_IMAGE_DATA + cube_index), m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], (*_serial));
}

void GCube::set_matrix_blink_rate(byte cube_index, byte blinkrate) {
	send_gcube(GCUBE_SET_DOTMATRIX_BLINK_RATE, get_iv(GCUBE_SET_DOTMATRIX_BLINK_RATE), cube_index, blinkrate, 0, 0, 0, 0, 0, 0, (*_serial));
}

void GCube::start_matrix_roll_image(byte GCUBE_TOTAL, byte m[], int duration) {
	GCUBE_TOTAL = GCUBE_TOTAL - 1; // the number of Cube which has dotMatrix
	byte roll[GCUBE_TOTAL * 8];
	byte roll_on[2]; // two matrix sector which should be refreshed
	byte current_roll_index = 0;
	byte total_line = GCUBE_TOTAL * 8;
	int d_index = 0;
	bool roll_flag = true;

	while (roll_flag) {
		for (int i = 0; i < total_line; i++) roll[i] = 0;

		for (int s = current_roll_index; s < current_roll_index + 8; s++) {
			roll[s % total_line] = m[s - current_roll_index];
		}

		if (current_roll_index % 8 == 0) {
			roll_on[0] = (byte)(current_roll_index / 8);
			roll_on[1] = (byte)(current_roll_index / 8 - 1);
			if (roll_on[1] < 0) roll_on[1] = GCUBE_TOTAL - 1;
		}
		else {
			roll_on[0] = (byte)(current_roll_index / 8);
			roll_on[1] = (byte)(current_roll_index / 8 + 1);
			if (roll_on[1] >= GCUBE_TOTAL) roll_on[1] = 0;
		}

		current_roll_index++;
		current_roll_index = current_roll_index % total_line;

		for (int i = 0; i < GCUBE_TOTAL; i++) {
			if (roll_on[0] == i || roll_on[1] == i) { // Refresh the matrix display only for the matrix the image is passing on
				send_gcube(GCUBE_SET_DOTMATRIX_IMAGE_DATA + i, get_iv(GCUBE_SET_DOTMATRIX_IMAGE_DATA + i), roll[8 * i + 0], roll[8 * i + 1], roll[8 * i + 2], roll[8 * i + 3], roll[8 * i + 4], roll[8 * i + 5], roll[8 * i + 6], roll[8 * i + 7], (*_serial));
				d_index++;
			}
		}
		if (d_index >= duration * 20) roll_flag = false; // 20*50msec = 1sec
	}
}

void GCube::start_matrix_shift_image(byte cubeIndex, byte GCUBE_TOTAL, byte rollImage[], int8_t xp, int8_t yp) {
	// cubeIndex = 0 : apply all connected GCubes
	// cubeIndex > 0 : just apply only the GCube of cubeIndex

	byte roll[8] = {};

	for (int i = 0; i < 8; i++) roll[i] = 0; // When maximum number of GCubes (8) are connected.

	//infinite loop for stop_rolling_matrix_image
	byte temp = GCUBE_TOTAL - 1; // the number of dot matrix plugged GCubes

	xp = xp * 4 / 90; // -4 ~ 4
	yp = yp * 4 / 90; // -4 ~ 4

	if (abs(xp) > 4 || abs(yp) > 4) return;

	if (cubeIndex > 0) {
		for (int i = 0; i < 8; i++) roll[i] = 0;
		for (int y = yp; y < 8; y++) {
			if (y >= 0) {
				if (xp >= 0)
					roll[y] = rollImage[y - yp] >> xp;
				else
					roll[y] = rollImage[y - yp] << (-1 * xp);
			}
		}

		send_matrix_still_image(cubeIndex, roll);
	}
	else {
		for (int i = 0; i < 8; i++) roll[i] = 0;
		for (int y = yp; y < 8; y++) {
			if (y >= 0) {
				if (xp >= 0)
					roll[y] = rollImage[y - yp] >> xp;
				else
					roll[y] = rollImage[y - yp] << (-1 * xp);
			}
		}

		for (int c = 0; c < temp; c++) {
			send_matrix_still_image(c + 1, roll);
		}
	}
}

void GCube::set_matrix_pixel_data(byte cube_index, byte x, byte y, byte onoff) {
	send_gcube(GCUBE_SET_DOTMATRIX_PIXEL_DATA, get_iv(GCUBE_SET_DOTMATRIX_PIXEL_DATA), cube_index, x, y, onoff, 0, 0, 0, 0, *(_serial));
}

void GCube::set_matrix_string_data(byte cube_index, byte s0, byte s1, byte s2, byte s3, byte s4, byte s5, byte s6, byte s7) {
	if (cube_index > 0) cube_index = cube_index - 1;
	send_gcube(GCUBE_SET_DOTMATRIX_STRING_DATA + cube_index, get_iv(GCUBE_SET_DOTMATRIX_STRING_DATA + cube_index), s0, s1, s2, s3, s4, s5, s6, s7, *(_serial));
}


void GCube::send_a_cube_speed(byte cube_number, char cube_speed)
{
	send_gcube(GCUBE_SET_A_MOTOR_SPEED, get_iv(GCUBE_SET_A_MOTOR_SPEED), cube_number, cube_speed, 0, 0, 0, 0, 0, 0, *(_serial));
}

void GCube::send_multi_cube_speed(byte GCUBE_TOTAL, char s0 = 0, char s1 = 0, char s2 = 0, char s3 = 0, char s4 = 0, char s5 = 0, char s6 = 0, char s7 = 0)
{
	GCUBE_TOTAL = GCUBE_TOTAL - 2;
	send_gcube(GCUBE_SET_MULTI_MOTOR_SPEED + GCUBE_TOTAL, get_iv(GCUBE_SET_MULTI_MOTOR_SPEED + GCUBE_TOTAL), s7, s6, s5, s4, s3, s2, s1, s0, *(_serial));
}

void GCube::stop_all_cube_motor(byte GCUBE_TOTAL)
{
	send_multi_cube_speed(GCUBE_TOTAL, 0, 0, 0, 0, 0, 0, 0, 0);
}

void GCube::send_a_cube_angle(byte cube_number, int cube_angle)
{
	cube_angle = 100 * cube_angle / 18;
	send_gcube(GCUBE_SET_A_MOTOR_ANGLE, get_iv(GCUBE_SET_A_MOTOR_ANGLE), cube_number, (cube_angle >> 8) & 0xFF, cube_angle & 0xFF, 0, 0, 0, 0, 0, *(_serial));
}

void GCube::send_multi_cube_angle(byte cube_range, int s0, int s1, int s2, int s3)
{
	cube_range = cube_range - 2;
	s3 = 100 * s3 / 18;
	s2 = 100 * s2 / 18;
	s1 = 100 * s1 / 18;
	s0 = 100 * s0 / 18;
	send_gcube(GCUBE_SET_MULTI_MOTOR_ANGLE + cube_range, get_iv(GCUBE_SET_MULTI_MOTOR_ANGLE + cube_range), (s3 >> 8) & 0xFF, s3 & 0xFF, (s2 >> 8) & 0xFF, s2 & 0xFF, (s1 >> 8) & 0xFF, s1 & 0xFF, (s0 >> 8) & 0xFF, s0 & 0xFF, *(_serial));
}

void GCube::move_pingpong_robot(byte gear_flag, int distance)
{
	if (gear_flag > 0) { //Geared-wheel type : AutoCar, BattleBot, AntBot
		int length = distance * 44;
		length = length / 10;
		unsigned int d_time = abs(distance) * 120;
		if (gear_flag == 1) send_multi_cube_angle(2, -1 * length, length, 0, 0);
		else send_multi_cube_angle(3, 0, -1 * length, length, 0);
		delay(d_time);
	}
	else { //Not geared-wheel type : Drawing bot
		int length = distance * 176;
		length = length / 10;
		unsigned int d_time = abs(distance) * 480;
		send_multi_cube_angle(3, 0, -1 * length, length, 0);
		delay(d_time);
	}
}

void GCube::rotate_pingpong_robot(byte gear_flag, int angle) { // distance : degree unit
	if (gear_flag > 0) { //Geared-wheel type : AutoCar, BattleBot, AntBot
		int rotation = angle * 41;
		rotation = rotation / 100;
		unsigned int d_time = abs(angle) * 11;
		if (gear_flag == 1) send_multi_cube_angle(2, -1 * rotation, -1 * rotation, 0, 0);
		else send_multi_cube_angle(3, 0, -1 * rotation, -1 * rotation, 0);
		delay(d_time);
	}
	else { //Not geared-wheel type : Drawing bot
		int rotation = angle * 135;
		rotation = rotation / 100;
		unsigned int d_time = abs(angle) * 44;
		send_multi_cube_angle(3, 0, -1 * rotation, -1 * rotation, 0);
		delay(d_time);
	}
}

void GCube::pen_up() {
	send_a_cube_angle(0, 90);
	unsigned int d_time = 90 * 40;
	delay(d_time);
}

void GCube::pen_down() {
	send_a_cube_angle(0, -90);
	unsigned int d_time = 90 * 40;
	delay(d_time);
}

void GCube::lever_up() {
	send_a_cube_angle(0, 90);
	unsigned int d_time = 90 * 40;
	delay(d_time);
}

void GCube::lever_down() {
	send_a_cube_angle(0, -90);
	unsigned int d_time = 90 * 40;
	delay(d_time);
}

void GCube::gripper_open() {
	send_a_cube_angle(0, 180);
	unsigned int d_time = 180 * 40;
	delay(d_time);
}

void GCube::gripper_close() {
	send_a_cube_angle(0, -180);
	unsigned int d_time = 180 * 40;
	delay(d_time);
}


void GCube::send_gcube(byte x0, byte x1, byte x2, byte x3, byte x4, byte x5, byte x6, byte x7, byte x8, byte x9, SoftwareSerial& cubeSerial)
{
	cubeSerial.write(x0);
	cubeSerial.write(x1);
	cubeSerial.write(x2);
	cubeSerial.write(x3);
	cubeSerial.write(x4);
	cubeSerial.write(x5);
	cubeSerial.write(x6);
	cubeSerial.write(x7);
	cubeSerial.write(x8);
	cubeSerial.write(x9);
	delay(50);
}

void GCube::wait_for_first_cube_connected(SoftwareSerial& cubeSerial)
{
	int rcvData[3];
	int rcvIndex = 0;
	while (1) {
		if (cubeSerial.available()) {
			rcvData[rcvIndex] = cubeSerial.read();

			if (rcvIndex >= 2) {
				if (rcvData[rcvIndex - 2] == GCUBE_GET_BOARD_ID && rcvData[rcvIndex - 1] == 0x00 && rcvData[rcvIndex] == 0x00) {
					send_gcube(GCUBE_GET_BOARD_ID, get_iv(GCUBE_GET_BOARD_ID), 0, 0, 0, GCUBE_CUBEINO_BOARD_ID, 0, 0, 0, 0, cubeSerial);
					DEBUG_PRINTLN("THE FIRST GCUBE IS CONNECTED");
					break;
				}
			}
			if (rcvData[0] == GCUBE_GET_BOARD_ID) rcvIndex++;
		}
	}
}

void GCube::wait_for_all_cube_connected(byte GCUBE_TOTAL, SoftwareSerial& cubeSerial)
{
	int rcvData[3];
	int rcvIndex = 0;
	byte cube_number = 0;
	unsigned int t_count = 1;

	while (1) {
		//Send 1st request after 1 second
		if (t_count++ % 1000 == 0) send_gcube(GCUBE_GET_CUBE_NUMBER, get_iv(GCUBE_GET_CUBE_NUMBER), 0, 0, 0, 0, 0, 0, 0, 0, cubeSerial);
		delay(1);

		if (cubeSerial.available()) {
			rcvData[rcvIndex] = cubeSerial.read();
			DEBUG_PRINT("WAITING ANOTHER GCUBE... CMD : ");
			DEBUG_PRINT(rcvData[0]);
			DEBUG_PRINT(", NUMBER OF ALEADY CONNECTED : ");
			DEBUG_PRINTLN(rcvData[2]);
			if (rcvData[0] == GCUBE_GET_CUBE_NUMBER) rcvIndex++;
		}

		if (rcvIndex >= 3) {
			if (rcvData[0] == GCUBE_GET_CUBE_NUMBER && rcvData[1] == 0x00) {
				cube_number = rcvData[2]; // STAR큐브에 연결된 큐브 숫자 (STAR큐브포함) 저장
			}
			rcvIndex = 0;
			if (cube_number >= GCUBE_TOTAL) {
				t_count = 0;
				rcvIndex = 0;

				delay(1000);
				//모든 큐브 연결되었음을 GCube0에게 알려줌. GCube0는 연결된 모든 큐브들에게 getSensor 명령 전송
				send_gcube(GCUBE_SET_ALL_CUBES_CONNECTED, get_iv(GCUBE_SET_ALL_CUBES_CONNECTED), GCUBE_TOTAL, 0, 0, 0, 0, 0, 0, 0, cubeSerial);
				delay(1000);
				DEBUG_PRINTLN("ALL GCUBES ARE CONNECTED");
				break;
			}
		}
	}
}

byte GCube::get_iv(byte a)
{
	return((a / 16) + (a & 0x0F) * 16);
}


void GCube::get_cube_echo_value(uint8_t mdata[], SoftwareSerial& cubeSerial)
{
	send_gcube(GCUBE_GET_CUBE_ECHO_BASE, get_iv(GCUBE_GET_CUBE_ECHO_BASE), 0, 0, 0, 0, 0, 0, 0, 0, cubeSerial);

	for (int i = 0; i < 3; i++) {
		if (cubeSerial.available()) {
			mdata[i] = cubeSerial.read();
		}
		else mdata[i] = 0;
	}
}


void GCube::get_cube_acc_value(int8_t mdata[], byte c_number, SoftwareSerial& cubeSerial) {
	send_gcube(GCUBE_GET_CUBE_GYRO_BASE + c_number, get_iv(GCUBE_GET_CUBE_GYRO_BASE + c_number), 0, 0, 0, 0, 0, 0, 0, 0, cubeSerial);

	for (int i = 0; i < 3; i++) {
		if (cubeSerial.available()) {
			mdata[i] = cubeSerial.read();
		}
		else mdata[i] = 0;
	}
}

void GCube::get_cube_proxi_value(uint8_t mdata[], byte c_number, SoftwareSerial& cubeSerial) {
	send_gcube(GCUBE_GET_CUBE_PROXI_BASE, get_iv(GCUBE_GET_CUBE_PROXI_BASE), c_number, 0, 0, 0, 0, 0, 0, 0, cubeSerial);

	for (int i = 0; i < 3; i++) {
		if (cubeSerial.available()) {
			mdata[i] = cubeSerial.read();
		}
		else mdata[i] = 0;
	}
}

void GCube::get_cube_button_value(uint8_t mdata[], byte c_number, SoftwareSerial& cubeSerial) {
	send_gcube(GCUBE_GET_CUBE_BUTTON_BASE, get_iv(GCUBE_GET_CUBE_BUTTON_BASE), c_number, 0, 0, 0, 0, 0, 0, 0, cubeSerial);

	for (int i = 0; i < 3; i++) {
		if (cubeSerial.available()) {
			mdata[i] = cubeSerial.read();
		}
		else mdata[i] = 0;
	}
}



#endif
