# LogicPi GD32F303CBT6 模板项目

本项目适用于 LogicPi 开发板上的 GD32F303CBT6 MCU。推荐的开发工具为 CLion IDE。

## 概述

本项目为 GD32F303CBT6 提供了一个基础固件模板，包括标准外设库、LogicPi 驱动以及一个示例应用程序。项目使用 CMake 进行构建。

## 目录结构

- `Application/`: 包含主应用程序代码。
- `Drivers/`: 包含所有硬件驱动。
  - `BSP/`: 板级支持包。用于特定于开发板的外设驱动，如 LED、按键和 USART。
  - `CMSIS/`: ARM Cortex-M4 内核支持文件。
  - `GD32F30x_standard_peripheral/`: GigaDevice 的 GD32F30x 系列标准外设驱动。
  - `PicoKit/`: 一个小而强大的抽象驱动库。
- `Project/`: 项目特定文件。
  - `gd32f303cbt6.lds`: 目标 MCU 的链接器脚本。
  - `gd32f303cbt6.cfg`: 用于烧录和调试的 OpenOCD 配置文件。
  - `GD32F30x_HD.svd`: 用于在调试器中检查外设寄存器的 SVD 文件。
- `CMakeLists.txt`: 项目的主 CMake 构建脚本。

## 环境准备

要构建和烧录此项目，您将需要以下工具：

- **ARM GCC 工具链:** `arm-none-eabi-gcc` 及相关工具。
- **CMake:** 用于生成构建系统。
- **Make** (或 Ninja 等): 构建工具。
- **OpenOCD:** 用于烧录和调试微控制器。
- **CLion IDE:** 推荐的集成开发环境。

## 烧录和调试

项目包含一个 OpenOCD 的配置文件 (`Project/gd32f303cbt6.cfg`)。

*注意：您可能需要根据您的调试器来调整 `Project/gd32f303cbt6.cfg` 文件。*
