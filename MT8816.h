#include <Arduino.h>

#define CONNECTED 1
#define DISCONNECTED 0

#ifdef ESP32
#define EEPROM_SIZE (8*16)*32
#include <EEPROM.h>
#endif // ESP32

class MT8816 {
public:
  MT8816(int pin_reset, int pin_strobe, int pin_data,
              int pin_ay0, int pin_ay1, int pin_ay2,
              int pin_ax0, int pin_ax1, int pin_ax2, int pin_ax3
             );

  void setState(uint8_t x, uint8_t y, bool state);
  bool getState(uint8_t x, uint8_t y);

  #ifdef ESP32
  int store(int slot)
  {
       if(slot < 0 || slot > 32)
        return 0;

       EEPROM.begin(EEPROM_SIZE);
       for(int x=0; x<16; x++)
       {
         for(int y=0; y<8; y++)
         {
           uint8_t val = 0;
           for(int i=0; i<8;i++)
           {
             val << 1;
             if(states[x][y] == 1)
                val |= 1;
           }
           EEPROM.write(slot*(8*16), val);
         }

       }

  }
  #endif // ESP32

  void setCallback(void (*fptr)(void))
  {
    set_callback = fptr;
    hasSetCallback = 1;
  }

private:

  #ifdef ESP32
  int start_addr = 0;
  #endif

  bool states[16][8];
  int _pin_reset, _pin_strobe, _pin_data;

  int _pin_ay0, _pin_ay1, _pin_ay2;
  int _pin_ax0, _pin_ax1, _pin_ax2, _pin_ax3;

  void (*set_callback)();
  bool hasSetCallback = 0;
};
