#pragma once

#include <mbGFX_MN12832JC.h>

typedef MN12832JC NativeDisplayType;
#define DISPLAY_CONSTRUCTOR_CALL _display()
#define DISPLAY_BEGIN_CODE       _display.begin();
#define DISPLAY_UPDATE_CODE      _display.display();
#define PAGES_WIDTH 42
#define PAGES_HEIGHT 11
#define PAGES_HEIGHT_OFF 1
#define PAGES_HEIGHT_TEXT_OFFSET 1

#include <mbDisplay.h>
#include <mbPages.h>
