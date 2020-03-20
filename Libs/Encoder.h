#ifndef __Encoder_h__
#define __Encoder_h__

#include "mbed.h"

class Encoder {
public:
    Encoder(PinName pinA, PinName pinB, PinName pinBtnPush);

    void read(int &delta, bool &btnPressed, bool &btnReleased);

private:
    void process();

    DigitalIn   _encInA;
    DigitalIn   _encInB;
    DigitalIn   _btnPush;
    int         _btnPushOld;
    int         _encDelta;
    int         _encLast;
    bool        _btnPressed;
    bool        _btnReleased;
};

#endif