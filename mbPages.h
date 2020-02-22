#pragma once

#include "mbDisplay.h"
#include "mbParameterStorage.h"

#define BLACK 0
#define WHITE 1

#define PAGES_FFT_BUFFER_SIZE 32
#define MB_MAX_PARAMS 16

#define FONT_BASE_ALIGN 0

// some standard display coordinates...
#define PAGES_WIDTH_X1 38
#define PAGES_HEIGHT_X1 9
#define PAGES_POS_X0 0
#define PAGES_POS_X1 PAGES_WIDTH_X1
#define PAGES_POS_X2 PAGES_WIDTH_X1*2
#define PAGES_POS_X3 PAGES_WIDTH_X1*3
#define PAGES_POS_Y0 0
#define PAGES_POS_Y1 (PAGES_HEIGHT_X1-1)*1+FONT_BASE_ALIGN
#define PAGES_POS_Y2 (PAGES_HEIGHT_X1-1)*2+FONT_BASE_ALIGN
#define PAGES_POS_Y3 (PAGES_HEIGHT_X1-1)*3+FONT_BASE_ALIGN
#define PAGES_POS_Y4 (PAGES_HEIGHT_X1-1)*4+FONT_BASE_ALIGN

/**
 * class mbPage
 * 
 */
template<class DisplayType>
class mbPage
{
public:
    mbPage();
    virtual void changeActiveParam(int16_t val);
    virtual void encoderClicked() { changeActiveParam(1); } // defaults to "next param"
    virtual void setActive(bool val);
    inline static uint8_t* getFFTBuffer()   { return _fftBuffer;   }
    inline static int16_t* getScopeBuffer() { return _scopeBuffer; }

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

    DisplayType& display() { return _display.get(); }

protected:
    int16_t _param = 0;
    int16_t _paramCount = 0;
    bool    _active = false;
    bool    _redraw;
    mbDisplay<DisplayType> &_display;

    static uint8_t _fftBuffer[PAGES_FFT_BUFFER_SIZE];
    static int16_t _scopeBuffer[128*52];

    mbParameterBase* _params[MB_MAX_PARAMS];
};

#include <mbPages.inl>
