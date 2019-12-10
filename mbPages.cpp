#include "mbPages.h"
#include "mbDisplay.h"
#include <Audio.h>
#include <ArduinoLog.h>

 // 'IMG_0229', 128x32px
static const unsigned char PROGMEM mbWurmi_bmp [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x03, 0x22, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x00,
	0x00, 0x00, 0x1c, 0xdf, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
	0x00, 0x06, 0x2c, 0xa3, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
	0x01, 0x1f, 0x46, 0x81, 0x80, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x06, 0xff, 0xe1, 0x28, 0x00,
	0x03, 0x23, 0x46, 0x81, 0x80, 0x00, 0x07, 0x9c, 0x80, 0x00, 0x00, 0x1b, 0x6f, 0xff, 0x02, 0x00,
	0x01, 0x23, 0x86, 0x83, 0x00, 0x00, 0x09, 0xa4, 0x80, 0x00, 0x00, 0x0d, 0xff, 0xff, 0xa1, 0x00,
	0x01, 0xc1, 0x87, 0x9c, 0x00, 0x06, 0x71, 0xc4, 0x80, 0x00, 0x24, 0x5b, 0xff, 0x5f, 0x61, 0x00,
	0x01, 0xc1, 0x06, 0xf0, 0x00, 0x3c, 0x60, 0x8c, 0xc0, 0x00, 0x08, 0x1f, 0xff, 0xfe, 0xe1, 0x40,
	0x01, 0xc0, 0x00, 0x00, 0x03, 0x30, 0x61, 0x88, 0xf0, 0x00, 0x00, 0xff, 0x7f, 0xfe, 0x70, 0x00,
	0x00, 0xc0, 0x00, 0x00, 0x06, 0x30, 0x20, 0x00, 0x00, 0x01, 0x00, 0x7b, 0xf3, 0x9e, 0x90, 0x00,
	0x00, 0xc0, 0x60, 0xf0, 0x86, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x2d, 0xc0, 0x00,
	0x00, 0xc0, 0x40, 0x18, 0x86, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf4, 0xdb, 0xc0, 0x00,
	0x00, 0x00, 0x80, 0x0d, 0x8e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xff, 0xe3, 0xc0, 0x00,
	0x00, 0x01, 0x80, 0x0d, 0x93, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3d, 0xe7, 0x7f, 0xc0, 0x00,
	0x00, 0x01, 0x00, 0x05, 0xe0, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x16, 0x7f, 0xef, 0x00, 0x01,
	0x00, 0x03, 0x16, 0x0d, 0x80, 0x00, 0x01, 0x68, 0x00, 0x00, 0x80, 0x0c, 0xe0, 0xfc, 0x00, 0x00,
	0x00, 0x02, 0x26, 0x08, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x02, 0x3d, 0x58, 0x01, 0x00,
	0x00, 0x06, 0xc3, 0x18, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x09, 0x08, 0x00, 0x00,
	0x00, 0x07, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x20, 0x02, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x20, 0x00, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/**********************************************************/


uint8_t mbPage::_fftBuffer[32];
int16_t mbPage::_scopeBuffer[128*52];

mbPage::mbPage() :
    _display(*DisplayType::the())
{
    for(int i = 0; i < MB_MAX_PARAMS; i++)
        _params[i] = nullptr;
}

void mbPage::changeActiveParam(int16_t val)
{
    _param += val;
    _param = _param % getParamCount();
    if(_param < 0)
        _param = getParamCount() - 1;
    update(true);
}

void mbPage::update(bool forceDrawAll)
{
    for(int i = 0; i < getParamCount(); i++)
    {
        auto *param = _params[i];
        if(!param)
            continue;
        if(!(param->getAndClearChanged() || forceDrawAll))
            continue;
        DISP.setDrawColor(_param == i ? 0 : 1);
        DISP.drawRBox(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        // DISP.drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        DISP.setCursor(param->x()+2, param->y()+1);
        DISP.print(param->name());
        DISP.setDrawColor(_param == i ? 1 : 0);
        DISP.drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        const char* str = param->getString();
        if(str)
        {
            // Log.warning("oh a string: %d %s\n", param->getI(), str);
            DISP.print(str);
        }
        else
        {
            auto mval = param->getMapped();
            if(mval < -9)
                {DISP.print(mval);}
            else if (mval < 0)
                {DISP.print(" "); DISP.print(mval);}
            else if (mval < 10)
                {DISP.print("  "); DISP.print(mval);}
            else if (mval < 100)
                {DISP.print(" "); DISP.print(mval);}
            else
                {DISP.print(mval);}
        }
    }
    DISP.sendBuffer();
}

void mbPage::setActive(bool val)
{
    _active = val;
}

void mbPage::restore()
{

}

void mbPage::encoderValue(int16_t val)
{
    for(int i = 0; i < getParamCount(); i++)
    {
        auto *param = _params[i];
        if(!param)
            continue;
        if(_param == i)
        {
            param->add(val);
            param->trigger();
        }
        // DISP.setDrawColor(_param == i ? 0 : 1);
        // DISP.drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        // DISP.setCursor(param->x()+2, param->y()+1);
        // DISP.print(param->name());
        // DISP.setDrawColor(_param == i ? 1 : 0);
        // DISP.drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        // auto mval = param->getMapped();
        // if(mval < -9)
        //     {DISP.print(mval);}
        // else if (mval < 0)
        //     {DISP.print(" "); DISP.print(mval);}
        // else if (mval < 10)
        //     {DISP.print("  "); DISP.print(mval);}
        // else if (mval < 100)
        //     {DISP.print(" "); DISP.print(mval);}
        // else
        //     {DISP.print(mval);}
    }
    // if(val)
    //     DISP.sendBuffer();
}

/**********************************************************/

void mbPageCover::redraw()
{
    if(!_active)
        return;
    DISP.clearBuffer();

    DISP.setFontMode(0); // 0-withBG, 1-noBG
    DISP.setDrawColor(1); // 0-black, 1-white

    DISP.drawBitmap(0, 0, 128/8, 32, mbWurmi_bmp);

    DISP.setCursor(7,32);
    DISP.print("intergalactic connector");
    DISP.setCursor(20,42);
    DISP.print("Mario Becker @2018");
    DISP.setCursor(20,54);
    DISP.print("   version:");
    DISP.print(_version);
    DISP.drawLine(18, 52, 110, 52);

    DISP.sendBuffer();
}

/**********************************************************/

/*******************************************************************/


/*******************************************************************/

void mbPageCV::redraw()
{
    if(!_active)
        return;
    DISP.clearBuffer();

    DISP.setFontMode(0); // 0-withBG, 1-noBG
    DISP.setDrawColor(1); // 0-black, 1-white

    DISP.setCursor(0,0);
    DISP.print("CV-IO");

    update(true);

    DISP.sendBuffer();
}

/*******************************************************************/
extern mbPageMixer _pageMixer;
extern AudioMixer4 mixerUsb1, mixerUsb2;
extern AudioMixer4 mixerLine1, mixerLine2;
extern AudioMixer4 mixerSend1, mixerSend2;
void mbPageMixer::UsbOutChanged::operator()(uint8_t value)
{
    mixerUsb1.gain(0, 0.09 * _pageMixer._usbOut0.get());
    mixerUsb1.gain(1, 0.09 * _pageMixer._usbOut1.get());
    mixerUsb1.gain(2, 0.09 * _pageMixer._usbOut2.get());
    mixerUsb1.gain(3, 0.09 * _pageMixer._usbOut3.get());
    mixerUsb2.gain(0, 0.09 * _pageMixer._usbOut0.get());
    mixerUsb2.gain(1, 0.09 * _pageMixer._usbOut1.get());
    mixerUsb2.gain(2, 0.09 * _pageMixer._usbOut2.get());
    mixerUsb2.gain(3, 0.09 * _pageMixer._usbOut3.get());
}
void mbPageMixer::LineOutChanged::operator()(uint8_t value)
{
    mixerLine1.gain(0, 0.09 * _pageMixer._lineOut0.get());
    mixerLine1.gain(1, 0.09 * _pageMixer._lineOut1.get());
    mixerLine1.gain(2, 0.09 * _pageMixer._lineOut2.get());
    mixerLine1.gain(3, 0.09 * _pageMixer._lineOut3.get());
    mixerLine2.gain(0, 0.09 * _pageMixer._lineOut0.get());
    mixerLine2.gain(1, 0.09 * _pageMixer._lineOut1.get());
    mixerLine2.gain(2, 0.09 * _pageMixer._lineOut2.get());
    mixerLine2.gain(3, 0.09 * _pageMixer._lineOut3.get());
}
void mbPageMixer::SendOutChanged::operator()(uint8_t value)
{
    mixerSend1.gain(0, 0.09 * _pageMixer._sendOut0.get());
    mixerSend1.gain(1, 0.09 * _pageMixer._sendOut1.get());
    mixerSend1.gain(2, 0.09 * _pageMixer._sendOut2.get());
    mixerSend1.gain(3, 0.09 * _pageMixer._sendOut3.get());
    mixerSend2.gain(0, 0.09 * _pageMixer._sendOut0.get());
    mixerSend2.gain(1, 0.09 * _pageMixer._sendOut1.get());
    mixerSend2.gain(2, 0.09 * _pageMixer._sendOut2.get());
    mixerSend2.gain(3, 0.09 * _pageMixer._sendOut3.get());
}

mbPageMixer::mbPageMixer() : mbPage(),
    _usbOut0("", 0,10),
    _usbOut1("", 0,10),
    _usbOut2("", 0,10),
    _usbOut3("", 0,10),
    _lineOut0("", 0,10),
    _lineOut1("", 0,10),
    _lineOut2("", 0,10),
    _lineOut3("", 0,10),
    _sendOut0("", 0,10),
    _sendOut1("", 0,10),
    _sendOut2("", 0,10),
    _sendOut3("", 0,10)
{
    _params[_paramCount++] = &_usbOut0;
    _params[_paramCount++] = &_usbOut1;
    _params[_paramCount++] = &_usbOut3;
    _params[_paramCount++] = &_usbOut2;
    _params[_paramCount++] = &_lineOut0;
    _params[_paramCount++] = &_lineOut1;
    _params[_paramCount++] = &_lineOut3;
    _params[_paramCount++] = &_lineOut2;
    _params[_paramCount++] = &_sendOut0;
    _params[_paramCount++] = &_sendOut1;
    _params[_paramCount++] = &_sendOut3;
    _params[_paramCount++] = &_sendOut2;
}

void mbPageMixer::redraw()
{
    if(!_active)
        return;
    DISP.clearBuffer();

    DISP.setFontMode(0); // 0-withBG, 1-noBG
    DISP.setDrawColor(1); // 0-black, 1-white

    DISP.setCursor(0,0);
    DISP.print("MIXER");

    // Raster 0 28 +4x25

    // Inputs
    DISP.setCursor(5,12);
    DISP.print("usb");
    DISP.setCursor(0,24);
    DISP.print("line");
    DISP.setCursor(5,36);
    DISP.print(" fx");
    DISP.setCursor(0,48);
    DISP.print("synv");
    // Outputs
    DISP.setCursor(32,-2);
    DISP.print("usb");
    DISP.setCursor(28+25,-2);
    DISP.print("line");
    DISP.setCursor(28+50,-2);
    DISP.print(" fx");
    // DISP.setCursor(28+75,0);
    // DISP.print("...");

    // U8G2::drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1);
    // horizontal
    DISP.drawLine(26, 12+6, 25+12+50-1, 12+6);
    DISP.drawLine(26, 24+6, 25+12+50-1, 24+6);
    DISP.drawLine(26, 36+6, 25+12+50-1, 36+6);
    DISP.drawLine(26, 48+6, 25+12+50-1, 48+6);
    // vertical
    DISP.drawLine(25+12,    12-4, 25+12,    53);
    DISP.drawLine(25+12+25, 12-4, 25+12+25, 53);
    DISP.drawLine(25+12+50, 12-4, 25+12+50, 53);
    //DISP.drawLine(25+12+75, 12+4, 25+12+75, 53);
    // arrows >
    DISP.drawLine(22, 18-2, 24, 18);
    DISP.drawLine(22, 18+2, 24, 18);
    DISP.drawLine(22, 18-2+12, 24, 18+12);
    DISP.drawLine(22, 18+2+12, 24, 18+12);
    DISP.drawLine(22, 18-2+24, 24, 18+24);
    DISP.drawLine(22, 18+2+24, 24, 18+24);
    DISP.drawLine(22, 18-2+36, 24, 18+36);
    DISP.drawLine(22, 18+2+36, 24, 18+36);
    // arrows^^
    DISP.drawLine(25+10,    12-2, 25+12,    12-4);
    DISP.drawLine(25+14,    12-2, 25+12,    12-4);
    DISP.drawLine(50+10,    12-2, 50+12,    12-4);
    DISP.drawLine(50+14,    12-2, 50+12,    12-4);
    DISP.drawLine(75+10,    12-2, 75+12,    12-4);
    DISP.drawLine(75+14,    12-2, 75+12,    12-4);

    DISP.setCursor(104,10);
    DISP.print("mind");
    DISP.setCursor(108,20);
    DISP.print("the");
    DISP.setCursor(104,30);
    DISP.print("feed");
    DISP.setCursor(104,40);
    DISP.print("back");
    DISP.setCursor(110,50);
    DISP.print(":-P");

    DISP.drawLine(0, 12-2, 23, 12-2);
    // DISP.drawLine(27, 0, 25, 10);
    // DISP.drawLine(100, 12-2, 125, 12-2);
    // DISP.drawLine(102, 0, 100, 10);
    // DISP.drawLine(112, 0, 110, 10);
    // DISP.drawLine(122, 0, 120, 10);
    // DISP.drawLine(100, 11, 100, 63);

    DISP.drawLine(40, 18, 110, 16+37);
    DISP.drawLine(100, 51, 110, 16+40);
    DISP.drawLine(100, 54, 110, 16+43);

    update(true);

    DISP.sendBuffer();
}

/*******************************************************************/
extern AudioMixer4 mixerFx1, mixerFx2, mixerFxPre, delayInMixer;
extern AudioEffectWaveshaper    _waveshaper;
extern AudioEffectFlange        flanger1, flanger2;
extern AudioEffectDelay         delayFX;
extern AudioFilterStateVariable delayFilter1, delayFilter2;
void mbPageFX::TriggerFlanger::operator()(uint8_t value)
{
    mixerFx1.gain(2, .95 * 1./128. * value);
    mixerFx2.gain(2, .95 * 1./128. * value);
}
void mbPageFX::TriggerWaveshaper::operator()(uint8_t value)
{
    mixerFx1.gain(1, .95 * 1./128. * value);
    mixerFx2.gain(1, .95 * 1./128. * value);
}
void mbPageFX::TriggerWaveGain::operator()(uint8_t value)
{
    mixerFxPre.gain(0, .9 + 5./128. * value);
    mixerFxPre.gain(1, .9 + 5./128. * value);
}
void mbPageFX::TriggerDelay::operator()(uint8_t value)
{
    delayFX.delay(0, 3 * value);
    delayFX.delay(4, 2 * value);
}
void mbPageFX::TriggerDelayFB::operator()(uint8_t value)
{
    delayInMixer.gain(1, .95 * 1./128. * value);
    delayInMixer.gain(3, .95 * 1./128. * value);
}
void mbPageFX::TriggerDelayMix::operator()(uint8_t value)
{
    mixerFx1.gain(3, .5 * 1./128. * value);
    mixerFx2.gain(3, .5 * 1./128. * value);
}

mbPageFX::mbPageFX() : mbPage(),
    _paramFlanger("flgr", 0, 127),
    _paramWaveshaper("dist", 0, 127),
    _paramWaveGain("gain", 0, 127),
    _paramDelay("dely", 0, 127),
    _paramDelayFB("defb", 0, 127),
    _paramDelayMix("dmix", 0, 127)
{
    _params[_paramCount++] = &_paramWaveshaper;
    _params[_paramCount++] = &_paramWaveGain;
    _params[_paramCount++] = &_paramFlanger;
    _params[_paramCount++] = &_paramDelayMix;
    _params[_paramCount++] = &_paramDelay;
    _params[_paramCount++] = &_paramDelayFB;
}

void mbPageFX::redraw()
{
    if(!_active)
        return;
    DISP.clearBuffer();

    DISP.setFontMode(0); // 0-withBG, 1-noBG
    DISP.setDrawColor(1); // 0-black, 1-white

    DISP.setCursor(0,0);
    DISP.print("FX");

    // Raster 0 28 +4x25


    DISP.drawLine(0, 12-2, 10, 12-2);
    // DISP.drawLine(27, 0, 25, 10);
    // DISP.drawLine(100, 12-2, 125, 12-2);
    // DISP.drawLine(102, 0, 100, 10);
    // DISP.drawLine(112, 0, 110, 10);
    // DISP.drawLine(122, 0, 120, 10);
    // DISP.drawLine(100, 11, 100, 63);

    // DISP.drawLine(40, 18, 110, 16+37);
    // DISP.drawLine(100, 51, 110, 16+40);
    // DISP.drawLine(100, 54, 110, 16+43);

    update(true);

    DISP.sendBuffer();
}
