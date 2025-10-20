################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/audio_play.c \
../Core/Src/eeprom.c \
../Core/Src/joystick.c \
../Core/Src/lcd.c \
../Core/Src/lcd_log.c \
../Core/Src/log.c \
../Core/Src/main.c \
../Core/Src/mems.c \
../Core/Src/sd.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/touchscreen.c \
../Core/Src/ts_calibration.c 

OBJS += \
./Core/Src/audio_play.o \
./Core/Src/eeprom.o \
./Core/Src/joystick.o \
./Core/Src/lcd.o \
./Core/Src/lcd_log.o \
./Core/Src/log.o \
./Core/Src/main.o \
./Core/Src/mems.o \
./Core/Src/sd.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/touchscreen.o \
./Core/Src/ts_calibration.o 

C_DEPS += \
./Core/Src/audio_play.d \
./Core/Src/eeprom.d \
./Core/Src/joystick.d \
./Core/Src/lcd.d \
./Core/Src/lcd_log.d \
./Core/Src/log.d \
./Core/Src/main.d \
./Core/Src/mems.d \
./Core/Src/sd.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/touchscreen.d \
./Core/Src/ts_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/audio_play.cyclo ./Core/Src/audio_play.d ./Core/Src/audio_play.o ./Core/Src/audio_play.su ./Core/Src/eeprom.cyclo ./Core/Src/eeprom.d ./Core/Src/eeprom.o ./Core/Src/eeprom.su ./Core/Src/joystick.cyclo ./Core/Src/joystick.d ./Core/Src/joystick.o ./Core/Src/joystick.su ./Core/Src/lcd.cyclo ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/lcd_log.cyclo ./Core/Src/lcd_log.d ./Core/Src/lcd_log.o ./Core/Src/lcd_log.su ./Core/Src/log.cyclo ./Core/Src/log.d ./Core/Src/log.o ./Core/Src/log.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mems.cyclo ./Core/Src/mems.d ./Core/Src/mems.o ./Core/Src/mems.su ./Core/Src/sd.cyclo ./Core/Src/sd.d ./Core/Src/sd.o ./Core/Src/sd.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/touchscreen.cyclo ./Core/Src/touchscreen.d ./Core/Src/touchscreen.o ./Core/Src/touchscreen.su ./Core/Src/ts_calibration.cyclo ./Core/Src/ts_calibration.d ./Core/Src/ts_calibration.o ./Core/Src/ts_calibration.su

.PHONY: clean-Core-2f-Src

