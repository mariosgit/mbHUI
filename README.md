# HUI - Hardware User Interface

This manages a bunch of Parameters on multiple display pages. Each parameter is permanently saved to EEPROM.

Parameters can have different numerical types like byte, int, float. I used it mostly for bytes and then mapped it to whatever was needed.
Functions for value mapping can be added to each, so the internal value can be different to the displayed one.

Uses U8g2 lib as display. Pins are hardcoded in mbDisplay.h, used on 128x32 OLEDs so far.

Interaction via
* A Button to switch pages
* A Button to select the parameter
* Encoder to change value.

## Todo

* Add Examples
* Add Gif's
* More Generic Display (AdafruitGFX)
* Parameter Types
* Font Y alignment, Scale to fit font.
