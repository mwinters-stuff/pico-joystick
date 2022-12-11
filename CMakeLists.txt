
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(PICO_SENSORS_PATH "../../pico-sensor-devices")
# set(PICO_SENSORS_FETCH_FROM_GIT 0)
include(pico_sdk_import.cmake)

set(PICO_SENSORS_FETCH_FROM_GIT 1)
include(pico_sensors_import.cmake)


project(joystick)

pico_sdk_init()

add_executable(dev_hid_composite)

target_sources(dev_hid_composite PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/hardware.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.cpp
        )

# target_include_directories(dev_hid_composite PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(dev_hid_composite PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

pico_enable_stdio_uart(dev_hid_composite 1)
pico_enable_stdio_usb(dev_hid_composite 0)

target_link_libraries(dev_hid_composite PUBLIC 
        tinyusb_device 
        tinyusb_board
        pico_stdlib 
        hardware_adc
        hardware_i2c
        hardware_watchdog
        sensor_PCF8591
        )

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(dev_hid_composite)

