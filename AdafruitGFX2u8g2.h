#include <mbLog.h>
#include <Adafruit_GFX.h>
#include <U8g2lib.h>


//// 2.42" OLED:
//typedef U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI U8G2DisplayType;
// #define OLED_ROTATION U8G2_R0
//// 1.3" mono OLED:
// typedef U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI U8G2DisplayType;
// #define OLED_ROTATION U8G2_R2
// typedef mbDisplay<U8G2DisplayType> DisplayType;
// typedef mbPage<U8G2DisplayType> PageType;

template <class U8G2Type>
class AdafruitGFX2u8g2 : public Adafruit_GFX
{
public:
    AdafruitGFX2u8g2(const u8g2_cb_t *rotation, uint8_t cs = U8X8_PIN_NONE, uint8_t dc = U8X8_PIN_NONE, uint8_t reset = U8X8_PIN_NONE) :
        Adafruit_GFX(128,64),
        u8g2(rotation, cs, dc, reset)
    {

    }

    void begin()
    {
        u8g2.begin();
        // LOG << "AdafruitGFX2u8g2.begin\n";
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
        u8g2.clearDisplay();
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
protected:
    U8G2Type u8g2;
};

/*


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

  // These exist only with Adafruit_GFX (no subclass overrides)
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
      drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
                       uint16_t color),
      fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
      fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
                       int16_t delta, uint16_t color),
      drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2,
                   int16_t y2, uint16_t color),
      fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2,
                   int16_t y2, uint16_t color),
      drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                    int16_t radius, uint16_t color),
      fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                    int16_t radius, uint16_t color),
      drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                 int16_t h, uint16_t color),
      drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                 int16_t h, uint16_t color, uint16_t bg),
      drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
                 uint16_t color),
      drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
                 uint16_t color, uint16_t bg),
      drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
                  int16_t h, uint16_t color),
      drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                          int16_t w, int16_t h),
      drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                          int16_t h),
      drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                          const uint8_t mask[], int16_t w, int16_t h),
      drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask,
                          int16_t w, int16_t h),
      drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w,
                    int16_t h),
      drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w,
                    int16_t h),
      drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
                    const uint8_t mask[], int16_t w, int16_t h),
      drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask,
                    int16_t w, int16_t h),
      drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
               uint16_t bg, uint8_t size),
      drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
               uint16_t bg, uint8_t size_x, uint8_t size_y),
      getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1,
                    int16_t *y1, uint16_t *w, uint16_t *h),
      getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,
                    int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h),
      getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1,
                    int16_t *y1, uint16_t *w, uint16_t *h),
      setTextSize(uint8_t s), setTextSize(uint8_t sx, uint8_t sy),
      setFont(const GFXfont *f = NULL);

*/