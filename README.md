# USB Keyboard/Mouse emulator using the Raspberry Pi Pico
## How it works
This project uses the pico c/c++ sdk along with tinyusb to send preset keystrokes to a host computer over usb. Currently you can press a button hooked up to pin 14 (and ground) and it types preset characters (stored in keyboard_testing.cpp as 'std::string command'). An led hooked up to pin 15 indicates key presses are being sent.
<br><br>
## Why did I do this?
I decided to do this project because I recently bought a Raspberry Pi Pico W and found out it can emulate usb devices so I wanted to try that out. Little did I realize that there is very little documentation on tinyusb and there examples were not clear. Through a lot of research and help I was able to take the tinyusb example 'hid_composite' and make it send certain keystrokes. I wanted to upload this so that I can use it for future reference and so that if anyone else wants to do this they can use this project as a base.