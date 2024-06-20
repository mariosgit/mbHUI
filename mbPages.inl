template<class DisplayType>
uint8_t mbPage<DisplayType>::_fftBuffer[32];

template<class DisplayType>
int16_t mbPage<DisplayType>::_scopeBuffer[128*52];

template<class DisplayType>
mbPage<DisplayType>::mbPage(DisplayType& display, const char* name) :
    _name(name),
    _display( display )
{
    for(int i = 0; i < MB_MAX_PARAMS; i++)
        _params[i] = nullptr;
}

template<class DisplayType>
void mbPage<DisplayType>::changeActiveParam(int16_t val)
{
    _param += val;
    _param = _param % getParamCount();
    if(_param < 0)
        _param = getParamCount() - 1;
    setRedrawFlag();
}

template<class DisplayType>
void mbPage<DisplayType>::update(bool forceDrawAll)
{
    for(int i = 0; i < getParamCount(); i++)
    {
        auto *param = _params[i];
        if(!param)
            continue;
        if(!(param->getAndClearChanged() || forceDrawAll))
            continue;
        display().setTextSize(1);
        uint16_t bgcolor = _param == i ? DISPLAY_FG_COLOR : DISPLAY_DIM_BG_COLOR;
        uint16_t fgcolor = _param == i ? DISPLAY_BG_COLOR : DISPLAY_DIM_FG_COLOR;
        display().setTextColor(fgcolor, fgcolor);
        display().fillRoundRect(param->x(), param->y(), param->width(), param->height(), 3, bgcolor); //OUT box
        if(_param != i)
            display().drawRoundRect(param->x(), param->y(), param->width(), param->height(), 3, fgcolor); //OUT box
        display().setCursor(param->x()+3, param->y()+PAGES_HEIGHT_TEXT_OFFSET);
        display().print(param->name());
        const char* str = param->getString();
        if(str)
        {
            // Log.warning("oh a string: %d %s\n", param->getI(), str);
            int16_t  x1, y1;
            uint16_t w, h;
            display().getTextBounds((char*)str, 0, 0, &x1, &y1, &w, &h);
            display().setCursor(-3 + param->x() + param->width() - w, param->y()+PAGES_HEIGHT_TEXT_OFFSET);
            display().print(str);
        }
        else
        {
            auto mval = param->getMapped();
            int16_t  x1, y1;
            uint16_t w, h;
            char str[8];
            sprintf(str, "%d", mval);
            display().getTextBounds((char*)str, 0, 0, &x1, &y1, &w, &h);
            display().setCursor(-3 + param->x() + param->width() - w, param->y()+PAGES_HEIGHT_TEXT_OFFSET);
            display().print(str);
        }
        display().setTextColor(DISPLAY_FG_COLOR, DISPLAY_BG_COLOR);
    }
}

template<class DisplayType>
void mbPage<DisplayType>::setActive(bool val)
{
    _active = val;
}

template<class DisplayType>
const char* mbPage<DisplayType>::getParamName(uint8_t id)
{
    if(id > _paramCount)
        return nullptr;
    return _params[id]->name();
}

template<class DisplayType>
mbParameterBase* mbPage<DisplayType>::getParam(uint8_t id)
{
    if(id > _paramCount)
        return nullptr;
    return _params[id];
}

template<class DisplayType>
void mbPage<DisplayType>::restore()
{
    for(int i = 0; i < _paramCount; i++)
    {
        _params[i]->trigger();
    }
}

template<class DisplayType>
void mbPage<DisplayType>::encoderValue(int16_t val)
{
    // LOG <<"mbPage<DisplayType>::encoderValue:" <<val <<" p#:" <<getParamCount() <<"\n";
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
        // display().setDrawColor(_param == i ? 0 : 1);
        // display().drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        // display().setCursor(param->x()+2, param->y()+1);
        // display().print(param->name());
        // display().setDrawColor(_param == i ? 1 : 0);
        // display().drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        // auto mval = param->getMapped();
        // if(mval < -9)
        //     {display().print(mval);}
        // else if (mval < 0)
        //     {display().print(" "); display().print(mval);}
        // else if (mval < 10)
        //     {display().print("  "); display().print(mval);}
        // else if (mval < 100)
        //     {display().print(" "); display().print(mval);}
        // else
        //     {display().print(mval);}
    }
    // if(val)
    //     display().sendBuffer();
}

template<class DisplayType>
void mbPage<DisplayType>::changeParamValue(uint8_t paramid, int8_t val)
{
    if(paramid >= _paramCount)
        return;

    auto *param = _params[paramid];
    if(param) {
        param->add(val);
        param->trigger();
    }
}
