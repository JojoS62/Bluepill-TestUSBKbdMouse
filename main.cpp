/*
 MIT License

Copyright (c) 2020 JojoS

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*
 */

#include "mbed.h"
#include "Encoder.h"
#include "USBMouseKeyboard.h"

// threshold settings for x/y switch at analog in
#define ThreshMax   (40+20)
#define ThreshMin   (40-20)

DigitalOut  led(PC_13);                         // onboard LED
Encoder     encoder1(PB_7, PB_8, PB_9);         // phaseA, phaseB, pushButon pins
AnalogIn    xRaw(A0);                           // grayhill encoder has analog 0 - 2.5V - 5 V outputs for direction
AnalogIn    yRaw(A1);                           //   connected via 47k - 47k voltage divider for max. 2.5 V at analog in 
InterruptIn intBtnMute(PB_6);                   // another pushbutton, showing interrupt usage
bool        flagMute;                           // USB function must not be called in ISR, use simple flag

// this is the USB class with default arguments, but individual PID/VID could be supplied also
USBMouseKeyboard hid;

void toggleMute() 
{
    flagMute = true;
}

int main() {
    intBtnMute.mode(PullUp);        // enable PullUp for interrupt pin
    intBtnMute.fall(toggleMute);    // attach callback function to interrupt

    while (true) {
        bool btnPressed = false;
        bool btnReleased = false;
        int delta = 0;
        
        encoder1.read(delta, btnPressed, btnReleased);      // get encoder state

        if (btnPressed) {
            led = !led;                                     // toggle LED, LED is also used as status
        }   

        if (delta > 0) {
            if (led)                                        // function depends on status
                hid.mediaControl(KEY_VOLUME_UP);
            else
                hid.move(+5, 0);
        }

        if (delta < 0) {
            if (led)
                hid.mediaControl(KEY_VOLUME_DOWN);
            else
                hid.move(-5, 0);
        }

        // check mute flag from interrupt in
        if (flagMute) {
            hid.mediaControl(KEY_MUTE);     // toggle muting
            wait_ms(10);                    // short debouncing delay
            flagMute = false;
        }

        // use direction switch for relative mouse movement
        // left/right, up/down is analog input. 
        int x = xRaw * 100.0f;                              // read ADCs, convert to integer percent
        int y = yRaw * 100.0f;
        
        if (x < ThreshMin) {                                // move mouse cursor
            hid.move(-5, 0);
        } else 
        if (x > ThreshMax) {
            hid.move(+5, 0);
        }

        if (y < ThreshMin) {
            hid.move(0, -5);
        } else 
        if (y > ThreshMax)
        {
            hid.move(0, +5);
        }

        wait_ms(10);
    }
}
