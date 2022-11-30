/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "bsp/board.h"

#include "pico/stdlib.h"
#include "tusb.h"
#include "usb_descriptors.h"

#include "hardware.h"

void hid_task(void);

Hardware hardware;

void serial_print(const char* str);
bool serialReady = false;

/*------------- MAIN -------------*/
int main(void) {
  stdio_init_all();

  serial_print("Init\n");

  hardware.begin();
  hardware.led_blink_fast();

  board_init();
  tusb_init();
  while (true) {
    tud_task();  // tinyusb device task
    hardware.update();
    hid_task();
    serial_print(("\r" + hardware.debug()).c_str());

  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
  hardware.led_blink_slow();
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
  hardware.led_blink_fast();
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
  (void)remote_wakeup_en;
  hardware.led_blink_slower();
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
  hardware.led_blink_slow();
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id) {
  // skip if hid is not ready yet
  if (!tud_hid_ready()) return;

  switch (report_id) {
    case REPORT_ID_KEYBOARD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_keyboard_key = false;

      if ( hardware.button_down(baMiddleMiddle) )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    break;
    // case REPORT_ID_JOYSTICK_LEFT: {
    //   static HID_JoystickReport_Data_t report = {0, 0, 0};

    //   report.xAxis1 = hardware.stick_left_x();
    //   report.yAxis1 = hardware.stick_left_y();

    //   report.buttons.bits.trigger = hardware.button_down(baBottomLeft) ? 1 : 0;
    //   report.buttons.bits.thumb = hardware.stick_left_button_down();
    //   tud_hid_report(REPORT_ID_JOYSTICK_LEFT, &report, sizeof(report));
    //   // button = (button + 1) & 0x07; // limit button to the range 0..7

    // } 
    // break;
    // case REPORT_ID_JOYSTICK_RIGHT: {
    //   static HID_JoystickReport_Data_t report = {0, 0, 0};

    //   report.xAxis1 = hardware.stick_right_x();
    //   report.yAxis1 = hardware.stick_right_y();

    //   report.buttons.bits.trigger = hardware.button_down(baBottomRight) ? 1 : 0;
    //   report.buttons.bits.thumb = hardware.stick_right_button_down();
    //   tud_hid_report(REPORT_ID_JOYSTICK_RIGHT, &report, sizeof(report));
    //   // button = (button + 1) & 0x07; // limit button to the range 0..7

    // } 
    // break;
    case REPORT_ID_GAMEPAD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_gamepad_key = false;

      hid_gamepad_report_t report =
      {
        .x   = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 0
      };

      report.x = hardware.stick_left_x();
      report.y = hardware.stick_left_y();
      report.rx = hardware.stick_right_x();
      report.ry = hardware.stick_right_y();

      if(hardware.stick_left_button_down())
      {
        report.buttons = GAMEPAD_BUTTON_TR;
      }

      if(hardware.stick_right_button_down())
      {
        report.buttons |= GAMEPAD_BUTTON_TR;
      }


      report.hat = GAMEPAD_HAT_CENTERED;
      switch(hardware.last_button_down()){
        case baTopLeft:
          report.hat = GAMEPAD_HAT_UP_LEFT;
        break;
        case baTopMiddle:
          report.hat = GAMEPAD_HAT_UP;
        break;
        case baTopRight:
          report.hat = GAMEPAD_HAT_UP_RIGHT;
        break;
        case baMiddleLeft:
          report.hat = GAMEPAD_HAT_LEFT;
        break;
        case baMiddleMiddle:
        break;
        case baMiddleRight:
          report.hat = GAMEPAD_HAT_RIGHT;
        break;
        case baBottomLeft:
          report.hat = GAMEPAD_HAT_DOWN_LEFT;
        break;
        case baBottomMiddle:
          report.hat = GAMEPAD_HAT_DOWN;
        break;
        case baBottomRight:
          report.hat = GAMEPAD_HAT_DOWN_RIGHT;
        break;

      }
      tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
    }
    break;    
    default:
      break;
  }
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void) {
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if (board_millis() - start_ms < interval_ms) return;  // not enough time
  start_ms += interval_ms;

  // Remote wakeup
  if (tud_suspended() && hardware.button_down(baBottomMiddle)) {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  } else {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len) {
  (void)instance;
  (void)len;
  uint8_t next_report_id = report[0] + 1;
  printf("tud_hid_report_complete_cb %d\n",next_report_id);

  if (next_report_id < REPORT_ID_COUNT) {
    send_hid_report(next_report_id);
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
  // TODO not Implemented
  (void)instance;
  (void)report_id;
  (void)report_type;
  (void)buffer;
  (void)reqlen;
  printf("tud_hid_get_report_cb\n");

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  (void)instance;
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) 
{
  (void)itf;
  (void)rts;

  serialReady = false;
  if (dtr) {
    serialReady = true;
    tud_cdc_write_str("Connected\n");
  }
}

void serial_print(const char* str) {
  if (serialReady) {
    tud_cdc_write_str(str);
  }else{
    printf(str);
  }
}