################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DllAccess/SonikDllAccessManager.cpp \
../DllAccess/SonikDllLoader.cpp 

CPP_DEPS += \
./DllAccess/SonikDllAccessManager.d \
./DllAccess/SonikDllLoader.d 

OBJS += \
./DllAccess/SonikDllAccessManager.o \
./DllAccess/SonikDllLoader.o 


# Each subdirectory must supply rules for building sources it contributes
DllAccess/%.o: ../DllAccess/%.cpp DllAccess/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-DllAccess

clean-DllAccess:
	-$(RM) ./DllAccess/SonikDllAccessManager.d ./DllAccess/SonikDllAccessManager.o ./DllAccess/SonikDllLoader.d ./DllAccess/SonikDllLoader.o

.PHONY: clean-DllAccess

