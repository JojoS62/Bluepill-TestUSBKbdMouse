# Bluepill-TestUSBKbdMouse
mbed2 project for USB with Bluepill-F103. Implements USB Keyboard and Mouse.

This is a sample project to implement an USB keyboard and mouse on a Bluepill board with STM32F103.
It uses mbed2 which makes it simple to use and to modify for custom keyboards. 

mbed2 maybe outdated as there is already mbed-os5, but for MCUs with smaller EEPROM/RAM sizes, it is still useful.
There is an USBDevice implementation for several MCUs in mbed2, but for the bluepill board, a slight modification was necessary. 

The recommended way to compile is to use the mbed-cli, refer to this installation guide:
https://os.mbed.com/docs/mbed-os/v5.15/quick-start/offline-with-mbed-cli.html

The repo contains some settings for VSCode, there are build tasks to start the compilation. The launch settings need to be adjusted to the existing debug probes.
