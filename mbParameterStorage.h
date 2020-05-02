#pragma once

#include <Arduino.h>
#include <mbLog.h>

class mbParameterBase
{
public:
    mbParameterBase();
    virtual size_t        getSize() = 0;
    virtual void*         getPtr() = 0;
    virtual int16_t       getI() { return 0; }
    virtual int16_t       getMapped() { return 0; }
    virtual const char*   getString() { return nullptr; }
    virtual void          trigger() {}
    virtual void          add(int16_t val) {};
    virtual void          set(int16_t val) {};

    virtual const int16_t x()  { return 0; }
    virtual const int16_t y()  { return 0; }
    virtual const int16_t height() { return 0; }
    virtual const int16_t width()  { return 0;  }
    virtual const char*   name()   { return ""; }

    inline bool getAndClearChanged() { bool result = _changed; _changed = false; return result; }
protected:
    bool _changed = false;
};

template<class ParameterType>
class mbParameter : public mbParameterBase
{
public:
    mbParameter();
    mbParameter& operator=(const ParameterType &val);
    inline ParameterType& get() { return _param; }
    inline int16_t getI() { return _param; }

    inline size_t getSize() override { return sizeof(_param); }
    inline void*  getPtr()  override { return &_param; }

protected:
    ParameterType _param;
};

/* displayMapper classes can change a displayed value from internal uint_8 range
 to some int16_t range.
 E.g. Used to display gain values in dB */
template<int16_t scaleUp, int16_t scaleDown, int16_t offset>
class displayMapper {
    public:
    int16_t operator()(int16_t value) {
        return value*scaleUp/scaleDown+offset;
    }
};
typedef displayMapper<1,1,0> identityMapper;

/* Trigger classes are called when a parameter changes, implement the action here
   and pass the Trigger class as template Param to mbParameterRB */
class NoTrigger
{
public:
    void operator()(uint8_t value) {}
};

class displayToNullString {
public:
    const char* operator()(int16_t value) { return nullptr; }
};

/** mbParameterRB (Range+Box) implements a typical midi range value. It can be
   added to a page (todo: and set to a midi CC message) */
template<int16_t BoxX, int16_t BoxY, int16_t BoxWidth, int16_t BoxHeight,
         class displayMapperType=identityMapper, class TriggerType=NoTrigger, class ToStringType=displayToNullString>
class mbParameterRB : public mbParameter<uint8_t>
{
    typedef uint8_t ParameterType;
public:
    /// @params name, min, max
    mbParameterRB(const char* name, ParameterType minval, ParameterType maxval) :
        mbParameter<ParameterType>(),
        _name(name),
        _minVal(minval),
        _maxVal(maxval)
    {}
    inline void add(int16_t val) override
    {
        // LOG <<"add " <<(-val + mbParameter<ParameterType>::_param) <<"\n";
        if(val + mbParameter<ParameterType>::_param < _minVal)
            mbParameter<ParameterType>::_param = _minVal;
        else if(val + mbParameter<ParameterType>::_param > _maxVal)
            mbParameter<ParameterType>::_param = _maxVal;
        else
            mbParameter<ParameterType>::_param += val;
        _changed = true;
    }
    inline void set(int16_t val) override
    {
        mbParameter<ParameterType>::_param = val;
        if( mbParameter<ParameterType>::_param <= _minVal)
            mbParameter<ParameterType>::_param = _minVal;
        if( mbParameter<ParameterType>::_param >= _maxVal)
            mbParameter<ParameterType>::_param = _maxVal;
        _changed = true;
    }

    inline const int16_t x()      { return BoxX; }
    inline const int16_t y()      { return BoxY; }
    inline const int16_t height() { return BoxHeight; }
    inline const int16_t width()  { return BoxWidth;  }
    inline const char*   name()   { return _name; }

    inline int16_t getMapped() override { displayMapperType dm; return dm(getI()); }
    ToStringType ts;
    inline const char* getString() override { return ts(getI()); }

    inline void trigger() override { TriggerType tt; tt(_param); }

private:
    const char* _name;
    ParameterType _minVal;
    ParameterType _maxVal;
};



/***************************************************/

class mbStorage
{
    friend class mbParameterBase;
public:
    mbStorage();
    static mbStorage* the();
    void dump();
    void store();
    void restore();
private:
    void add(mbParameterBase *param);

    mbParameterBase* _store[64];
    int _storePtr  = 0;
    int _storeSize = 0;
    uint16_t _baseAdr = 4;

    static mbStorage *_the;
};

/****************************************************
 * Implementation of Templates
 ****************************************************/

template<class ParameterType>
mbParameter<ParameterType>::mbParameter() :
    mbParameterBase()
{

}

template<class ParameterType>
mbParameter<ParameterType>& mbParameter<ParameterType>::operator=(const ParameterType &val)
{
    _param = val;
    return *this;
}
