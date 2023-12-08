################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikFrameControl/SonikFrameControl.cpp \
../SonikFrameControl/SonikFrameControl_x64.cpp 

CPP_DEPS += \
./SonikFrameControl/SonikFrameControl.d \
./SonikFrameControl/SonikFrameControl_x64.d 

OBJS += \
./SonikFrameControl/SonikFrameControl.o \
./SonikFrameControl/SonikFrameControl_x64.o 


# Each subdirectory must supply rules for building sources it contributes
SonikFrameControl/%.o: ../SonikFrameControl/%.cpp SonikFrameControl/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D__cplusplus=202002L -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikFrameControl

clean-SonikFrameControl:
	-$(RM) ./SonikFrameControl/SonikFrameControl.d ./SonikFrameControl/SonikFrameControl.o ./SonikFrameControl/SonikFrameControl_x64.d ./SonikFrameControl/SonikFrameControl_x64.o

.PHONY: clean-SonikFrameControl

