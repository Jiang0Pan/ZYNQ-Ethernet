################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/User_y/Max9972/Max528.c \
../src/User_y/Max9972/Max9972.c 

OBJS += \
./src/User_y/Max9972/Max528.o \
./src/User_y/Max9972/Max9972.o 

C_DEPS += \
./src/User_y/Max9972/Max528.d \
./src/User_y/Max9972/Max9972.d 


# Each subdirectory must supply rules for building sources it contributes
src/User_y/Max9972/%.o: ../src/User_y/Max9972/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Benchmaking_DI\Software\Reference\src\Peripherals\Include" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Emio" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Ethernet" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Main" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\QSPI" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Device\Spiflash" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Error_Handler" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\Others" -I"E:\Benchmaking_DI\Software\Reference\src\User_j\Include\System_State" -I"E:\Benchmaking_DI\Software\Reference\src\User_y\Include" -I"E:\Benchmaking_DI\Software\Reference_bsp\ps7_cortexa9_0\include" -I"E:\Benchmaking_DI\Software\Reference\src" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


