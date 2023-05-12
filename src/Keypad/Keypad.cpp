/*
 * last updated By HuemoneLab, May 2023

 * This software is provided "AS IS" only for educational purpose using arduino kit made by Huemone Lab.
 * Unauthorized for copying, modifying, distributing of this code.

 * 본 라이브러리는 (주)휴몬랩이 제작한 아두이노 키트의 실습을 위해 제작되었습니다.
 * 따라서 모든 저작권은 (주)휴몬랩에 있습니다.
 * 키트 실습과 같은 교육적 용도로만 사용 및 활용이 가능하며
 * 무단으로 복사/수정/재배포하거나 코드 전체 혹은 일부를 다른 용도로 사용할 시 법적인 조치를 취할 수 있습니다.
 */

#ifndef HUEMONELAB_KEYPAD_CPP
#define HUEMONELAB_KEYPAD_CPP

#pragma once

#include "./Keypad.h"

const byte defaultRowPins[DEFAULT_KEYPAD_ROW_SIZE] = {9, 8, 7, 6};
const byte defaultColPins[DEFAULT_KEYPAD_COL_SIZE] = {5, 4, 3, 2};

char defaultKeys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE]= {  
  {'1', '2', '3', 'A'},  
  {'4', '5', '6', 'B'},  
  {'7', '8', '9', 'C'},  
  {'*', '0', '#', 'D'}
}; 

Keypad::Keypad()
{
  // Default 설정
  
  rowPins = defaultRowPins;
  columnPins = defaultColPins;
  
  sizeKpd.rows = DEFAULT_KEYPAD_ROW_SIZE;
  sizeKpd.columns = DEFAULT_KEYPAD_COL_SIZE;

  setKeys(defaultKeys);
  
  setDebounceTime(10);
	setHoldTime(500);
	keypadEventListener = 0;

	startTime = 0;
	single_key = false;
};

void Keypad::setKeys(char keys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE])
{
  // DefualtKeys value 덮어쓰기
  for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE; i++) {
        for (int j = 0; j < DEFAULT_KEYPAD_COL_SIZE; j++) {
            defaultKeys[i][j] = keys[i][j];
        }
    }

  keymap = makeKeymap(defaultKeys);
};

void Keypad::setRows(byte r1, byte r2, byte r3, byte r4)
{
  byte customRows[4] = {r1, r2, r3, r4};
  for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE ; i++ ) {
    rowPins[i] = customRows[i];
  }
};

void Keypad::setCols(byte c1, byte c2, byte c3, byte c4)
{
  byte customCols[4] = { c1, c2, c3, c4 };
  for (int i = 0; i < DEFAULT_KEYPAD_COL_SIZE ; i++ ) {
    columnPins[i] = customCols[i];
  }
};


char Keypad::getKey()
{
  single_key = true;

  if (getKeys() && key[0].stateChanged && (key[0].kstate==PRESSED))
		return key[0].kchar;
	
	single_key = false;

	return NO_KEY;
};

// Populate the key list.
bool Keypad::getKeys() {
	bool keyActivity = false;

	// Limit how often the keypad is scanned. This makes the loop() run 10 times as fast.
	if ( (millis()-startTime)>debounceTime ) {
		scanKeys();
		keyActivity = updateList();
		startTime = millis();
	}

	return keyActivity;
}


// Private : Hardware scan
void Keypad::scanKeys() {
	// Re-intialize the row pins. Allows sharing these pins with other hardware.
	for (byte r=0; r<sizeKpd.rows; r++) {
		pin_mode(rowPins[r],INPUT_PULLUP);
	}

	// bitMap stores ALL the keys that are being pressed.
	for (byte c=0; c<sizeKpd.columns; c++) {
		pin_mode(columnPins[c],OUTPUT);
		pin_write(columnPins[c], LOW);	// Begin column pulse output.
		for (byte r=0; r<sizeKpd.rows; r++) {
			bitWrite(bitMap[r], c, !pin_read(rowPins[r]));  // keypress is active low so invert to high.
		}
		// Set pin to high impedance input. Effectively ends column pulse.
		pin_write(columnPins[c],HIGH);
		pin_mode(columnPins[c],INPUT);
	}
}


// Manage the list without rearranging the keys. Returns true if any keys on the list changed state.
bool Keypad::updateList() {

	bool anyActivity = false;

	// Delete any IDLE keys
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].kstate==IDLE) {
			key[i].kchar = NO_KEY;
			key[i].kcode = -1;
			key[i].stateChanged = false;
		}
	}

	// Add new keys to empty slots in the key list.
	for (byte r=0; r<sizeKpd.rows; r++) {
		for (byte c=0; c<sizeKpd.columns; c++) {
			boolean button = bitRead(bitMap[r],c);
			char keyChar = keymap[r * sizeKpd.columns + c];
			int keyCode = r * sizeKpd.columns + c;
			int idx = findInList (keyCode);
			// Key is already on the list so set its next state.
			if (idx > -1)	{
				nextKeyState(idx, button);
			}
			// Key is NOT on the list so add it.
			if ((idx == -1) && button) {
				for (byte i=0; i<LIST_MAX; i++) {
					if (key[i].kchar==NO_KEY) {		// Find an empty slot or don't add key to list.
						key[i].kchar = keyChar;
						key[i].kcode = keyCode;
						key[i].kstate = IDLE;		// Keys NOT on the list have an initial state of IDLE.
						nextKeyState (i, button);
						break;	// Don't fill all the empty slots with the same key.
					}
				}
			}
		}
	}

	// Report if the user changed the state of any key.
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].stateChanged) anyActivity = true;
	}

	return anyActivity;
}


// Private
// This function is a state machine but is also used for debouncing the keys.
void Keypad::nextKeyState(byte idx, boolean button) {
	key[idx].stateChanged = false;

	switch (key[idx].kstate) {
		case IDLE:
			if (button==CLOSED) {
				transitionTo (idx, PRESSED);
				holdTimer = millis(); }		// Get ready for next HOLD state.
			break;
		case PRESSED:
			if ((millis()-holdTimer)>holdTime)	// Waiting for a key HOLD...
				transitionTo (idx, HOLD);
			else if (button==OPEN)				// or for a key to be RELEASED.
				transitionTo (idx, RELEASED);
			break;
		case HOLD:
			if (button==OPEN)
				transitionTo (idx, RELEASED);
			break;
		case RELEASED:
			transitionTo (idx, IDLE);
			break;
	}
}


// Search by character for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int Keypad::findInList (char keyChar) {
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].kchar == keyChar) {
			return i;
		}
	}
	return -1;
}

// Search by code for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int Keypad::findInList (int keyCode) {
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].kcode == keyCode) {
			return i;
		}
	}
	return -1;
}

// New in 2.0
char Keypad::waitForKey() {
	char waitKey = NO_KEY;
	while( (waitKey = getKey()) == NO_KEY );	// Block everything while waiting for a keypress.
	return waitKey;
}

// Backwards compatibility function.
KeyState Keypad::getState() {
	return key[0].kstate;
}

// The end user can test for any changes in state before deciding
// if any variables, etc. needs to be updated in their code.
bool Keypad::keyStateChanged() {
	return key[0].stateChanged;
}

// The number of keys on the key list, key[LIST_MAX], equals the number
// of bytes in the key list divided by the number of bytes in a Key object.
byte Keypad::numKeys() {
	return sizeof(key)/sizeof(Key);
}


// Minimum debounceTime is 1 mS. Any lower *will* slow down the loop().
void Keypad::setDebounceTime(uint debounce) {
	debounce<1 ? debounceTime=1 : debounceTime=debounce;
};


void Keypad::setHoldTime(uint hold) {
    holdTime = hold;
}


void Keypad::addEventListener(void (*listener)(char)){
	keypadEventListener = listener;
}

void Keypad::transitionTo(byte idx, KeyState nextState) {
	key[idx].kstate = nextState;
	key[idx].stateChanged = true;

	// Sketch used the getKey() function.
	// Calls keypadEventListener only when the first key in slot 0 changes state.
	if (single_key)  {
	  	if ( (keypadEventListener!=NULL) && (idx==0) )  {
			keypadEventListener(key[0].kchar);
		}
	}
	// Sketch used the getKeys() function.
	// Calls keypadEventListener on any key that changes state.
	else {
	  	if (keypadEventListener!=NULL)  {
			keypadEventListener(key[idx].kchar);
		}
	}
}

#endif