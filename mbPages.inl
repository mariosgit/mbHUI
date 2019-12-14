
template<class DisplayType>
uint8_t mbPage<DisplayType>::_fftBuffer[32];

template<class DisplayType>
int16_t mbPage<DisplayType>::_scopeBuffer[128*52];

template<class DisplayType>
mbPage<DisplayType>::mbPage() :
    _display(* (mbDisplay<DisplayType>::the()) )
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
    redrawFlag();
    // update(true);
}

template<class DisplayType>
void mbPage<DisplayType>::update(bool forceDrawAll)
{
    if(_redraw)
    {
        _redraw = false;
        redraw();
    }
    for(int i = 0; i < getParamCount(); i++)
    {
        auto *param = _params[i];
        if(!param)
            continue;
        if(!(param->getAndClearChanged() || forceDrawAll))
            continue;
        display().setTextSize(1);
        uint16_t bgcolor = _param == i ? 1 : 0;
        uint16_t fgcolor = _param == i ? 0 : 1;
        display().setTextColor(fgcolor, bgcolor);
        display().fillRoundRect(param->x(), param->y(), param->width(), param->height(), 3, bgcolor); //OUT box
        if(_param == i)
            display().drawRoundRect(param->x(), param->y(), param->width(), param->height(), 3, fgcolor); //OUT box
        // display().drawRFrame(param->x(), param->y(), param->width(), param->height(), 3); //OUT box
        display().setCursor(param->x()+2, param->y()+6);
        display().print(param->name());
        // display().drawRoundRect(param->x(), param->y(), param->width(), param->height(), 3, fgcolor); //OUT box
        const char* str = param->getString();
        if(str)
        {
            // Log.warning("oh a string: %d %s\n", param->getI(), str);
            display().print(str);
        }
        else
        {
            auto mval = param->getMapped();
            if(mval < -9)
                {display().print(mval);}
            else if (mval < 0)
                {display().print(" "); display().print(mval);}
            else if (mval < 10)
                {display().print("  "); display().print(mval);}
            else if (mval < 100)
                {display().print(" "); display().print(mval);}
            else
                {display().print(mval);}
        }
        display().setTextColor(1, 0);
    }
    display().swapBuffers();
}

template<class DisplayType>
void mbPage<DisplayType>::setActive(bool val)
{
    _active = val;
}

template<class DisplayType>
void mbPage<DisplayType>::restore()
{

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
