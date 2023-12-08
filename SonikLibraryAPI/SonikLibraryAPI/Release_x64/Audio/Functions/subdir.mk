################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Audio/Functions/LoadFunction.cpp \
../Audio/Functions/WaveBitConvert.cpp \
../Audio/Functions/WriteFunction.cpp 

CPP_DEPS += \
./Audio/Functions/LoadFunction.d \
./Audio/Functions/WaveBitConvert.d \
./Audio/Functions/WriteFunction.d 

OBJS += \
./Audio/Functions/LoadFunction.o \
./Audio/Functions/WaveBitConvert.o \
./Audio/Functions/WriteFunction.o 


# Each subdirectory must supply rules for building sources it contributes
Audio/Functions/%.o: ../Audio/Functions/%.cpp Audio/Functions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_RELEASE -D__cplusplus=202002L -D_WIN64 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Audio-2f-Functions

clean-Audio-2f-Functions:
	-$(RM) ./Audio/Functions/LoadFunction.d ./Audio/Functions/LoadFunction.o ./Audio/Functions/WaveBitConvert.d ./Audio/Functions/WaveBitConvert.o ./Audio/Functions/WriteFunction.d ./Audio/Functions/WriteFunction.o

.PHONY: clean-Audio-2f-Functions

