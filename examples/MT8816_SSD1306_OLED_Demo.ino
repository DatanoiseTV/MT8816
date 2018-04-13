#include <MT8816.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_RESET 0
#define PIN_STROBE 4
#define PIN_DATA 16
#define PIN_AY0 18
#define PIN_AY1 5
#define PIN_AY2 17
#define PIN_AX0 23
#define PIN_AX1 22
#define PIN_AX2 21
#define PIN_AX3 19

MT8816 matrix(PIN_RESET, PIN_STROBE, PIN_DATA,
              PIN_AY0, PIN_AY1, PIN_AY2,
              PIN_AX0, PIN_AX1, PIN_AX2, PIN_AX3);

#define OLED_DC     12
#define OLED_CS     14
#define OLED_RESET  27
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


void setup() {
    display.begin(SSD1306_SWITCHCAPVCC);
    display.display();
    display.clearDisplay();
}

#define CELL_SIZE 6
#define ROUND_CORNER_RADIUS 3
void drawMatrix()
{
  for(int x=0; x<16; x++)
  {
    for(int y=0; y<8; y++)
    {
      display.drawRoundRect(x*(CELL_SIZE+1) , y*(CELL_SIZE+1), CELL_SIZE, CELL_SIZE, ROUND_CORNER_RADIUS, WHITE);
      if(matrix.getState(x, y) == 1)
      {
        display.fillRoundRect(x*(CELL_SIZE+1) , y*(CELL_SIZE+1), CELL_SIZE, CELL_SIZE, ROUND_CORNER_RADIUS, WHITE);
      }
    }
  }
  display.display();
}

void loop() {
  // Connect X0 and Y5
  matrix.setState(0, 5, CONNECTED);

  // Connect X5 and Y2
  matrix.setState(5, 2, CONNECTED);

  drawMatrix(); // Show status on matrix

  // Disconnect X0 and Y5 again 1s later
  delay(1000);
  matrix.setState(0, 5, DISCONNECTED);

  drawMatrix(); // Show status on matrix

  // Start over
  delay(1000);
}
