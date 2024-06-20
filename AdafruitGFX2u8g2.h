#include <Adafruit_GFX.h>

#define U8X8_NO_HW_I2C // disable I2C parts -> tut nix, hard auskommentiert ! Wegen ld error multiple defs..
#include <U8g2lib.h>

/**
  Wrap u8g2 display in a Adafruit_GFX class.
  
   Example: (this would go into ```mbConfig.h```)
   ```
   const byte pinCS = 10;
   const byte pinReset = 9;
   typedef AdafruitGFX2u8g2<U8G2_GP1294AI_256X48_F_4W_HW_SPI,256,48> NativeDisplayType;
   #define DISPLAY_CONSTRUCTOR_CALL _display(U8G2_R0, pinCS, U8X8_PIN_NONE, pinReset)
   #define DISPLAY_BEGIN_CODE       _display.begin();
   #define DISPLAY_UPDATE_CODE      _display.display();
   #include <mbDisplay.h>
   #include <mbPages.h>
   ```
*/
template <class U8G2Type,int resX,int resY>
class AdafruitGFX2u8g2 : public Adafruit_GFX
{
public:
    AdafruitGFX2u8g2(const u8g2_cb_t *rotation, uint8_t cs, uint8_t dc, uint8_t reset) :
        Adafruit_GFX(resX, resY),
        u8g2(rotation, cs, dc, reset)
    {

    }
    AdafruitGFX2u8g2(const u8g2_cb_t *rotation, uint8_t cs, uint8_t reset) :
        Adafruit_GFX(resX,resY),
        u8g2(rotation, cs, reset)
    {

    }

    void begin()
    {
        u8g2.begin();
        // LOG << "AdafruitGFX2u8g2.begin\n";
        u8g2.setContrast(50);
    }

    void dim(bool value)
    {
        // u8g2.dim();
    }

    void drawPixel(
        int16_t x, int16_t y,
        uint16_t color) override
    {
        u8g2.setDrawColor(color);
        u8g2.drawPixel(x, y);
    }

    void clearDisplay()
    {
        u8g2.clearBuffer();
    }

    void display()
    {
        u8g2.sendBuffer();
        // LOG << "AdafruitGFX2u8g2.display\n";
    }

    void setCursor(int16_t x, int16_t y)
    {
        // u8g cursor is at top of char, Ada is at baseline
        Adafruit_GFX::setCursor(x,y+6);
    }

    // implement me !
    inline void drawCentreString(const char* text, int16_t dx, int16_t y0, uint8_t color)
    {
        u8g2.drawStr(dx,y0,text);
    }
    inline void drawRightString(const char* text, int16_t dx, int16_t y0, uint8_t color)
    {
        u8g2.drawStr(dx,y0,text);
    }
    inline void drawLeftString(const char* text, int16_t dx, int16_t y0, uint8_t color)
    {
        u8g2.drawStr(dx,y0,text);
    }

    // Returns a reference to the u8g2 instance.
    inline U8G2Type& native() { return u8g2; }

protected:
    U8G2Type u8g2;
};

/*
// All virtual funcs...

public:
  Adafruit_GFX(int16_t w, int16_t h); // Constructor

  // This MUST be defined by the subclass:
  virtual void drawPixel(
      int16_t x, int16_t y,
      uint16_t color) = 0; ///< Virtual drawPixel() function to draw to the
                           ///< screen/framebuffer/etc, must be overridden in
                           ///< subclass. @param x X coordinate.  @param y Y
                           ///< coordinate. @param color 16-bit pixel color.

  // TRANSACTION API / CORE DRAW API
  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void startWrite(void);
  virtual void writePixel(int16_t x, int16_t y, uint16_t color);
  virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                             uint16_t color);
  virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                         uint16_t color);
  virtual void endWrite(void);

  // CONTROL API
  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void setRotation(uint8_t r);
  virtual void invertDisplay(boolean i);

  // BASIC DRAW API
  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void
  // It's good to implement those, even if using transaction API
  drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
      drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
      fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
      fillScreen(uint16_t color),
      // Optional and probably not necessary to change
      drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color),
      drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
*/