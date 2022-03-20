# STM32G030F6P6 Evaluation board

## Introduction
This project's objective is to allow the evalution of the STM32G030F6 MCU based on a powerful Cortex-M0+ that can run at 64Mhz.
It has 32KB of Flash and 8KB of RAM and a very low price point.

## Motivation
The motivation behind this project is:
- Given the chip shortage, less powerful (but fully capable!) MCU like this one are still more available than others
- There are no development or evaluation boards for this specific MCU

## Features
This board will allow you to interface the MCU with interesting devices such as:
- USB com port with bus voltage monitoring
- IMU
- Digital temperature sensor
- 1.3" OLED display
- High current DC load (controllable via PWM)
- SPI bus
- User led and switch

## Development tools
The FW is developped and compiled in STM32CubeIDE v1.6.1.
For debugging you'll need an ST-LINK/V2 which can also be used to download the program.
It is also possible to download it via USB.

## Assembled PCB
![Alt text](PCB/stm32g0f0_eval_picture.jpg?raw=true)