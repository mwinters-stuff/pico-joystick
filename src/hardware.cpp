#include<sstream>

#include "hardware.h"
#include "pico/binary_info.h"

static const uint8_t buttons[] = {
   GPIO_BUTTON_1_1,GPIO_BUTTON_1_2,GPIO_BUTTON_1_3,
   GPIO_BUTTON_2_1,GPIO_BUTTON_2_2,GPIO_BUTTON_2_3,
   GPIO_BUTTON_3_1,GPIO_BUTTON_3_2,GPIO_BUTTON_3_3,
};

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

Hardware hardware;

Hardware::Hardware(): i2c(i2c0), pcf8591(){
  blink_interval_ms = 0;
  
}

void Hardware::begin(){


  adc_init();
  adc_gpio_init(26);
  adc_gpio_init(27);
  adc_gpio_init(28);

  i2c_init(i2c, 40 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

  if(!pcf8591.begin(i2c)){
    printf("ERROR: PCF8591 Failed to talk\n");
  }
  pcf8591.disableDAC();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  set_gpio_pin_out(GPIO_BUTTON_STICK1);
  set_gpio_pin_out(GPIO_BUTTON_STICK2);
  set_gpio_pin_out(GPIO_SWITCH_1_UP);
  set_gpio_pin_out(GPIO_SWITCH_1_DOWN);
  set_gpio_pin_out(GPIO_SWITCH_2_UP);
  set_gpio_pin_out(GPIO_SWITCH_2_DOWN);

  for(int d =0; d < 9; d++){
    set_gpio_pin_out(buttons[d]);
  }

}

void Hardware::set_gpio_pin_out(uint8_t pin){
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
  gpio_set_pulls(pin, true, false);
}

std::string Hardware::debug(){
      std::stringstream ss;
      
      const uint adc_max = (1 << 8);
      
      const uint bar_width = 20;
      uint bar_x_pos = adc_stick_1_x_raw * bar_width / adc_max;
      uint bar_y_pos = adc_stick_1_y_raw * bar_width / adc_max;
      ss << "X: [";
      for (int i = 0; i < bar_width; ++i){ 
        ss << (i == bar_x_pos ? 'o' : ' ');
      }
      ss << "]  Y: [";
      for (int i = 0; i < bar_width; ++i){
        ss << (i == bar_y_pos ? 'o' : ' ');
      } 
      ss << "] ";

      bar_x_pos = adc_stick_2_x_raw * bar_width / adc_max;
      bar_y_pos = adc_stick_2_y_raw * bar_width / adc_max;
      ss << "X: [";
      for (int i = 0; i < bar_width; ++i){ 
        ss << (i == bar_x_pos ? 'o' : ' ');
      }
      ss << "]  Y: [";
      for (int i = 0; i < bar_width; ++i){
        ss << (i == bar_y_pos ? 'o' : ' ');
      } 
      ss << "] ("
         << (stick_down1 ? "X" : ".")
         << (stick_down2 ? "X" : ".") << " ";

      for(int d =0; d < 9; d++){
        ss << (button_down((ButtonArray)d) ? "X" : ".");
        if(d == 2 || d == 5){
          ss << "/";
        }
      }

      ss << "/";
      switch(switchesPosition){
        case spTopUpBottomUp:
          ss << "UU";
          break;
        case spTopUpBottomDown:
          ss << "UD";
          break;
        case spTopDownBottomUp:
          ss << "DU";
          break;
        case spTopDownBottomDown:
          ss << "DD";
          break;
      }

      ss << ") " << (int)adc_stick_1_x_raw << " " << (int)adc_stick_1_y_raw << " " << (int)adc_stick_2_x_raw << " " <<  (int)adc_stick_2_y_raw << "          \r";
      return ss.str();
}

void Hardware::update(){
  led_blinking_task();

    if(pcf8591.analogRead4() == PCF8591_I2C_ERROR)
    {
      printf("****I2C Error\n\n\n");
    
    }else{
      adc_stick_1_y_raw = pcf8591.lastRead(0) ^ 0xff;
      adc_stick_1_x_raw = pcf8591.lastRead(1) ;
      adc_stick_2_y_raw = pcf8591.lastRead(2) ^ 0xff;
      adc_stick_2_x_raw = pcf8591.lastRead(3) ;
    }

    stick_down1 = !gpio_get(GPIO_BUTTON_STICK1);
    stick_down2 = !gpio_get(GPIO_BUTTON_STICK2);

    lastButtonDown = baNone;
    for(int d =0; d < 9; d++){
      buttons_down[d] = !gpio_get(buttons[d]);
      if(buttons_down[d]){
        lastButtonDown = (ButtonArray)d;
      }
    }
 
    bool sw1_up = !gpio_get(GPIO_SWITCH_1_UP);
    bool sw1_down = !gpio_get(GPIO_SWITCH_1_DOWN);

    bool sw2_up = !gpio_get(GPIO_SWITCH_2_UP);
    bool sw2_down = !gpio_get(GPIO_SWITCH_2_DOWN);

    if(sw1_up && sw2_up){
      switchesPosition = spTopUpBottomUp;
    }else if(sw1_up && sw2_down){
      switchesPosition = spTopUpBottomDown;
    }else if(sw1_down && sw2_up){
      switchesPosition = spTopDownBottomUp;
    }else if(sw1_down && sw2_down){
      switchesPosition = spTopDownBottomDown;
    }
}

void Hardware::led_blinking_task() {
  // blink is disabled
  if (!blink_interval_ms)
{
    return;
}

  // Blink every interval ms
  if (absolute_time_diff_us(get_absolute_time(), next_blink_time) > 0){
    return;  // not enough time
  } 

  next_blink_time = make_timeout_time_ms(blink_interval_ms);
  led_state = !led_state;
  gpio_put(LED_PIN, led_state);
}

void Hardware::led_blink_slow(){
  blink_interval_ms = BLINK_NOT_MOUNTED;
  next_blink_time = make_timeout_time_ms(blink_interval_ms);
}

void Hardware::led_blink_slower(){
  blink_interval_ms = BLINK_SUSPENDED;
  next_blink_time = make_timeout_time_ms(blink_interval_ms);
}

void Hardware::led_blink_fast(){
  blink_interval_ms = BLINK_MOUNTED;
  next_blink_time = make_timeout_time_ms(blink_interval_ms);
}

void Hardware::led_off(){
  blink_interval_ms = 0;
  gpio_put(LED_PIN,0);
}

void Hardware::led_on(){
  blink_interval_ms = 0;
  gpio_put(LED_PIN,1);
}


uint8_t Hardware::stick_left_x(){
  return adc_stick_1_x_raw;
}

uint8_t Hardware::stick_left_y(){
  return adc_stick_1_y_raw;
}

bool Hardware::stick_left_button_down(){
  return stick_down1;
}

uint8_t Hardware::stick_right_x()
{
  return adc_stick_2_x_raw;
}

uint8_t Hardware::stick_right_y()
{
  return adc_stick_2_y_raw;
}

bool Hardware::stick_right_button_down(){
  return stick_down2;
}

bool Hardware::button_down(const ButtonArray button){
  return buttons_down[button];
}

ButtonArray Hardware::last_button_down(){
  return lastButtonDown;
}

SwitchesPosition Hardware::switches_position(){
  return switchesPosition;
}

uint16_t Hardware::analog_pot_0(){
return 0;
}

uint16_t Hardware::analog_pot_1(){
return 0;
}

uint16_t Hardware::analog_pot_2(){
  return 0;
}
