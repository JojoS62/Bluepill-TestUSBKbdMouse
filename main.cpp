#include "mbed.h"
#include "Encoder.h"
#include "USBMouseKeyboard.h"

#define ThreshMax   (40+20)
#define ThreshMin   (40-20)

DigitalOut  led(PC_13);
Encoder     encoder1(PB_7, PB_8, PB_9);
AnalogIn    xRaw(A0);
AnalogIn    yRaw(A1);

USBMouseKeyboard hid;

int main() {
    while (true) {
        bool btnPressed = false;
        bool btnReleased = false;
        int delta = 0;
        
        encoder1.read(delta, btnPressed, btnReleased);     

        if (btnPressed) {
            led = !led;
            //hid.mediaControl(KEY_MUTE);
        }   

        if (delta > 0) {
            if (led)
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

        int x = xRaw * 100.0f;
        int y = yRaw * 100.0f;
        
        if (x < ThreshMin) {
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
