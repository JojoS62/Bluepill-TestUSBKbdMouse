#include "Encoder.h"

Encoder::Encoder(PinName pinA, PinName pinB, PinName pinBtnPush) :
    _encInA(pinA, PullUp),
    _encInB(pinB, PullUp),
    _btnPush(pinBtnPush, PullUp)
{
    _encLast = 0;
    _encDelta = 0;
}

void Encoder::process()
{
    int i = 0;

    int btnPush = _btnPush;
    if (btnPush != _btnPushOld) {
        if (_btnPushOld) {
            _btnPressed = true;
        } else {
            _btnReleased = true;
        }
    } else {
        _btnPressed = false;
        _btnReleased = false;
    }
    _btnPushOld = btnPush;

    if (_encInB) {
        i = 1;
    }
    if (_encInA) {
        i ^= 3;                 // convert gray to binary
    }

    i -= _encLast;              // difference new - last

    if (i & 1) {                // bit 0 = value (1)
        _encLast += i;          // store new as next last
        _encDelta += (i & 2) - 1;   // bit 1 = direction (+/-)
    }
}

void Encoder::read(int &delta, bool &btnPressed, bool &btnReleased)
{
    process();
    delta = _encDelta;
    btnPressed = _btnPressed;
    btnReleased = _btnReleased;
    _encDelta = 0;
}
