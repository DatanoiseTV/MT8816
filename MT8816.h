#include <Arduino.h>

#define CONNECTED 1
#define DISCONNECTED 1

class MT8816 {
public:
  MT8816(int pin_reset, int pin_strobe, int pin_data,
              int pin_ay0, int pin_ay1, int pin_ay2,
              int pin_ax0, int pin_ax1, int pin_ax2, int pin_ax3
             );

  void setState(uint8_t x, uint8_t y, bool state);
  bool getState(uint8_t x, uint8_t y);

private:
  bool states[16][8];
  int _pin_reset, _pin_strobe, _pin_data;

  int _pin_ay0, _pin_ay1, _pin_ay2;
  int _pin_ax0, _pin_ax1, _pin_ax2, _pin_ax3;
};
