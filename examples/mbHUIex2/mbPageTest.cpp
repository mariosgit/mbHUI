#include <mbLog.h>
#include "mbPageTest.h"

void mbPageTestDebugTrigger::operator()(uint8_t value)
{
    LOG <<"irgnwas:" <<value <<"\n";
}

mbPageTest::mbPageTest() : PageType(),
    _irgnwas0("a", 0, 64),
    _irgnwas1("b", 128, 255)
{
    _params[_paramCount++] = &_irgnwas0;
    _params[_paramCount++] = &_irgnwas1;
}

void mbPageTest::redraw()
{
    LOG <<"mbPageTest::redraw\n";
}

void mbPageTest::update(bool forceDrawAll)
{
    display().fillScreen(0);

    display().setTextSize(1);
    display().setCursor(128+42+pos2, 29);
    display().print("This is a test !!!");

    // Volume
    int16_t  x1, y1;
    uint16_t w, h;
    char str[4];
    sprintf(str, "%d%%", 12);
    display().setTextSize(2);
    display().getTextBounds(str, 0, 0, &x1, &y1, &w, &h);
    display().setCursor(126-w, 14);
    display().print(str);

    pos2 -= 1;
    pos2 = (pos2 % 300);

    // display().fillRect(0,0,16,31,0);
    // display().drawLine(0,-_peakLevel1, 5,-_peakLevel1, 1);
    // display().drawLine(7,-_peakLevel2,12,-_peakLevel2, 1);
    // display().fillRect(0,-_level1, 2, 32+_level1, 1);
    // display().fillRect(7,-_level2, 2, 32+_level2, 1);

    PageType::update(true); //we cleared the screen...
}
