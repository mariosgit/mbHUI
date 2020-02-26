template<class GFX> mbDisplay<GFX>* mbDisplay<GFX>::_the = nullptr;

template<class GFX>
mbDisplay<GFX>::mbDisplay() :
    DISPLAY_CONSTRUCTOR_CALL,  // defined in mbConfig.h
    _blanked(false)
{
    for(uint8_t i = 0; i < MB_MAX_PAGES; i++)
        _pages[i] = nullptr;
    _the = this;
}

template<class GFX>
void mbDisplay<GFX>::begin()
{
    DISPLAY_BEGIN_CODE  // defined in mbConfig.h
    get().begin();
    // get().setFont(DISP_FONT1x);
    // get().setFontRefHeightExtendedText();
    // get().setFontMode(0); // 0-withBG, 1-noBG
    // get().setDrawColor(1); // 0-black, 1-white
    get().setTextColor(1, 0); // fore back
    // get().setFontPosTop();
    // get().setFontDirection(0);

    changeCurrentPage(_currentPage.get());
}

template<class GFX>
void mbDisplay<GFX>::restore()
{
    // range fix after restore
    if(_the->_currentPage.get() < 0)
        _the->_currentPage.get() = _the->_pagePtr - 1;
    _the->_currentPage.get() = _the->_currentPage.get() % _the->_pagePtr;

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
void mbDisplay<GFX>::changeCurrentPage(int8_t val)
{
    if( _the->_pages[_the->_currentPage.get()] )
        _the->_pages[_the->_currentPage.get()]->setActive(false);
    _the->_currentPage.get() = (_the->_currentPage.get() + val);
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    if(_the->_currentPage.get() < 0)
        _the->_currentPage.get() = _the->_pagePtr - 1;
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    _the->_currentPage.get() = _the->_currentPage.get() % _the->_pagePtr;
    // Log.warning("mbDisplay::changeCurrentPage %d\n", _the->_currentPage);
    if( _the->_pages[_the->_currentPage.get()] )
    {
        Log.warning("mbDisplay::changeCurrentPage #%d p:%p\n",
            _the->_currentPage.get(), _the->_pages[_the->_currentPage.get()]);
        _the->_pages[_the->_currentPage.get()]->setActive(true);
        _the->_pages[_the->_currentPage.get()]->setRedrawFlag();
        _the->unblank();
    }
    else
    {
        Log.warning("mbDisplay::changeCurrentPage #%d p:nullPtr\n", _the->_currentPage.get());
    }
}

template<class GFX>
void mbDisplay<GFX>::changeActiveParam(int8_t val)
{
    if( _the->_pages[_the->_currentPage.get()] )
        _the->_pages[_the->_currentPage.get()]->changeActiveParam(val);
}

template<class GFX>
void mbDisplay<GFX>::addPage(PageType *page)
{
    _the->_pages[_the->_pagePtr++] = page;
    if(_pagePtr >= MB_MAX_PAGES)
    {
        Log.error(F("Pages FULL\n"));
    }
}


template<class GFX>
mbDisplay<GFX>* mbDisplay<GFX>::the()
{
    if(!_the)
        _the = new mbDisplay;
    return _the;
}

template<class GFX>
void mbDisplay<GFX>::blank()
{
    Log.notice(F("**************** blank *****************\n"));
    get().clearDisplay();
    get().display();
    _blanked = true;
}

template<class GFX>
void mbDisplay<GFX>::unblank()
{
    if(!_blanked)
        return;
    Log.notice(F("**************** unblank ***************\n"));
    restore();
    get().display();
    _blanked = false;
}

template<class GFX>
void mbDisplay<GFX>::update()
{
    if(getPage().getRedrawFlag())
    {
        getPage().resetRedrawFlag();
        getPage().redraw();
        getPage().update(true);
    }
    else
    {
        getPage().update();
    }

    get().display();
}
