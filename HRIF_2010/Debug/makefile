################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/System/System_State/subdir.mk
-include src/System/System_Config/FPGA_Config/subdir.mk
-include src/System/System_Config/DPS_Config/subdir.mk
-include src/System/Main/subdir.mk
-include src/System/Error_Handler/subdir.mk
-include src/System/Device/SPI/SPI_Device/subdir.mk
-include src/System/Device/SPI/SPI_BUS/subdir.mk
-include src/System/Device/QSPI/QSPI_Device/subdir.mk
-include src/System/Device/QSPI/QSPI_BUS/subdir.mk
-include src/System/Device/PL/Axi/subdir.mk
-include src/System/Device/IIC/IIC_Device/subdir.mk
-include src/System/Device/IIC/IIC_BUS/subdir.mk
-include src/System/Device/Ethernet/Verify/subdir.mk
-include src/System/Device/Ethernet/Tcp/subdir.mk
-include src/System/Device/Ethernet/Operation/subdir.mk
-include src/System/Device/Ethernet/App_Layer_Protocol/subdir.mk
-include src/System/Device/Ethernet/Ack/subdir.mk
-include src/System/Device/Emio/subdir.mk
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
HRIF_2010.elf.size \


# All Target
all: HRIF_2010.elf secondary-outputs

# Tool invocations
HRIF_2010.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -Wl,-T -Wl,../src/lscript.ld -L../../HRIF_2010_bsp/ps7_cortexa9_0/lib -o "HRIF_2010.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HRIF_2010.elf.size: HRIF_2010.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size HRIF_2010.elf  |tee "HRIF_2010.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) HRIF_2010.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
