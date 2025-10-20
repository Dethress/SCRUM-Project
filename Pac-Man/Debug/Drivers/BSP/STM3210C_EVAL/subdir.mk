################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.c \
../Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.c 

OBJS += \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.o \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.o 

C_DEPS += \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.d \
./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM3210C_EVAL/%.o Drivers/BSP/STM3210C_EVAL/%.su Drivers/BSP/STM3210C_EVAL/%.cyclo: ../Drivers/BSP/STM3210C_EVAL/%.c Drivers/BSP/STM3210C_EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM3210C_EVAL

clean-Drivers-2f-BSP-2f-STM3210C_EVAL:
	-$(RM) ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_accelerometer.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_audio.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_eeprom.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_io.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_lcd.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_sd.su ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.cyclo ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.d ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.o ./Drivers/BSP/STM3210C_EVAL/stm3210c_eval_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM3210C_EVAL

