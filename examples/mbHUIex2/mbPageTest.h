#pragma once

#include "mbConfig.h"

class mbPageTestDebugTrigger
{
public:
    void operator()(uint8_t value);
};

class mbPageTest : public PageType
{
  public:
    mbPageTest();

    void redraw() override;
    void update(bool forceDrawAll) override;

  private:
    int16_t pos2 = 0;

    mbParameterRB<16,0, 38,9, identityMapper, mbPageTestDebugTrigger> _irgnwas0;
    mbParameterRB<16,9, 38,9, identityMapper, mbPageTestDebugTrigger> _irgnwas1;
};
