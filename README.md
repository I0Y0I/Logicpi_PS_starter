# GD32F303CBT6 Starter Project for LogicPi

[中文](./README_cn.md)

This project is for the GD32F303CBT6 MCU in the LogicPi development board. The recommended development tool is the CLion IDE.

## Overview

This project provides a basic firmware structure for the GD32F303CBT6, including standard peripheral libraries, LogicPi drivers, and a sample application. It uses CMake for building.

## Directory Structure

- `Application/`: Contains the main application code.
- `Drivers/`: Contains all the hardware drivers.
  - `BSP/`: Board Support Package. Drivers for board-specific peripherals like LEDs, buttons, and USART.
  - `CMSIS/`: ARM Cortex-M4 core support files.
  - `GD32F30x_standard_peripheral/`: GigaDevice's standard peripheral drivers for the GD32F30x series.
  - `PicoKit/`: A small but powerful abstract driver library.
- `Project/`: Project-specific files.
  - `gd32f303cbt6.lds`: Linker script for the target MCU.
  - `gd32f303cbt6.cfg`: OpenOCD configuration for flashing and debugging.
  - `GD32F30x_HD.svd`: SVD file for peripheral register inspection in a debugger.
- `CMakeLists.txt`: The main CMake build script for the project.

## Prerequisites

To build and flash this project, you will need the following tools:

- **ARM GCC Toolchain:** `arm-none-eabi-gcc` and related tools.
- **CMake:** For generating the build system.
- **Make** (or Ninja, etc.): The build tool.
- **OpenOCD:** For flashing and debugging the microcontroller.
- **CLion IDE:** The recommended integrated development environment.

## Flashing and Debugging

The project includes a configuration file for OpenOCD (`Project/gd32f303cbt6.cfg`).

*Note: The `Project/gd32f303cbt6.cfg` might need to be adjusted based on your debug probe.*