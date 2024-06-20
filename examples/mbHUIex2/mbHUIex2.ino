/* platformio.ini
[env:teensylc]
platform = teensy
board = teensylc
framework = arduino

src_dir =
    src/mbHUI-ext
    src

build_flags = -D TEENSY_OPT_SMALLEST_CODE -D USB_SERIAL

lib_deps =
    ArduinoLog
    ClickEncoder
*/

#include "mbConfig.h"
#include "mbButtons.h"
#include <elapsedMillis.h>
#include <ClickEncoder.h>  // it's on github
#include "mbPageTest.h"

// Encoders
const byte pinROT1L = 15;
const byte pinROT1R = 16;
const byte pinROT1C = 11;
const byte pinROT2L = 10;
const byte pinROT2R = 17;
const byte pinROT2C = 12;

const byte pinSWRU = 22;
const byte pinSWRD = 23;
const byte pinSWLU = 0;
const byte pinSWLD = 1;

// useable space is 126 width, one coloum missing at the sides
DisplayType _display;  //  uint8_t *getBuffer(void);
mbPageTest _pageTest(_display);
mbButtons _buttons;
ClickEncoder encoder1(pinROT1R, pinROT1L, pinROT1C, 4, HIGH); // Bourns, STEC12E08(Alps plastik)
ClickEncoder encoder2(pinROT2R, pinROT2L, pinROT2C, 4, HIGH); // Bourns, STEC12E08(Alps plastik)

void encoderServiceFunc()
{
    encoder1.service();
    encoder2.service();
    _buttons.loop();
}

void setup()
{
    // button changes page
    _buttons.add(pinSWRU, [](int8_t) { _display.changeCurrentPage(1); }, 0);

    // button changes selected param
    _buttons.add(pinSWRU, [](int8_t) { _display.changeActiveParam(1); }, 0);

    _display.begin();
    _display.addPage(&_pageTest);
}

void loop()
{
    auto bu1 = encoder1.getButton();
    if(bu1 == ClickEncoder::Clicked) {
        _display.changeCurrentPage(1); // change page with encoder click or do whatever..
    }

    auto bu2 = encoder2.getButton();
    if(bu1 == ClickEncoder::Clicked) {
        _display.changeActiveParam(1); // change selected param with encoder click or do whatever..
    }

    auto val = encoder1.getValue();
    _display.changeActiveParam(val);

    _display.update();

    // all your drawing code goes into one of the pages::update() method.
}
