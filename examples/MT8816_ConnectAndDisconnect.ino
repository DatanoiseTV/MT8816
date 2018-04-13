#include <MT8816.h>

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


void setup() {

}

void loop() {
  // Connect X0 and Y5
  matrix.setState(0, 5, CONNECTED);

  // Connect X5 and Y2
  matrix.setState(5, 2, CONNECTED);

  // Disconnect X0 and Y5 again 1s later
  delay(1000);
  matrix.setState(0, 5, DISCONNECTED);

  // Start over
  delay(1000);
}
