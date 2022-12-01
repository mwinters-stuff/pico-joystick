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
 */

#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

enum
{
  EMPTY_REPORT_ID = 0,
  // REPORT_ID_KEYBOARD = 1,
  // REPORT_ID_MOUSE,
  // REPORT_ID_CONSUMER_CONTROL,
  REPORT_ID_JOYSTICK_LEFT,
  REPORT_ID_JOYSTICK_RIGHT,
  // REPORT_ID_GAMEPAD = 1,
  REPORT_ID_COUNT,
  START_REPORT_ID = REPORT_ID_JOYSTICK_LEFT,
};

/// HID Gamepad Protocol Report.
typedef struct TU_ATTR_PACKED
{
  uint8_t  x;         ///< Delta x  movement of left analog-stick
  uint8_t  y;         ///< Delta y  movement of left analog-stick
  // int8_t  z;         ///< Delta z  movement of right analog-joystick
  // int8_t  rz;        ///< Delta Rz movement of right analog-joystick
  uint8_t  rx;        ///< Delta Rx movement of analog left trigger
  uint8_t  ry;        ///< Delta Ry movement of analog right trigger
  uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
  uint32_t buttons;  ///< Buttons mask for currently pressed buttons
}hid_gamepad_custom_report_t;

struct buttonBits{ 
      uint8_t trigger:1;
      uint8_t thumb  :1;
      uint8_t button2  :1;
      uint8_t button3  :1;
      uint8_t button4  :1;
      uint8_t button5  :1;
      uint8_t button6  :1;
      uint8_t button7  :1;
    } ;

;

typedef struct TU_ATTR_PACKED {
    uint8_t xAxis1;
    uint8_t yAxis1;
    union {
      struct buttonBits bits;
      uint8_t byte;
    } buttons;
} HID_JoystickReport_Data_t;


#define TUD_HID_REPORT_DESC_GAMEPAD_CUSTOM(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_GAMEPAD  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
    /* 8 bit X, Y, Z, Rz, Rx, Ry (min 0, max 255 ) */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ) ,\
    /* HID_USAGE        ( HID_USAGE_DESKTOP_Z                    ) , \
       HID_USAGE        ( HID_USAGE_DESKTOP_RZ                   ) ,*/\ 
    HID_USAGE        ( HID_USAGE_DESKTOP_RX                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RY                   ) ,\
    HID_LOGICAL_MIN  ( 0x00                                   ) ,\
    HID_LOGICAL_MAX  ( 0xff                                   ) ,\
    HID_REPORT_COUNT ( 4                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 8 bit DPad/Hat Button Map  */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_HAT_SWITCH           ) ,\
    HID_LOGICAL_MIN  ( 1                                      ) ,\
    HID_LOGICAL_MAX  ( 8                                      ) ,\
    HID_PHYSICAL_MIN ( 0                                      ) ,\
    HID_PHYSICAL_MAX_N ( 315, 2                               ) ,\
    HID_REPORT_COUNT ( 1                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 16 bit Button Map */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_BUTTON                  ) ,\
    HID_USAGE_MIN    ( 1                                      ) ,\
    HID_USAGE_MAX    ( 32                                     ) ,\
    HID_LOGICAL_MIN  ( 0                                      ) ,\
    HID_LOGICAL_MAX  ( 1                                      ) ,\
    HID_REPORT_COUNT ( 32                                     ) ,\
    HID_REPORT_SIZE  ( 1                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \


#define TUD_HID_REPORT_DESC_JOYSTICK_LEFT(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_JOYSTICK  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
  HID_USAGE        ( 0x01                       ),\
  HID_COLLECTION   ( HID_COLLECTION_PHYSICAL ),\
    HID_USAGE      (HID_USAGE_DESKTOP_X),\
    HID_USAGE      (HID_USAGE_DESKTOP_Y),\
    HID_LOGICAL_MIN    (0                                 ) ,\
    HID_LOGICAL_MAX  (0xff                          ) ,\
    HID_REPORT_SIZE  ( 8                                    ) ,\
    HID_REPORT_COUNT ( 2                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE |HID_WRAP_NO | HID_LINEAR |HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_BITFIELD) ,\
  HID_COLLECTION_END, \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_BUTTON     )                 ,\
  HID_USAGE_MIN    ( 1                                      ) ,\
  HID_USAGE_MAX    ( 8                                      ) ,\
  HID_LOGICAL_MIN  ( 0                                      ) ,\
  HID_LOGICAL_MAX  ( 1                                      ) ,\
  HID_REPORT_SIZE  ( 1                                     ) ,\
  HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE |HID_WRAP_NO | HID_LINEAR |HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_BITFIELD) ,\
  HID_COLLECTION_END \

#define TUD_HID_REPORT_DESC_JOYSTICK_RIGHT(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_MULTI_AXIS_CONTROLLER  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
  HID_USAGE        ( 0x01                       ),\
  HID_COLLECTION   ( HID_COLLECTION_PHYSICAL ),\
    HID_USAGE      (HID_USAGE_DESKTOP_X),\
    HID_USAGE      (HID_USAGE_DESKTOP_Y),\
    HID_LOGICAL_MIN    (0                                 ) ,\
    HID_LOGICAL_MAX  (0xff                          ) ,\
    HID_REPORT_SIZE  ( 8                                    ) ,\
    HID_REPORT_COUNT ( 2                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE |HID_WRAP_NO | HID_LINEAR |HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_BITFIELD) ,\
  HID_COLLECTION_END, \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_BUTTON     )                 ,\
  HID_USAGE_MIN    ( 1                                      ) ,\
  HID_USAGE_MAX    ( 8                                      ) ,\
  HID_LOGICAL_MIN  ( 0                                      ) ,\
  HID_LOGICAL_MAX  ( 1                                      ) ,\
  HID_REPORT_SIZE  ( 1                                     ) ,\
  HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE |HID_WRAP_NO | HID_LINEAR |HID_PREFERRED_STATE | HID_NO_NULL_POSITION | HID_BITFIELD) ,\
  HID_COLLECTION_END \


#endif /* USB_DESCRIPTORS_H_ */