/**
 * Abstract display drawing class.
 * Used to display
 *  - LevelMeter
 * on different output devices.
 *  - OLED 128x32 based on 1306 controller, connected via SPI
 */

#pragma once

#include <Arduino.h>
#include <elapsedMillis.h>

#include <mbConfig.h>
#include "mbParameterStorage.h"

#define MB_MAX_PAGES 10

#ifndef DISPLAY_SCALER_X
#define DISPLAY_SCALER_X 1
#endif
#ifndef DISPLAY_SCALER_Y
#define DISPLAY_SCALER_Y 1
#endif

template<class GFX>
class mbDisplay;

template<class mbDisplay>
class mbPage;

template<class GFX>
class mbDisplay
{
public:
    mbDisplay();

    typedef mbPage<mbDisplay<GFX> >  PageType;
    // initialization
    void begin(); // calls begin of GFX, the underlying display lib
    void addPage(PageType *page); // add your pages in the order you want, no more then MB_MAX_PAGES
    void restore(); // goes through all pages and calls triggers.. use after mbStorage::restore.

    // runtime, call in your main loop, with fps rate u want, e.g. 20 times/sec
    void update(); // to be called in main loop..

    // access
    PageType& getPage(uint8_t id);
    PageType& getCurrentPage();
    inline uint8_t getCurrentPageNum() { return _currentPage.getI(); }
    inline GFX& display() { return _display; }
    inline uint8_t getPageCount() { return _pagePtr; }

    // blank control
    inline void setBlankTime(uint32_t val) { _blankTime = val; }  // default 60000 = 1min
    inline void setBlankPage(int8_t val) { _blankPage = val; }    // -1 >>> no page change, or index of page to show
    inline bool blanked() { return _blanked; }
    void blank();
    void unblank();

    // action
    void setCurrentPage(int8_t val); // random acces

    // interaction, very encoder focused
    void changeCurrentPage(int8_t val, bool force = false); // +1 for next page, -1 for previous..
    void changeActiveParam(int8_t val); // +1 for next parameter, -1 for previous..
    void changeParamValue(int8_t val);  // adds val to the current parameter

private:
    PageType*           _pages[MB_MAX_PAGES];
    mbParameter<int8_t> _currentPage;
    uint8_t             _pagePtr = 0;
    GFX                 _display;

    elapsedMillis       _timerBlank;
    uint32_t            _blankTime;
    int8_t              _blankPage;
    bool                _blanked;
};

typedef mbDisplay<NativeDisplayType> DisplayType;

#include "mbDisplay.inl"