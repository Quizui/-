################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TimerClock/subdir.mk
-include SonikWorkThread/subdir.mk
-include SonikString/subdir.mk
-include SonikStateMachine/subdir.mk
-include SonikFrameControl/subdir.mk
-include SonikFileSystems/subdir.mk
-include SonikCASLock/subdir.mk
-include MathBit/subdir.mk
-include AllocatorRaw/subdir.mk
-include Allocator/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: lib_Rx86_SonikLibraryAPI.a

# Tool invocations
lib_Rx86_SonikLibraryAPI.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	ar -r  "lib_Rx86_SonikLibraryAPI.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(ARCHIVES)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) lib_Rx86_SonikLibraryAPI.a
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
