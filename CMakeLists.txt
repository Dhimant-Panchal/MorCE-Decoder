cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(morse-code-assessment C CXX ASM)

pico_sdk_init()

add_executable(out main.c morse_tree.c parse_input_str.c seven_segment.c)
target_link_libraries(out pico_stdlib hardware_pwm hardware_adc pico_time)