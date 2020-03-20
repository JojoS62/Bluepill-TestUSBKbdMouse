#include "mbed.h"
#include "Encoder.h"
#include "USBMouseKeyboard.h"

DigitalOut led(PC_13);
Encoder encoder1(PB_7, PB_8, PB_9);

USBMouseKeyboard hid;

int main() {
    while (true) {
        bool btnPressed = false;
        bool btnReleased = false;
        int delta = 0;
        
        encoder1.read(delta, btnPressed, btnReleased);     

        if (btnPressed) {
            led = 0;
            hid.mediaControl(KEY_MUTE);
            wait_ms(100);
            led = 1;
        }   

        if (delta > 0)
            hid.mediaControl(KEY_VOLUME_UP);

        if (delta < 0)
            hid.mediaControl(KEY_VOLUME_DOWN);

        wait_ms(10);
    }
}
