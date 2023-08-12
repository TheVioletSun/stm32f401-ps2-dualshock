################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ps2-dualshock-spi/ps2_dualshock_spi.c 

OBJS += \
./ps2-dualshock-spi/ps2_dualshock_spi.o

C_DEPS += \
./ps2-dualshock-spi/ps2_dualshock_spi.d 


# Each subdirectory must supply rules for building sources it contributes
ps2-dualshock-spi/%.o ps2-dualshock-spi/%.su ps2-dualshock-spi/%.cyclo: ../ps2-dualshock-spi/%.c ps2-dualshock-spi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../ps2-dualshock-spi -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ps2-dualshock-spi-Src

clean-ps2-dualshock-spi-Src:
	-$(RM) ./ps2-dualshock-spi/ps2_dualshock_spi.cyclo ./ps2-dualshock-spi/ps2_dualshock_spi.d ./ps2-dualshock-spi/ps2_dualshock_spi.o ./ps2-dualshock-spi/ps2_dualshock_spi.su 


.PHONY: clean-ps2-dualshock-spi-Src

