# Thrustmaster

```
> sudo usbhid-dump -a3:99 -i0 -t0 | grep -v : | xxd -r -p | hidrd-convert -o spec
Usage Page (Desktop),                           ; Generic desktop controls (01h)
Usage (Joystick),                               ; Joystick (04h, application collection)
Collection (Application),
    Usage Page (Button),                        ; Button (09h)
    Usage Minimum (01h),
    Usage Maximum (10h),
    Logical Minimum (0),
    Logical Maximum (1),
    Physical Minimum (0),
    Physical Maximum (1),
    Report Size (1),
    Report Count (16),
    Input (Variable),
    Usage Page (Desktop),                       ; Generic desktop controls (01h)
    Usage (Hat Switch),                         ; Hat switch (39h, dynamic value)
    Logical Minimum (0),
    Logical Maximum (7),
    Physical Minimum (0),
    Physical Maximum (315),
    Unit (Degrees),
    Report Size (4),
    Report Count (1),
    Input (Variable, Null State),
    Input (Constant),
    Usage Page (Desktop),                       ; Generic desktop controls (01h)
    Usage (X),                                  ; X (30h, dynamic value)
    Logical Minimum (0),
    Logical Maximum (16383),
    Physical Minimum (0),
    Physical Maximum (16383),
    Unit,
    Report Size (14),
    Report Count (1),
    Input (Variable),
    Report Size (2),
    Input (Constant),
    Usage (Y),                                  ; Y (31h, dynamic value)
    Report Size (14),
    Input (Variable),
    Report Size (2),
    Input (Constant),
    Usage (Rz),                                 ; Rz (35h, dynamic value)
    Usage (Slider),                             ; Slider (36h, dynamic value)
    Logical Minimum (0),
    Logical Maximum (255),
    Physical Minimum (0),
    Physical Maximum (255),
    Unit,
    Report Size (8),
    Report Count (2),
    Input (Variable),
    Usage Page (FF00h),                         ; FF00h, vendor-defined
    Logical Maximum (65535),
    Usage (01h),
    Report Size (8),
    Report Count (4),
    Feature (Variable, No Preferred, Volatile),
End Collection
```

# CAT Stick.
mwinters@mwinters-nz-ll:~/src/hidrd$ sudo usbhid-dump -a3:101 -i0 -t0 | grep -v : | xxd -r -p | hidrd-convert -o spec
```
Usage Page (Desktop),       ; Generic desktop controls (01h)
Usage (Joystick),           ; Joystick (04h, application collection)
Collection (Application),
    Report ID (12),
    Usage (X),              ; X (30h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage (Y),              ; Y (31h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage Page (Button),    ; Button (09h)
    Usage Minimum (01h),
    Usage Maximum (08h),
    Logical Minimum (0),
    Logical Maximum (1),
    Report Size (1),
    Report Count (8),
    Input (Variable),
End Collection,
Usage Page (Desktop),       ; Generic desktop controls (01h)
Usage (Joystick),           ; Joystick (04h, application collection)
Collection (Application),
    Report ID (13),
    Usage (X),              ; X (30h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage (Y),              ; Y (31h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage (Z),              ; Z (32h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage (Slider),         ; Slider (36h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage (Slider),         ; Slider (36h, dynamic value)
    Logical Minimum (1),
    Logical Maximum (2047),
    Report Size (11),
    Report Count (1),
    Input (Variable),
    Logical Minimum (0),
    Logical Maximum (31),
    Report Size (5),
    Report Count (1),
    Input (Constant),
    Usage Page (Button),    ; Button (09h)
    Usage Minimum (01h),
    Usage Maximum (10h),
    Logical Minimum (0),
    Logical Maximum (1),
    Report Size (1),
    Report Count (16),
    Input (Variable),
End Collection,
Usage Page (FF00h),         ; FF00h, vendor-defined
Usage (01h),
Collection (Application),
    Report ID (8),
    Logical Minimum (0),
    Logical Maximum (255),
    Report Size (8),
    Report Count (7),
    Usage (01h),
    Output (Variable),
    Usage (01h),
    Report Count (7),
    Input (Variable),
End Collection,
Usage Page (FF00h),         ; FF00h, vendor-defined
Usage (01h),
Collection (Application),
    Report ID (4),
    Logical Minimum (0),
    Logical Maximum (255),
    Report Size (8),
    Report Count (63),
    Usage (01h),
    Output (Variable),
    Usage (01h),
    Report Count (63),
    Input (Variable),
End Collection
```

# Logitech F310 - Direct Input Mode
```
athew@gonzalas:~$ sudo usbhid-dump -a3:11 -i0 -t0 | grep -v : | xxd -r -p | hidrd-convert -o spec
Usage Page (Desktop),                   ; Generic desktop controls (01h)
Usage (Joystick),                       ; Joystick (04h, application collection)
Collection (Application),
    Collection (Logical),
        Report Size (8),
        Report Count (4),
        Logical Minimum (0),
        Logical Maximum (255),
        Physical Minimum (0),
        Physical Maximum (255),
        Usage (X),                      ; X (30h, dynamic value)
        Usage (Y),                      ; Y (31h, dynamic value)
        Usage (Z),                      ; Z (32h, dynamic value)
        Usage (Rz),                     ; Rz (35h, dynamic value)
        Input (Variable),
        Report Size (4),
        Report Count (1),
        Logical Maximum (7),
        Physical Maximum (315),
        Unit (Degrees),
        Usage (Hat Switch),             ; Hat switch (39h, dynamic value)
        Input (Variable, Null State),
        Unit,
        Report Size (1),
        Report Count (12),
        Logical Maximum (1),
        Physical Maximum (1),
        Usage Page (Button),            ; Button (09h)
        Usage Minimum (01h),
        Usage Maximum (0Ch),
        Input (Variable),
        Usage Page (FF00h),             ; FF00h, vendor-defined
        Report Size (1),
        Report Count (16),
        Logical Maximum (1),
        Physical Maximum (1),
        Usage (01h),
        Input (Variable),
    End Collection,
    Collection (Logical),
        Report Size (8),
        Report Count (7),
        Physical Maximum (255),
        Logical Maximum (255),
        Usage (02h),
        Output (Variable),
    End Collection,
```

# ASUS Nexus Player Gamepad.
```
0x0A, 0xDE, 0x0A,  // Usage (0x0ADE)
0xAE, 0x0A, 0x0A,  // Unknown (bTag: 0x0A, bType: 0x03)
0x00,              // Unknown (bTag: 0x00, bType: 0x00)
0x1A, 0x7D, 0xDA,  // Usage Minimum (0xDA7D)
0x71, 0x11,        // Unknown (bTag: 0x07, bType: 0x00)
0x0A, 0x0F, 0xBE,  // Usage (0xBE0F)
0x05, 0xBE,        // Usage Page (Reserved 0xBE)
0xED, 0xDC,        // Unknown (bTag: 0x0E, bType: 0x03)
0x0E, 0x0E, 0x0E,  // Unknown (bTag: 0x00, bType: 0x03)
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)
0xA1, 0x01,        // Collection (Application)
0x85, 0x01,        //   Report ID (1)
0x05, 0x09,        //   Usage Page (Button)
0x0A, 0x01, 0x00,  //   Usage (0x01)
0x0A, 0x02, 0x00,  //   Usage (0x02)
0x0A, 0x04, 0x00,  //   Usage (0x04)
0x0A, 0x05, 0x00,  //   Usage (0x05)
0x0A, 0x07, 0x00,  //   Usage (0x07)
0x0A, 0x08, 0x00,  //   Usage (0x08)
0x0A, 0x0E, 0x00,  //   Usage (0x0E)
0x0A, 0x0F, 0x00,  //   Usage (0x0F)
0x0A, 0x0D, 0x00,  //   Usage (0x0D)
0x05, 0x0C,        //   Usage Page (Consumer)
0x0A, 0x24, 0x02,  //   Usage (AC Back)
0x0A, 0x23, 0x02,  //   Usage (AC Home)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x0B,        //   Report Count (11)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x75, 0x01,        //   Report Size (1)
0x95, 0x01,        //   Report Count (1)
0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
0x75, 0x04,        //   Report Size (4)
0x95, 0x01,        //   Report Count (1)
0x25, 0x07,        //   Logical Maximum (7)
0x46, 0x3B, 0x01,  //   Physical Maximum (315)
0x66, 0x14, 0x00,  //   Unit (System: English Rotation, Length: Centimeter)
0x09, 0x39,        //   Usage (Hat switch)
0x81, 0x42,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
0x66, 0x00, 0x00,  //   Unit (None)
0xA1, 0x00,        //   Collection (Physical)
0x09, 0x30,        //     Usage (X)
0x09, 0x31,        //     Usage (Y)
0x09, 0x32,        //     Usage (Z)
0x09, 0x35,        //     Usage (Rz)
0x05, 0x02,        //     Usage Page (Sim Ctrls)
0x09, 0xC5,        //     Usage (Brake)
0x09, 0xC4,        //     Usage (Accelerator)
0x15, 0x00,        //     Logical Minimum (0)
0x26, 0xFF, 0x00,  //     Logical Maximum (255)
0x35, 0x00,        //     Physical Minimum (0)
0x46, 0xFF, 0x00,  //     Physical Maximum (255)
0x75, 0x08,        //     Report Size (8)
0x95, 0x06,        //     Report Count (6)
0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0xC0,              //   End Collection
0x85, 0x02,        //   Report ID (2)
0x05, 0x08,        //   Usage Page (LEDs)
0x0A, 0x01, 0x00,  //   Usage (Num Lock)
0x0A, 0x02, 0x00,  //   Usage (Caps Lock)
0x0A, 0x03, 0x00,  //   Usage (Scroll Lock)
0x0A, 0x04, 0x00,  //   Usage (Compose)
0x15, 0x00,        //   Logical Minimum (0)
0x25, 0x01,        //   Logical Maximum (1)
0x75, 0x01,        //   Report Size (1)
0x95, 0x04,        //   Report Count (4)
0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0x75, 0x04,        //   Report Size (4)
0x95, 0x01,        //   Report Count (1)
0x91, 0x03,        //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
0xC0,              // End Collection
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)
0xA1, 0x01,        // Collection (Application)
0x85, 0x03,        //   Report ID (3)
0x05, 0x06,        //   Usage Page (Generic Dev Ctrls)
0x09, 0x20,        //   Usage (Battery Strength)
0x15, 0x00,        //   Logical Minimum (0)
0x26, 0xFF, 0x00,  //   Logical Maximum (255)
0x75, 0x08,        //   Report Size (8)
0x95, 0x01,        //   Report Count (1)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x06, 0xBC, 0xFF,  //   Usage Page (Vendor Defined 0xFFBC)
0x0A, 0xAD, 0xBD,  //   Usage (0xBDAD)
0x75, 0x08,        //   Report Size (8)
0x95, 0x06,        //   Report Count (6)
0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
0x06, 0x78, 0xFF,  //   Usage Page (Vendor Defined 0xFF78)
0x0A, 0x03, 0x02,  //   Usage (0x0203)
0x75, 0x08,        //   Report Size (8)
0x95,              //   Report Count (0)

// 214 bytes
```