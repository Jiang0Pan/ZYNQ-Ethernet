################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/User_y/Version/subdir.mk
-include src/User_y/Storage/subdir.mk
-include src/User_y/Max9972/subdir.mk
-include src/User_y/IO/subdir.mk
-include src/User_y/Dps/subdir.mk
-include src/User_y/Dev_Ctl/subdir.mk
-include src/User_y/ADS8688/subdir.mk
-include src/User_j/System/System_State/subdir.mk
-include src/User_j/System/Main/subdir.mk
-include src/User_j/System/Error_Handler/subdir.mk
-include src/User_j/System/Device/Spiflash/subdir.mk
-include src/User_j/System/Device/QSPI/QSPI_Device/subdir.mk
-include src/User_j/System/Device/QSPI/QSPI_BUS/subdir.mk
-include src/User_j/System/Device/Ethernet/Verify/subdir.mk
-include src/User_j/System/Device/Ethernet/Tcp/subdir.mk
-include src/User_j/System/Device/Ethernet/Operation/subdir.mk
-include src/User_j/System/Device/Ethernet/App_Layer_Protocol/subdir.mk
-include src/User_j/System/Device/Ethernet/Ack/subdir.mk
-include src/User_j/System/Device/Emio/subdir.mk
-include src/Peripherals/Uartps/subdir.mk
-include src/Peripherals/Timer/subdir.mk
-include src/Peripherals/Spi/subdir.mk
-include src/Peripherals/Interrupt/subdir.mk
-include src/Peripherals/IIC/subdir.mk
-include src/Peripherals/Gpio/subdir.mk
-include src/Peripherals/Assist/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
Reference.elf.size \


# All Target
all: Reference.elf secondary-outputs

# Tool invocations
Reference.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -Wl,-T -Wl,../src/lscript.ld -L../../Reference_bsp/ps7_cortexa9_0/lib -o "Reference.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Reference.elf.size: Reference.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size Reference.elf  |tee "Reference.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) Reference.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
