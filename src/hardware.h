#ifndef _HARDWARE_H
#define _HARDWARE_H

#include <string>
#include <cstdint>

#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "sensor/PCF8591.h"

#define LED_PIN PICO_DEFAULT_LED_PIN

#define GPIO_BUTTON_STICK1 2
#define GPIO_BUTTON_STICK2 3

#define GPIO_BUTTON_1_1 9
#define GPIO_BUTTON_1_2 7
#define GPIO_BUTTON_1_3 14

#define GPIO_BUTTON_2_1 8
#define GPIO_BUTTON_2_2 13
#define GPIO_BUTTON_2_3 12

#define GPIO_BUTTON_3_1 6
#define GPIO_BUTTON_3_2 11
#define GPIO_BUTTON_3_3 10

#define GPIO_SWITCH_1_UP   18
#define GPIO_SWITCH_1_DOWN 19

#define GPIO_SWITCH_2_UP   20
#define GPIO_SWITCH_2_DOWN 21


enum SwitchesPosition{
  spTopUpBottomUp,
  spTopDownBottomUp,
  spTopUpBottomDown,
  spTopDownBottomDown,
};

enum ButtonArray{
  baTopLeft,
  baTopMiddle,
  baTopRight,
  baMiddleLeft,
  baMiddleMiddle,
  baMiddleRight,
  baBottomLeft,
  baBottomMiddle,
  baBottomRight,
  baNone,
};

class Hardware{
  private:
    i2c_inst_t* i2c;
    PCF8591 pcf8591;
    uint16_t blink_interval_ms;
    absolute_time_t next_blink_time;
    bool led_state;

    void set_gpio_pin_out(uint8_t pin);
    void led_blinking_task();


    uint8_t adc_stick_1_x_raw;
    uint8_t adc_stick_1_y_raw;
    uint8_t adc_stick_2_x_raw;
    uint8_t adc_stick_2_y_raw; 

    bool stick_down1 = false;
    bool stick_down2 = false;

    bool buttons_down[9] = {false,false,false,false,false,false,false,false,false};
    ButtonArray lastButtonDown = baNone;

    SwitchesPosition switchesPosition;
  
  public:
    Hardware();

    std::string debug();

    void begin();
    void update();

    uint8_t stick_left_x();
    uint8_t stick_left_y();
    bool stick_left_button_down();

    uint8_t stick_right_x();
    uint8_t stick_right_y();
    bool stick_right_button_down();

    bool button_down(const ButtonArray button);
    ButtonArray last_button_down();

    SwitchesPosition switches_position();

    uint16_t analog_pot_0();
    uint16_t analog_pot_1();
    uint16_t analog_pot_2();


    void led_blink_slow();
    void led_blink_slower();
    void led_blink_fast();
    void led_off();
    void led_on();

};

extern Hardware hardware;

#endif