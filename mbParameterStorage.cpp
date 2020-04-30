#include <mbLog.h>
#include <EEPROM.h>
#include "mbParameterStorage.h"

mbParameterBase::mbParameterBase()
{
    mbStorage::the()->add(this);
}

/*******************************************/

mbStorage* mbStorage::_the = nullptr;

mbStorage::mbStorage() :
    _baseAdr(4)
{
    _the = this;

    _storeSize = sizeof(_store) / sizeof(_store[0]);

    for(int i = 0; i < _storeSize; i++)
        _store[i] = nullptr;
}

mbStorage* mbStorage::the()
{
    // first call creates the store on heap
    if(!_the)
        _the = new mbStorage;
    return _the;
}

void mbStorage::add(mbParameterBase *param)
{
    _store[_storePtr++] = param;
    if(_storePtr >= _storeSize)
    {
        LOG <<"Storage FULL\n";
    }
}

void mbStorage::dump()
{
    LOG <<"store usage " <<_storePtr <<" of " <<_storeSize <<"\n\n";
    // for(int i = 0; i < _storePtr; i++)
    //     Log.notice("\t%X\n", _store[i]);
}

void mbStorage::store()
{
    int eepos = 0;
    { // keep base addr in lowest bytes of eeprom (might move later, to prevent EE decration)
        volatile byte *ptr = (byte*)&_baseAdr;
        for(size_t s = 0; s < sizeof(_baseAdr); s++)
        {
            EEPROM.update(eepos++, *ptr++);
        }
    }
    // Log.notice("Wrote %d bytes to EEPROM, base:%d\n", eepos, _baseAdr);
    eepos = _baseAdr;
    for(int i = 0; i < _storePtr; i++)
    {
        volatile byte *ptr = (byte*)_store[i]->getPtr();
        for(size_t s = 0; s < _store[i]->getSize(); s++)
        {
            EEPROM.update(eepos++, *ptr++);
        }
    }
    // Log.notice("Wrote %d bytes to EEPROM, base:%d\n", eepos, _baseAdr);
}
// EEPROM.read(address)
// EEPROM.update(address, data)

void mbStorage::restore()
{
    LOG <<"mbStorage::restore\n";
    int eepos = 0;
    { // keep base addr in lowest bytes of eeprom (might move later, to prevent EE decration)
        uint16_t murks;
        volatile byte *ptr = (byte*)&murks;
        for(size_t s = 0; s < sizeof(murks); s++)
        {
            *ptr++ = EEPROM.read(eepos++);
        }
        LOG <<LOG.dec <<"Read " <<eepos <<" murks from EEPROM, base:" <<murks <<"\n";
    }
    eepos = _baseAdr;
    for(int i = 0; i < _storePtr; i++)
    {
        volatile byte *ptr = (byte*)_store[i]->getPtr();
        for(size_t s = 0; s < _store[i]->getSize(); s++)
        {
            *ptr++ = EEPROM.read(eepos++);
        }
        _store[i]->add(0);    // triggers a range check
        // _store[i]->trigger(); // func triggers, do this in display.restore / page.restore !
    }
    LOG <<LOG.dec<<"Read " <<eepos <<" bytes from EEPROM, base:" <<_baseAdr <<"\n";
}
