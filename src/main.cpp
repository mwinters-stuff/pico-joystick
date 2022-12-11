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
#include "hardware/watchdog.h"
#include "hardware.h"

void hid_task(void);


void serial_print(const char* str);
bool serialReady = false;
static absolute_time_t next_task_time;
#define USB_REPORT_INTERVAL 10

SwitchesPosition switches_position;

/*------------- MAIN -------------*/
int main(void) {
  stdio_init_all();
  board_init();
  tusb_init();

  serial_print("Init\n");

  hardware.begin();
  hardware.led_blink_fast();

  next_task_time =  make_timeout_time_ms(USB_REPORT_INTERVAL);
  hardware.update();
  switches_position = hardware.switches_position();
  // configure_usb();

  watchdog_enable(100, 1);

  while (true) {
    watchdog_update();
    tud_task();  // tinyusb device task
    hardware.update();
    serial_print( hardware.debug().c_str());
    
    if(hardware.switches_position() != switches_position){
      serial_print("Switches Changed, Rebooting\n");
      sleep_ms(1000);
    }
    hid_task();

  }

  return 0;
}


void configure_usb(){

}
//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
  serial_print("tud_mount_cb\n");
  hardware.led_blink_slow();
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
  serial_print("tud_umount_cb\n");
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
    case REPORT_ID_JOYSTICK_SINGLE: {
      // printf("send_hid_report joystick left\n");
      static HID_JoystickReport_Data_t report = {0, 0, 0};

      report.xAxis1 = hardware.stick_left_x();
      report.yAxis1 = hardware.stick_left_y();

      report.buttons.bits.trigger = hardware.button_down(baBottomLeft) ? 1 : 0;
      report.buttons.bits.thumb = hardware.stick_left_button_down();
      tud_hid_report(REPORT_ID_JOYSTICK_SINGLE, &report, sizeof(report));
      // button = (button + 1) & 0x07; // limit button to the range 0..7

    } 
    break;

     case REPORT_ID_JOYSTICK_LEFT: {
      // printf("send_hid_report joystick left\n");
      static HID_JoystickReport_Data_t report = {0, 0, 0};

      report.xAxis1 = hardware.stick_left_x();
      report.yAxis1 = hardware.stick_left_y();

      report.buttons.bits.trigger = hardware.button_down(baBottomLeft) ? 1 : 0;
      report.buttons.bits.thumb = hardware.stick_left_button_down();
      tud_hid_report(REPORT_ID_JOYSTICK_LEFT, &report, sizeof(report));
      // button = (button + 1) & 0x07; // limit button to the range 0..7

    } 
    break;

    case REPORT_ID_JOYSTICK_RIGHT: {
      static HID_JoystickReport_Data_t report = {0, 0, 0};

      report.xAxis1 = hardware.stick_right_x();
      report.yAxis1 = hardware.stick_right_y();

      report.buttons.bits.trigger = hardware.button_down(baBottomRight) ? 1 : 0;
      report.buttons.bits.thumb = hardware.stick_right_button_down();
      tud_hid_report(REPORT_ID_JOYSTICK_RIGHT, &report, sizeof(report));
      // button = (button + 1) & 0x07; // limit button to the range 0..7

    } 
    break;


    case REPORT_ID_GAMEPAD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_gamepad_key = false;

      hid_gamepad_custom_report_t report =
      {
        .x   = 0, .y = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 0
      };

      report.x = hardware.stick_left_x();
      report.y = hardware.stick_left_y();
      report.rx = hardware.stick_right_x();
      report.ry = hardware.stick_right_y();

      if(hardware.stick_left_button_down())
      {
        report.buttons = GAMEPAD_BUTTON_TL;
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
          report.buttons |= GAMEPAD_BUTTON_START;
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
  if (absolute_time_diff_us(get_absolute_time(), next_task_time) > 0){
    // printf("hid_task No Time %" PRId64 " %" PRIu32 " %" PRIu32 "\n", atd, to_ms_since_boot(at), to_ms_since_boot(next_task_time));
    return;  // not enough time
  } 

  next_task_time = make_timeout_time_ms(USB_REPORT_INTERVAL);
  // printf("hid_task %" PRIu32 "\n", to_ms_since_boot(get_absolute_time()));


  // Remote wakeup
  if (tud_suspended() && hardware.button_down(baBottomMiddle)) {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  } else {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    
    switch(hardware.switches_position())
    {
      case spTopUpBottomUp:
        send_hid_report(REPORT_ID_JOYSTICK_SINGLE);
        break;
      case spTopDownBottomUp:
        send_hid_report(REPORT_ID_JOYSTICK_LEFT);
        break;
      case spTopUpBottomDown:
        send_hid_report(REPORT_ID_GAMEPAD);
        break;
    }

  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len) {
  (void)instance;
  (void)len;

  uint8_t report_id = report[0];
  switch(hardware.switches_position())
  {
    case spTopUpBottomDown:
    case spTopUpBottomUp:
      // send_hid_report(REPORT_ID_JOYSTICK_SINGLE);
      break;
    case spTopDownBottomUp:
      if(report_id == REPORT_ID_JOYSTICK_LEFT)
        send_hid_report(REPORT_ID_JOYSTICK_RIGHT);
      break;
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
  serial_print("tud_hid_get_report_cb\n");

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
    serial_print("Connected\n");
  }
}

void serial_print(const char* str) {
  if (serialReady) {
    tud_cdc_write_str(str);
  }else{
    printf(str);
  }
}