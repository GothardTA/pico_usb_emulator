# USB Keyboard/Mouse emulator using the Raspberry Pi Pico
## How it works
This project uses the pico c/c++ sdk along with tinyusb to send preset keystrokes to a host computer over usb. Currently you can press a button hooked up to pin 14 (and ground) and it types preset characters (stored in keyboard_testing.cpp as 'std::string command'). An led hooked up to pin 15 indicates key presses are being sent.


## How to build and run
### VS Code
First clone or download this repo. Open VS Code to this directory. Use the raspberry pi pico extension, go over to its extension tab (pico board icon), click compile project.

### Linux
First clone or download this repo and open a terminal in this directory. Then run the command listed below:<br>
`$ mkdir build`   - creates directory for build files<br>
`$ cd build`      - changes your directory within your terminal<br>
`$ cmake ..`      - configures project for next command<br>
`$ make -j8`      - change the `8` to however many cpu threads you want to use to compile the project

### Mac OS
Try to use the vscode extension or look at the [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) section 9.1. I think if you have the required utils to build the pico sdk then you can use the linux commands.

### Windows
Try to use the vscode extension or look at the [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) section 9.2

### How to run
Hold the BOOTSEL button on the pico while plugging it into your computer. You should see a new removable drive pop up. Go into the build directory and copy the `keyboard_testing.uf2` to the pico (the new remavable drive). The pico will reboot and run the program as soon as its copied. You can press the button to send the keystrokes, you can also brisge pin 14 and ground to do the same.


## Why did I do this?
I decided to do this project because I recently bought a Raspberry Pi Pico W and found out it can emulate usb devices so I wanted to try that out. Little did I realize that there is very little documentation on tinyusb and there examples were not clear. Through a lot of research and help I was able to take the tinyusb example 'hid_composite' and make it send certain keystrokes. I wanted to upload this so that I can use it for future reference and so that if anyone else wants to do this they can use this project as a base.