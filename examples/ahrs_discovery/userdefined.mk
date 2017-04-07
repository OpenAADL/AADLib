# This makefile configured the compilation chain for this example.

###############################################################################
# User-specific installaiton, please adjust

# Path to STM32Cube, and its bundled FreeRTOS
STM32LIB = $(HOME)/local/STM32Cube_FW_F4_V1.15.0
FREERTOS = ${STM32LIB}/Middlewares/Third_Party/FreeRTOS

USER_LDFLAGS += -T $(shell pwd)/../../LinkerScript.ld

# Third-party Mavlink library
MAVLINK_HEADERS=$(HOME)/local/mavlnkgit/mavlink_headers
USER_INCLUDE += -I${MAVLINK_HEADERS}/common

# Local copy of the BSP adapted for this example

DISCOVERY_FOLDER = $(shell pwd)/../../src
USER_INCLUDE += -I$(shell pwd)/../../include

###############################################################################
# Toolchain configuration

USER_CC  =   arm-none-eabi-gcc
USER_CPP =   arm-none-eabi-g++

AS       =   arm-none-eabi-gcc
LD       =   arm-none-eabi-gcc

LD_CPP   =   arm-none-eabi-g++

# Compilation-time configuration
USER_CFLAGS += -g3
USER_CFLAGS += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -g3
USER_CFLAGS += -DSTM32F411VETx -DSTM32F4 -DSTM32 -DSTM32F411E_DISCO	\
	-DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DFREERTOS

# Link-time configuration
USER_LDFLAGS +=-specs=rdimon.specs
USER_LIBS    +=-lrdimon

################################################################################
# FreeRTOS compilation

# FreeRTOS include
USER_INCLUDE += -I${FREERTOS}/Source/include
USER_INCLUDE += -I${FREERTOS}/Source/portable/GCC/ARM_CM4F
USER_INCLUDE += -I${FREERTOS}/Source/CMSIS_RTOS
# CMSIS library
USER_INCLUDE += -I${STM32LIB}/Drivers/CMSIS/Include
USER_INCLUDE += -I${STM32LIB}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
USER_INCLUDE += -I${STM32LIB}/Drivers/STM32F4xx_HAL_Driver/Inc
USER_INCLUDE += -I${STM32LIB}/Drivers/BSP/STM32F401-Discovery/

RTOS_CFLAG += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -g3

VPATH = ${STM32LIB}/Drivers/STM32F4xx_HAL_Driver/Src/:${STM32LIB}/Drivers/BSP/STM32F401-Discovery/:${STM32LIB}/Drivers/BSP/Components/lsm303dlhc/:${STM32LIB}/Drivers/BSP/Components/l3gd20/:${STM32LIB}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/:${DISCOVERY_FOLDER}:${FREERTOS}/Source:${FREERTOS}/Source/portable/GCC/ARM_CM4F/:${FREERTOS}/Source/portable/CMSIS_RTOS:${FREERTOS}/Source/portable/MemMang/:${FREERTOS}/Source/CMSIS_RTOS/

COMPILE_FREERTOS_OBJ = croutine.o event_groups.o list.o queue.o		\
tasks.o timers.o port.o heap_4.o stm32f4xx_hal_cortex.o			\
stm32f4xx_hal.o stm32f4xx_hal_rcc.o stm32f4xx_hal_gpio.o		\
stm32f4xx_hal_uart.o stm32f4xx_hal_i2c.o stm32f4xx_hal_spi.o		\
stm32f4xx_hal_dma.o stm32f401_discovery.o				\
stm32f401_discovery_accelerometer.o stm32f401_discovery_gyroscope.o	\
lsm303dlhc.o l3gd20.o system_stm32f4xx.o cmsis_os.o			\
startup_stm32f411xe.o stm32f4xx_it.o stm32f4xx_hal_msp.o hardware.o	\
stm32_mavlink.o AttitudeEKF.o
