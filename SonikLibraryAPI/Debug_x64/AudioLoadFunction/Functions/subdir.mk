################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AudioLoadFunction/Functions/LoadFunction.cpp \
../AudioLoadFunction/Functions/WaveBitConvert.cpp \
../AudioLoadFunction/Functions/WriteFunction.cpp 

CPP_DEPS += \
./AudioLoadFunction/Functions/LoadFunction.d \
./AudioLoadFunction/Functions/WaveBitConvert.d \
./AudioLoadFunction/Functions/WriteFunction.d 

OBJS += \
./AudioLoadFunction/Functions/LoadFunction.o \
./AudioLoadFunction/Functions/WaveBitConvert.o \
./AudioLoadFunction/Functions/WriteFunction.o 


# Each subdirectory must supply rules for building sources it contributes
AudioLoadFunction/Functions/%.o: ../AudioLoadFunction/Functions/%.cpp AudioLoadFunction/Functions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D__cplusplus=202002L -D_WIN64 -I"D:\MyLibrary\include\Audio\AudioFormat\LoadFunction" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-AudioLoadFunction-2f-Functions

clean-AudioLoadFunction-2f-Functions:
	-$(RM) ./AudioLoadFunction/Functions/LoadFunction.d ./AudioLoadFunction/Functions/LoadFunction.o ./AudioLoadFunction/Functions/WaveBitConvert.d ./AudioLoadFunction/Functions/WaveBitConvert.o ./AudioLoadFunction/Functions/WriteFunction.d ./AudioLoadFunction/Functions/WriteFunction.o

.PHONY: clean-AudioLoadFunction-2f-Functions

