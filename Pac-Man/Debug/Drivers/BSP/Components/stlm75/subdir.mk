################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/stlm75/stlm75.c 

OBJS += \
./Drivers/BSP/Components/stlm75/stlm75.o 

C_DEPS += \
./Drivers/BSP/Components/stlm75/stlm75.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/stlm75/%.o Drivers/BSP/Components/stlm75/%.su Drivers/BSP/Components/stlm75/%.cyclo: ../Drivers/BSP/Components/stlm75/%.c Drivers/BSP/Components/stlm75/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-stlm75

clean-Drivers-2f-BSP-2f-Components-2f-stlm75:
	-$(RM) ./Drivers/BSP/Components/stlm75/stlm75.cyclo ./Drivers/BSP/Components/stlm75/stlm75.d ./Drivers/BSP/Components/stlm75/stlm75.o ./Drivers/BSP/Components/stlm75/stlm75.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-stlm75

