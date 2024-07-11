#include <stdio.h>
#include "pico/stdlib.h"
#include <string>
#include "tusb.h"


// Interface index depends on the order in configuration descriptor
enum {
  ITF_KEYBOARD = 0,
  ITF_MOUSE = 1
};

int getUSBKeyCodeModifier(char letter) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+{}|:\"~<>?";

    size_t location = alphabet.find(letter);
    if (location != std::string::npos) {
      return 0xe1; // left shift key code
    }

    return 0; // no modifier
}

int getUSBKeyCode(char letter) {
    std::string alphabet1 = "abcdefghijklmnopqrstuvwxyz1234567890\naaa -=[]\\a;'`,./";
    std::string alphabet2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()\naaa _+{}|a:\"~<>?";

    size_t location = alphabet1.find(letter);
    if (location != std::string::npos) {
      return location + 4;
    }
    location = alphabet2.find(letter);
    if (location != std::string::npos) {
      return location + 4;
    }

    return -1; // if a character is not found
}


void send_keystroke(uint key1, uint modifier) {
    uint8_t keycode[6] = { 0 };
    keycode[0] = modifier;
    keycode[1] = key1;
    tud_hid_n_keyboard_report(ITF_KEYBOARD, 0, 0, keycode);
    sleep_ms(10);
    tud_task();
}


void send_keystroke_NULL() {
    // while ( !tud_hid_n_ready(ITF_KEYBOARD) ) {
    //     gpio_put(16, 1);
    // }
    // gpio_put(16, 0);
    tud_hid_n_keyboard_report(ITF_KEYBOARD, 0, 0, NULL);
    sleep_ms(10);
    tud_task();
}


int main(void) {
    stdio_init_all();
    tusb_init();

    const uint LED_PIN = 15;
    const uint LED_ERROR_PIN = 16;
    const uint BUTTIN_PIN = 14;
    gpio_init(LED_PIN);
    gpio_init(BUTTIN_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTIN_PIN, GPIO_IN);
    gpio_pull_up(BUTTIN_PIN);

    bool buttonPressed = false;

    std::string command = "https://www.youtube.com/watch?v=dQw4w9WgXcQ/\n";

    while (1)
    {
        tud_task();

        if ( gpio_get(BUTTIN_PIN) == 0 ) {
          buttonPressed = true;
        } else {
          buttonPressed = false;
        }

        if ( tud_hid_n_ready(ITF_KEYBOARD) && buttonPressed ) {
            for (int i = 0; i < command.length(); i++) {
                gpio_put(LED_PIN, 1);
                int code = getUSBKeyCode(command[i]);
                if (code == -1) { continue; }
                send_keystroke(code, getUSBKeyCodeModifier(command[i]));
                gpio_put(LED_PIN, 0);
                send_keystroke_NULL();
            }

            while ( gpio_get(BUTTIN_PIN) == 0 );
        } else if (tud_hid_n_ready(ITF_KEYBOARD) && !buttonPressed ) {
            send_keystroke_NULL();
        }
    }

    return 0;
}

  /*------------- Mouse -------------*/
//   if ( tud_hid_n_ready(ITF_MOUSE) )
//   {
//     if ( btn )
//     {
//       int8_t const delta = 5;

//       // no button, right + down, no scroll pan
//       tud_hid_n_mouse_report(ITF_MOUSE, 0, 0x00, delta, delta, 0, 0);
//     }
//   }


// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // TODO set LED based on CAPLOCK, NUMLOCK etc...
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) bufsize;
}