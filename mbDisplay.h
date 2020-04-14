/**
 * Abstract display drawing class.
 * Used to display
 *  - LevelMeter
 * on different output devices.
 *  - OLED 128x32 based on 1306 controller, connected via SPI
 */

#pragma once

#include <Arduino.h>
#include <SPI.h>

#include <mbLog.h>
#include "mbParameterStorage.h"
/*
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
 */

#define MB_MAX_PAGES 10


// Display selection at the end !

template<class GFX>
class mbPage;

template<class GFX>
class mbDisplay
{
    typedef mbPage<GFX> PageType;
public:
    mbDisplay();
    void begin();
    void loop() {};
    void restore();

    void addPage(PageType *page);

    inline PageType& getPage() { return *(_the->_pages[_currentPage.get()]); }
    static void changeCurrentPage(int8_t val);
    static void changeActiveParam(int8_t val);
    static mbDisplay* the();
    static inline GFX& get() { return _the->_display; }
    inline bool blanked() { return _blanked; }

    void blank();
    void unblank();

    void update(); // to be called in main loop..

private:
    mbPage<GFX>*        _pages[MB_MAX_PAGES];
    mbParameter<int8_t> _currentPage;
    uint8_t             _pagePtr = 0;
    GFX                 _display;
    bool                _blanked;
    static mbDisplay   *_the;
};


// 2.42" OLED:
//typedef U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI U8G2DisplayType;
// #define OLED_ROTATION U8G2_R0
// 1.3" mono OLED:
// typedef U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI U8G2DisplayType;
// #define OLED_ROTATION U8G2_R2
//typedef mbDisplay<U8G2DisplayType> DisplayType;

// font...
//#define DISP_FONT1x u8g2_font_profont10_mf
//#define DISP_FONT2x u8g2_font_profont22_mf //15,17,22

#include "mbDisplay.inl"