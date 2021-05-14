################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Packet_analyzer/Packet_analyzer.cpp 

OBJS += \
./Core/Packet_analyzer/Packet_analyzer.o 

CPP_DEPS += \
./Core/Packet_analyzer/Packet_analyzer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Packet_analyzer/Packet_analyzer.o: ../Core/Packet_analyzer/Packet_analyzer.cpp Core/Packet_analyzer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Check_clock" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Clock_channel" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Device_relay" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/FlashPROM" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_main_cpp" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Grow_device" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Grow_device_component" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_module" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/Packet_analyzer" -I"/home/igor/Downloads/Telegram Desktop/STM32F103C8_device-basement/Core/LoRa_contact_data" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Packet_analyzer/Packet_analyzer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

