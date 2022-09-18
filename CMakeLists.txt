cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

pico_sdk_init()

add_executable(test 
    main.cpp
    reboot/bootsel-reboot.cpp)

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)

pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib hardware_pwm pico_cyw43_arch_none)