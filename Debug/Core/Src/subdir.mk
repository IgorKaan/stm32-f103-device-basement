################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32f1xx_hal_msp.o: ../Core/Src/stm32f1xx_hal_msp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f1xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/stm32f1xx_it.o: ../Core/Src/stm32f1xx_it.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f1xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/system_stm32f1xx.o: ../Core/Src/system_stm32f1xx.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f1xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

