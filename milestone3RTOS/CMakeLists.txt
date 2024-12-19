cmake_minimum_required(VERSION 3.13)

# Set the C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Specify the board type
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Define the project
project(milestone2 C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable and source files, including ir_sensor.c
add_executable(milestone2 
    milestone2.c
    ultrasonic_sensor.c
    motor_control.c
    ir_sensor.c          # Added IR sensor source file
)

# Set program name and version
pico_set_program_name(milestone2 "milestone2")
pico_set_program_version(milestone2 "0.1")

# Enable USB output (for debugging)
pico_enable_stdio_uart(milestone2 0)
pico_enable_stdio_usb(milestone2 1)

# Link libraries
target_link_libraries(milestone2
    pico_stdlib         # Standard library for Pico
    hardware_pwm        # Required for motor control
)

# Add the standard include files to the build
target_include_directories(milestone2 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Generate additional output formats (e.g., UF2)
pico_add_extra_outputs(milestone2)
