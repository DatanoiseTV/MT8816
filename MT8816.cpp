#include <MT8816.h>

MT8816::MT8816(int pin_reset, int pin_strobe, int pin_data,
  int pin_ay0, int pin_ay1, int pin_ay2,
  int pin_ax0, int pin_ax1, int pin_ax2, int pin_ax3)
{
  _pin_reset = pin_reset;
  _pin_strobe = pin_strobe;
  _pin_data = pin_data;
  _pin_ay0 = pin_ay0;
  _pin_ay1 = pin_ay1,
  _pin_ay2 = pin_ay2,
  _pin_ax0 = pin_ax0;
  _pin_ax1 = pin_ax1;
  _pin_ax2 = pin_ax2;
  _pin_ax3 = pin_ax3;
  pinMode(_pin_reset, OUTPUT);
  pinMode(_pin_strobe, OUTPUT);
  pinMode(_pin_data, OUTPUT);
  pinMode(_pin_ay0, OUTPUT);
  pinMode(_pin_ay1, OUTPUT);
  pinMode(_pin_ay2, OUTPUT);
  pinMode(_pin_ax0, OUTPUT);
  pinMode(_pin_ax1, OUTPUT);
  pinMode(_pin_ax2, OUTPUT);
  pinMode(_pin_ax3, OUTPUT);
  digitalWrite(_pin_reset, HIGH);
}


void MT8816::setState(uint8_t x, uint8_t y, bool state)
{
    states[x][y] = state;
    if(x >= 6) x+= 2;
    if(bitRead(x, 0)) digitalWrite(_pin_ax0, HIGH);
    if(bitRead(x, 1)) digitalWrite(_pin_ax1, HIGH);
    if(bitRead(x, 2)) digitalWrite(_pin_ax2, HIGH);
    if(bitRead(x, 3)) digitalWrite(_pin_ax3, HIGH);
    if(bitRead(y, 0)) digitalWrite(_pin_ay0, HIGH);
    if(bitRead(y, 1)) digitalWrite(_pin_ay1, HIGH);
    if(bitRead(y, 2)) digitalWrite(_pin_ay2, HIGH);
    delayMicroseconds(10000);
    digitalWrite(_pin_reset, LOW);
    digitalWrite(_pin_strobe, HIGH);
    digitalWrite(_pin_data, state);
    digitalWrite(_pin_strobe, LOW);

    if(hasSetCallback)
      (*set_callback)() ;
}

bool MT8816::getState(uint8_t x, uint8_t y)
{
    return states[x][y];
}
