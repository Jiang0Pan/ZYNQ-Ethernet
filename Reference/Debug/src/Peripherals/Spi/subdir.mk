################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Peripherals/Spi/Spi.c 

OBJS += \
./src/Peripherals/Spi/Spi.o 

C_DEPS += \
./src/Peripherals/Spi/Spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/Peripherals/Spi/%.o: ../src/Peripherals/Spi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Benchmaking_DI\Software\Reference\src\Peripherals\Include" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Emio" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Ethernet" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Main" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\QSPI" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Spiflash" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Error_Handler" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Others" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\System_State" -I"E:\Benchmaking_DI\Software\Reference\src\User_y\Include" -I"E:\Benchmaking_DI\Software\Reference_bsp\ps7_cortexa9_0\include" -I"E:\Benchmaking_DI\Software\Reference\src" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


