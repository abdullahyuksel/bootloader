################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/boot/bootloader.c 

OBJS += \
./Core/Src/boot/bootloader.o 

C_DEPS += \
./Core/Src/boot/bootloader.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/boot/%.o Core/Src/boot/%.su: ../Core/Src/boot/%.c Core/Src/boot/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"D:/stmEgitim/bootloader/workspace_1.9.0_bootloader/bootloader_HAL_Application/Core/Src/boot" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-boot

clean-Core-2f-Src-2f-boot:
	-$(RM) ./Core/Src/boot/bootloader.d ./Core/Src/boot/bootloader.o ./Core/Src/boot/bootloader.su

.PHONY: clean-Core-2f-Src-2f-boot

