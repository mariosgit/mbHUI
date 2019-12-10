#pragma once

#include "mbDisplay.h"
#include "mbParameterStorage.h"

#define BLACK 0
#define WHITE 1

#define PAGES_FFT_BUFFER_SIZE 32
#define MB_MAX_PARAMS 16

// some standard display coordinates...
#define PAGES_POS_X0 0
#define PAGES_POS_X1 42
#define PAGES_POS_X2 84
#define PAGES_POS_Y0 0
#define PAGES_POS_Y1 12
#define PAGES_POS_Y2 24
#define PAGES_POS_Y3 36
#define PAGES_POS_Y4 48
#define PAGES_WIDTH_X1 40
#define PAGES_HEIGHT_X1 12


class mbPage
{
public:
    mbPage();
    virtual void changeActiveParam(int16_t val);
    virtual void encoderClicked() { changeActiveParam(1); } // defaults to "next param"
    virtual void setActive(bool val);
    inline static uint8_t* getFFTBuffer()   { return _fftBuffer;   }
    inline static int16_t* getScopeBuffer() { return _scopeBuffer; }

    virtual void redraw() = 0;       // redraw the complete page
    virtual void update(bool forceDrawAll = false); // only redraw updated content (parameters)

    virtual void restore(); // parameters have changed/reloaded
    virtual int8_t getParamCount() { return _paramCount; };
    // inputs
    virtual void encoderValue(int16_t val);

protected:
    int16_t _param = 0;
    int16_t _paramCount = 0;
    bool    _active = false;
    DisplayType &_display;

    static uint8_t _fftBuffer[PAGES_FFT_BUFFER_SIZE];
    static int16_t _scopeBuffer[128*52];

    mbParameterBase* _params[MB_MAX_PARAMS];
};

class mbPageCover : public mbPage
{
    const char* _version;
public:
    mbPageCover(const char* version) :
        _version(version)
    {
    }
    void redraw() override; // redraw
};

class mbPageCV : public mbPage
{
public:
    mbPageCV() :
        _ch("ch", 0,1),
        _func("func", 0,3),
        _wasCooles("bla", 0,1)
    {
        _params[_paramCount++] = &_ch;
        _params[_paramCount++] = &_func;
        _params[_paramCount++] = &_wasCooles;
    }
    void redraw() override;
private:
    mbParameterRB<PAGES_POS_X0, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1> _ch;
    mbParameterRB<PAGES_POS_X1, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1> _func;
    mbParameterRB<PAGES_POS_X2, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1> _wasCooles;
};


class mbPageMixer : public mbPage
{
    friend class UsbOutChanged;
    friend class LineOutChanged;
    friend class SendOutChanged;
public:
    mbPageMixer();
    void redraw() override;

private:
    class UsbOutChanged
    {
    public:
        void operator()(uint8_t value);
    };
    class LineOutChanged
    {
    public:
        void operator()(uint8_t value);
    };
    class SendOutChanged
    {
    public:
        void operator()(uint8_t value);
    };
    mbParameterRB<28, PAGES_POS_Y1, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, UsbOutChanged> _usbOut0;
    mbParameterRB<28, PAGES_POS_Y2, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, UsbOutChanged> _usbOut1;
    mbParameterRB<28, PAGES_POS_Y4, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, UsbOutChanged> _usbOut2;
    mbParameterRB<28, PAGES_POS_Y3, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, UsbOutChanged> _usbOut3;

    mbParameterRB<28+25, PAGES_POS_Y1, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, LineOutChanged> _lineOut0;
    mbParameterRB<28+25, PAGES_POS_Y2, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, LineOutChanged> _lineOut1;
    mbParameterRB<28+25, PAGES_POS_Y4, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, LineOutChanged> _lineOut2;
    mbParameterRB<28+25, PAGES_POS_Y3, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, LineOutChanged> _lineOut3;

    mbParameterRB<28+50, PAGES_POS_Y1, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, SendOutChanged> _sendOut0;
    mbParameterRB<28+50, PAGES_POS_Y2, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, SendOutChanged> _sendOut1;
    mbParameterRB<28+50, PAGES_POS_Y4, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, SendOutChanged> _sendOut2;
    mbParameterRB<28+50, PAGES_POS_Y3, PAGES_WIDTH_X1/2, PAGES_HEIGHT_X1, identityMapper, SendOutChanged> _sendOut3;
};

class mbPageFX : public mbPage
{
    friend class mbSynth; //uuuhhh move FX to own midi class
public:
    mbPageFX();
    void redraw() override;

private:
    class TriggerFlanger
    {
    public:
        void operator()(uint8_t value);
    };
    class TriggerWaveshaper
    {
    public:
        void operator()(uint8_t value);
    };
    class TriggerWaveGain
    {
    public:
        void operator()(uint8_t value);
    };
    class TriggerDelay
    {
    public:
        void operator()(uint8_t value);
    };
    class TriggerDelayFB
    {
    public:
        void operator()(uint8_t value);
    };
    class TriggerDelayMix
    {
    public:
        void operator()(uint8_t value);
    };
    mbParameterRB<PAGES_POS_X1, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerFlanger>    _paramFlanger;
    mbParameterRB<PAGES_POS_X0, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerWaveshaper> _paramWaveshaper;
    mbParameterRB<PAGES_POS_X0, PAGES_POS_Y2, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerWaveGain>   _paramWaveGain;
    mbParameterRB<PAGES_POS_X2, PAGES_POS_Y2, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerDelay>      _paramDelay;
    mbParameterRB<PAGES_POS_X2, PAGES_POS_Y3, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerDelayFB>    _paramDelayFB;
    mbParameterRB<PAGES_POS_X2, PAGES_POS_Y1, PAGES_WIDTH_X1, PAGES_HEIGHT_X1, identityMapper, TriggerDelayMix>   _paramDelayMix;
};



