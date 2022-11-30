
#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

enum
{
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_GAMEPAD,
    // REPORT_ID_JOYSTICK_LEFT,
  // REPORT_ID_JOYSTICK_RIGHT,
  REPORT_ID_COUNT
};

#define ATTRIBUTE_PACKED  __attribute__((packed, aligned(1)))

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


typedef struct ATTRIBUTE_PACKED {
    uint8_t xAxis1;
    uint8_t yAxis1;
    union {
      struct buttonBits bits;
      uint8_t byte;
    } buttons;
} HID_JoystickReport_Data_t;

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



#endif /* USB_DESCRIPTORS_H_ */