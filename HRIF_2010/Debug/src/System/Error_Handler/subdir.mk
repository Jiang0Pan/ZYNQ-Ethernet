################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/System/Error_Handler/error_handler.c 

OBJS += \
./src/System/Error_Handler/error_handler.o 

C_DEPS += \
./src/System/Error_Handler/error_handler.d 


# Each subdirectory must supply rules for building sources it contributes
src/System/Error_Handler/%.o: ../src/System/Error_Handler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I../../HRIF_2010_bsp/ps7_cortexa9_0/include -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\System_State" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Main" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Error_Handler" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\Emio" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\Ethernet" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\IIC" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\QSPI" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\SPI" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Device\PL" -I"E:\Benchmaking_DI\Software\HRIF_2010\src\Include\Others" -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


