# HUI - Hardware User Interface

This manages a bunch of Parameters on multiple display pages. Each parameter is permanently saved to EEPROM.

Parameters can have different numerical types like byte, int, float. I used it mostly for bytes and then mapped it to whatever was needed.
Functions for value mapping can be added to each, so the internal value can be different to the displayed one.

Uses U8g2 lib as display. Pins are ~~hardcoded in mbDisplay.h~~ can be defined as macros, see below. Used on 128x32 monochrome OLEDs so far, should do on every display supported by the underlying lib.

Interaction via
* A Button to switch pages
* A Button to select the parameter
* Encoder to change value.


## Usage

You will need a config file "mbConfig.h" in your project. The order of defines and includes is important.

It includes you display lib first. Then defines DISPLAY_CONSTRUCTOR_CALL where you can pass parameters for your display e.g. pins...
After that the mbDisplay.h can be included and at the end the template types are defined.

```
#pragma once

#include <mbGFX_MN12832JC.h>

#define DISPLAY_CONSTRUCTOR_CALL _display()
#define DISPLAY_BEGIN_CODE

#include <mbDisplay.h>
#include <mbPages.h>

typedef mbDisplay<MN12832JC> DisplayType;
typedef mbPage<MN12832JC> PageType;
```

## Todo

* Add Examples &#10004; (NOT TESTED)
* Add Gif's
* More Generic Display (AdafruitGFX) &#10004;
* Parameter Types
* Font Y alignment, Scale to fit font.
