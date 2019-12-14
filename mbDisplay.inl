// from example code

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

// #if (SSD1306_LCDHEIGHT != 64)
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
// #endif


/* void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(_display->width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      _display->drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    _display->display();
    delay(200);

    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      _display->drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > _display->height()) {
        icons[f][XPOS] = random(_display->width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}
 */
/******************************************************************************/


/******************************************************************************/

template<class GFX> mbDisplay<GFX>* mbDisplay<GFX>::_the = nullptr;

template<class GFX>
mbDisplay<GFX>::mbDisplay() :
    //_display(OLED_DC, OLED_RESET, OLED_CS), // AdafruitGFX
    //_display(/*rotation=*/ OLED_ROTATION, /* cs=*/ OLED_CS, /* dc=*/ OLED_DC, /* reset=*/ OLED_RESET),
    _display(),
    _blanked(false)
{
    for(uint8_t i = 0; i < MB_MAX_PAGES; i++)
        _pages[i] = nullptr;
    _the = this;
}

template<class GFX>
void mbDisplay<GFX>::begin()
{
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    get().begin();
    // get().setFont(DISP_FONT1x);
    // get().setFontRefHeightExtendedText();
    // get().setFontMode(0); // 0-withBG, 1-noBG
    // get().setDrawColor(1); // 0-black, 1-white
    get().setTextColor(1, 0); // fore back
    // get().setFontPosTop();
    // get().setFontDirection(0);

    changeCurrentPage(_currentPage.get());
}

template<class GFX>
void mbDisplay<GFX>::restore()
{
    // range fix after restore
    if(_the->_currentPage.get() < 0)
        _the->_currentPage.get() = _the->_pagePtr - 1;
    _the->_currentPage.get() = _the->_currentPage.get() % _the->_pagePtr;

    // _currentPage.get() = 1;
    for(uint8_t i = 0; i < MB_MAX_PAGES; i++)
    {
        if(!_pages[i])
            continue;
        _pages[i]->setActive(false);
        _pages[i]->restore();
    }
    _pages[_currentPage.get()]->setActive(true);
    _pages[_currentPage.get()]->redraw();
}

template<class GFX>
void mbDisplay<GFX>::changeCurrentPage(int8_t val)
{
    if( _the->_pages[_the->_currentPage.get()] )
        _the->_pages[_the->_currentPage.get()]->setActive(false);
    _the->_currentPage.get() = (_the->_currentPage.get() + val);
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    if(_the->_currentPage.get() < 0)
        _the->_currentPage.get() = _the->_pagePtr - 1;
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    _the->_currentPage.get() = _the->_currentPage.get() % _the->_pagePtr;
    Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    if( _the->_pages[_the->_currentPage.get()] )
    {
        Log.warning("mbDisplay::changeCurrentPage #%d p:%p\n", _the->_currentPage.get(), _the->_pages[_the->_currentPage.get()]);
        _the->_pages[_the->_currentPage.get()]->setActive(true);
        _the->_pages[_the->_currentPage.get()]->redrawFlag();
        _the->unblank();
    }
    else
    {
        Log.warning("mbDisplay::changeCurrentPage #%d p:nullPtr\n", _the->_currentPage.get());
    }
}

template<class GFX>
void mbDisplay<GFX>::changeActiveParam(int8_t val)
{
    if( _the->_pages[_the->_currentPage.get()] )
        _the->_pages[_the->_currentPage.get()]->changeActiveParam(val);
}

template<class GFX>
void mbDisplay<GFX>::addPage(PageType *page)
{
    _the->_pages[_the->_pagePtr++] = page;
    if(_pagePtr >= MB_MAX_PAGES)
    {
        Log.error(F("Pages FULL\n"));
    }
}


template<class GFX>
mbDisplay<GFX>* mbDisplay<GFX>::the()
{
    if(!_the)
        _the = new mbDisplay;
    return _the;
}

template<class GFX>
void mbDisplay<GFX>::blank()
{
    Log.notice(F("**************** blank *****************\n"));
    get().setDrawColor(0);
    get().drawBox(0,0, 128,64);
    get().setDrawColor(1);
    get().sendBuffer();
    _blanked = true;
}

template<class GFX>
void mbDisplay<GFX>::unblank()
{
    if(!_blanked)
        return;
    restore();
    getPage().update();
    _blanked = false;
}
