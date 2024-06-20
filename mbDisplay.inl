template<class GFX>
mbDisplay<GFX>::mbDisplay() :
    DISPLAY_CONSTRUCTOR_CALL,  // defined in mbConfig.h
    _timerBlank(0),
    _blankTime(60*1000), // min*sec*ms
    _blankPage(-1),
    _blanked(false)
{
    for(uint8_t i = 0; i < MB_MAX_PAGES; i++)
        _pages[i] = nullptr;
}

template<class GFX>
void mbDisplay<GFX>::begin()
{
    DISPLAY_BEGIN_CODE  // defined in mbConfig.h
    // display().setFont(DISP_FONT1x);
    // display().setFontRefHeightExtendedText();
    // display().setFontMode(0); // 0-withBG, 1-noBG
    // display().setDrawColor(1); // 0-black, 1-white
    // display().setTextColor(1, 0); // fore back
    // display().setFontPosTop();
    // display().setFontDirection(0);

    if(_pageCount)
        changeCurrentPage(_currentPage.get());
}

template<class GFX>
void mbDisplay<GFX>::restore()
{
    // range fix after restore
    if(_currentPage.get() < 0)
        _currentPage.get() = _pageCount - 1;
    _currentPage.get() = _currentPage.get() % _pageCount;

    // _currentPage.get() = 1;
    for(uint8_t i = 0; i < MB_MAX_PAGES; i++)
    {
        if(!_pages[i])
            continue;
        _pages[i]->setActive(false);
        _pages[i]->restore();
    }
    _pages[_currentPage.get()]->setActive(true);
    _pages[_currentPage.get()]->setRedrawFlag();
}

template<class GFX>
void mbDisplay<GFX>::setCurrentPage(int8_t val)
{
    changeCurrentPage(val - _currentPage.get());
}

template<class GFX>
void mbDisplay<GFX>::changeCurrentPage(int8_t val, bool force)
{
    _timerBlank = 0;
    if(force)
        _currentPage = 0;
    if(_timerBlank > _blankTime)
        return;
    if( _pages[_currentPage.get()] )
        _pages[_currentPage.get()]->setActive(false);
    _currentPage.get() = (_currentPage.get() + val);
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _currentPage);
    if(_currentPage.get() < 0)
        _currentPage.get() = _pageCount - 1;
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _currentPage);
    _currentPage.get() = _currentPage.get() % _pageCount;
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _currentPage);
    if(_pages[_currentPage.get()] )
    {
        LOG <<LOG.dec <<"mbDisplay::changeCurrentPage #" <<_currentPage.get();
        LOG <<LOG.hex <<" p:" <<(int32_t)(_pages[_currentPage.get()]) <<"\n";
        _pages[_currentPage.get()]->setActive(true);
        _pages[_currentPage.get()]->setRedrawFlag();
        unblank();
    }
    else
    {
        LOG <<"mbDisplay::changeCurrentPage #" << _currentPage.get() <<" p:nullPtr\n" ;
    }
}

template<class GFX>
void mbDisplay<GFX>::changeActiveParam(int8_t val)
{
    _timerBlank = 0;
    if(_timerBlank > _blankTime)
        return;
    if( _pages[_currentPage.get()] )
        _pages[_currentPage.get()]->changeActiveParam(val);
}

template<class GFX>
void mbDisplay<GFX>::changeParamValue(int8_t val)
{
    _timerBlank = 0;
    if(_timerBlank > _blankTime)
        return;
    getCurrentPage().encoderValue(val);
}

template<class GFX>
void mbDisplay<GFX>::changeParamValue(uint8_t paramid, int8_t val)
{
    _timerBlank = 0;
    if(_timerBlank > _blankTime)
        return;
    getCurrentPage().changeParamValue(paramid, val);
}

template<class GFX>
void mbDisplay<GFX>::addPage(PageType *page)
{
    _pages[_pageCount++] = page;
    if(_pageCount >= MB_MAX_PAGES)
    {
        LOG <<"Pages FULL\n";
    }
}

template<class GFX>
typename mbDisplay<GFX>::PageType& mbDisplay<GFX>::getPage(uint8_t id)
{
    if(id > _pageCount)
        return *(_pages[0]);
    return *(_pages[id]);
}

template<class GFX>
typename mbDisplay<GFX>::PageType& mbDisplay<GFX>::getCurrentPage()
{
    // when blanked and a blankpage is set, use this...
    if(_blanked && _blankPage != -1) {
        return *(_pages[_blankPage]);
    }
    // otherwise be normal.
    return *(_pages[_currentPage.get()]);
}

template<class GFX>
void mbDisplay<GFX>::blank()
{
    LOG <<"**************** blank *****************\n";
    if(_blankPage != -1 && _blankPage < _pageCount)
    {
        // _currentPage.set(_blankPage);
    }
    else
    {
        display().clearDisplay();
        display().display();
    }


    if(_blankFunc) {
        _blankFunc();
    }
    _blanked = true;
}

template<class GFX>
void mbDisplay<GFX>::unblank()
{
    if(!_blanked)
        return;
    LOG <<"**************** unblank ***************\n";
    _timerBlank = 0;
    if(_unblankFunc) {
        _unblankFunc();
    }
    restore();
    DISPLAY_UPDATE_CODE
    _blanked = false;
}

template<class GFX>
void mbDisplay<GFX>::update()
{
    if(_timerBlank > _blankTime)
    {
        if(!_blanked)
            blank();
    }
    else
    {
        unblank();
    }

    // LOG <<"update0 n:" <<getCurrentPage().getPageName() <<" \n";
    if(!_blanked || _blankPage != -1)
    {
        if(getCurrentPage().getRedrawFlag())
        {
            getCurrentPage().resetRedrawFlag();
            getCurrentPage().redraw();
            getCurrentPage().update(true);
        }
        else
        {
            getCurrentPage().update();
        }
    }

    DISPLAY_UPDATE_CODE
}
