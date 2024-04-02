/*
 * last updated By HuemoneLab, April 2024
 * 
 * Dependency : Keypad / by Mark Stanley, Alexander Brevig
 */

#ifndef HUEMONELAB_NUMPAD_CPP
#define HUEMONELAB_NUMPAD_CPP

#include "HuemonelabKit.h"

const byte defaultRowPins[DEFAULT_KEYPAD_ROW_SIZE] = { 9, 8, 7, 6 };
const byte defaultColPins[DEFAULT_KEYPAD_COL_SIZE] = { 5, 4, 3, 2 };

char defaultKeys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Numpad::Numpad() {
    {
        for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE; i++) _defaultColPins[i] = defaultColPins[i];
        for (int i = 0; i < DEFAULT_KEYPAD_COL_SIZE; i++) _defaultRowPins[i] = defaultRowPins[i];
        for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE; i++) {
            for (int j = 0; j < DEFAULT_KEYPAD_COL_SIZE; j++) {
                _defaultKeys[i][j] = defaultKeys[i][j];
            }
        }
        _pad = new Keypad(makeKeymap(_defaultKeys), _defaultRowPins, _defaultColPins, DEFAULT_KEYPAD_ROW_SIZE, DEFAULT_KEYPAD_COL_SIZE);
    }
}

void Numpad::setKeys(char keys[DEFAULT_KEYPAD_ROW_SIZE][DEFAULT_KEYPAD_COL_SIZE]) {
    delete _pad;
    for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE; i++) {
        for (int j = 0; j < DEFAULT_KEYPAD_COL_SIZE; j++) {
            _defaultKeys[i][j] = keys[i][j];
        }
    }
    _pad = new Keypad(makeKeymap(_defaultKeys), _defaultRowPins, _defaultColPins, DEFAULT_KEYPAD_ROW_SIZE, DEFAULT_KEYPAD_COL_SIZE);
}

void Numpad::setRows(byte r1, byte r2, byte r3, byte r4) {
    delete _pad;
    byte customRows[4] = { r1, r2, r3, r4 };
    for (int i = 0; i < DEFAULT_KEYPAD_ROW_SIZE; i++) {
        _defaultRowPins[i] = customRows[i];
    }
    _pad = new Keypad(makeKeymap(_defaultKeys), _defaultRowPins, _defaultColPins, DEFAULT_KEYPAD_ROW_SIZE, DEFAULT_KEYPAD_COL_SIZE);
}

void Numpad::setCols(byte c1, byte c2, byte c3, byte c4) {
    delete _pad;
    byte customCols[4] = { c1, c2, c3, c4 };
    for (int i = 0; i < DEFAULT_KEYPAD_COL_SIZE; i++) {
        _defaultColPins[i] = customCols[i];
    }
    _pad = new Keypad(makeKeymap(_defaultKeys), _defaultRowPins, _defaultColPins, DEFAULT_KEYPAD_ROW_SIZE, DEFAULT_KEYPAD_COL_SIZE);
}

char Numpad::getKey() {
    return _pad->getKey();
}

bool Numpad::getKeys() {
    return _pad->getKey();
}

#endif