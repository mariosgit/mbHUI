/*
 * Abstract display drawing class.
 * Used to display
 *  - LevelMeter
 * on different output devices.
 *  - OLED 128x32 based on 1306 controller, connected via SPI
 */

#pragma once

#include "mbParameterStorage.h"
#include <Arduino.h>
#include <ArduinoLog.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Pins to connect the Display
#define OLED_DC     8
#define OLED_CS     5
#define OLED_RESET  4
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

#define MB_MAX_PAGES 10


// Display selection at the end !

class mbPage;

template<class GFX>
class mbDisplay
{
public:
    mbDisplay();
    void begin();
    void loop() {};
    void restore();

    void addPage(mbPage *page);

    inline mbPage& getPage() { return *(_the->_pages[_currentPage.get()]); }
    static void changeCurrentPage(int8_t val);
    static mbDisplay* the();
    static inline GFX& get() { return _the->_display; }
    inline bool blanked() { return _blanked; }

    void blank();
    void unblank();

private:
    mbPage*    _pages[MB_MAX_PAGES];
    mbParameter<int8_t> _currentPage;
    uint8_t    _pagePtr = 0;
    GFX        _display;
    bool       _blanked;
    static mbDisplay *_the;
};


// 2.42" OLED:
typedef U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI U8G2DisplayType;
#define OLED_ROTATION U8G2_R0
// 1.3" mono OLED:
// typedef U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI U8G2DisplayType;
// #define OLED_ROTATION U8G2_R2
typedef mbDisplay<U8G2DisplayType> DisplayType;

// font...
#define DISP_FONT1x u8g2_font_profont10_mf
#define DISP_FONT2x u8g2_font_profont22_mf //15,17,22

#define DISP DisplayType::get()
