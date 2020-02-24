#pragma once

#include <mbGFX_MN12832JC.h>

#define DISPLAY_CONSTRUCTOR_CALL _display()
#define DISPLAY_BEGIN_CODE

#include <mbDisplay.h>
#include <mbPages.h>

typedef mbDisplay<MN12832JC> DisplayType;
typedef mbPage<MN12832JC> PageType;
