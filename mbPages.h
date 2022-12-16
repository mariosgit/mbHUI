#pragma once

#include <string>
#include "mbDisplay.h"
#include "mbParameterStorage.h"

#define PAGES_FFT_BUFFER_SIZE 32
#define MB_MAX_PARAMS 16

// some standard display coordinates...
#ifndef PAGES_WIDTH
    #define PAGES_WIDTH 38
#endif
#ifndef PAGES_HEIGHT
    #define PAGES_HEIGHT 9
#endif
#ifndef PAGES_HEIGHT_OFF
    #define PAGES_HEIGHT_OFF 0
#endif
#ifndef PAGES_HEIGHT_TEXT_OFFSET
    #define PAGES_HEIGHT_TEXT_OFFSET 0
#endif
#ifndef DISPLAY_FG_COLOR
    #define DISPLAY_FG_COLOR 1
#endif
#ifndef DISPLAY_BG_COLOR
    #define DISPLAY_BG_COLOR 0
#endif
#ifndef DISPLAY_DIM_FG_COLOR
    #define DISPLAY_DIM_FG_COLOR 1
#endif
#ifndef DISPLAY_DIM_BG_COLOR
    #define DISPLAY_DIM_BG_COLOR 0
#endif
#define PAGES_POS_X0 0
#define PAGES_POS_X1 PAGES_WIDTH
#define PAGES_POS_X2 PAGES_WIDTH*2
#define PAGES_POS_X3 PAGES_WIDTH*3
#define PAGES_POS_Y0 PAGES_HEIGHT_OFF/2
#define PAGES_POS_Y1 (PAGES_HEIGHT+PAGES_HEIGHT_OFF)*1
#define PAGES_POS_Y2 (PAGES_HEIGHT+PAGES_HEIGHT_OFF)*2
#define PAGES_POS_Y3 (PAGES_HEIGHT+PAGES_HEIGHT_OFF)*3
#define PAGES_POS_Y4 (PAGES_HEIGHT+PAGES_HEIGHT_OFF)*4
#define PAGES_POS_Y5 (PAGES_HEIGHT+PAGES_HEIGHT_OFF)*5

/**
 * class mbPage
 *
 */
template<class DisplayType>
class mbPage
{
public:
    mbPage(DisplayType& display, const char* name);
    virtual void changeActiveParam(int16_t val);
    virtual void encoderClicked() { changeActiveParam(1); } // defaults to "next param"
    virtual void encoderHeld(int16_t val) { _display.changeCurrentPage(1); }
    virtual void setActive(bool val);
    inline  bool getActive() { return _active; }
    inline static uint8_t* getFFTBuffer()   { return _fftBuffer;   }
    inline static int16_t* getScopeBuffer() { return _scopeBuffer; }

    inline const char* getPageName() { return _name.c_str(); }
    const char* getParamName(uint8_t id);
    mbParameterBase* getParam(uint8_t id);

    /// redraw the complete page
    virtual void redraw() = 0;
    void setRedrawFlag() { _redraw = true; }
    bool getRedrawFlag() { return _redraw; }
    void resetRedrawFlag() { _redraw = false; }
    /// only redraw updated content (parameters)
    virtual void update(bool forceDrawAll = false);

    virtual void restore(); // parameters have changed/reloaded
    virtual int8_t getParamCount() { return _paramCount; };
    // inputs
    virtual void encoderValue(int16_t val);

    NativeDisplayType& display() { return _display.display(); }

protected:
    std::string _name;
    int16_t _param = 0;
    int16_t _paramCount = 0;
    bool    _active = false;
    bool    _redraw = false;
    DisplayType &_display;

    static uint8_t _fftBuffer[PAGES_FFT_BUFFER_SIZE];
    static int16_t _scopeBuffer[128*52];

    mbParameterBase* _params[MB_MAX_PARAMS];
};

typedef mbPage<mbDisplay<NativeDisplayType> > PageType;

#include <mbPages.inl>
