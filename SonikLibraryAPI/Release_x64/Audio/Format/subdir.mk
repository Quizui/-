################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Audio/Format/SonikAppleAiffFormat.cpp \
../Audio/Format/SonikWindowsWaveFormat.cpp 

CPP_DEPS += \
./Audio/Format/SonikAppleAiffFormat.d \
./Audio/Format/SonikWindowsWaveFormat.d 

OBJS += \
./Audio/Format/SonikAppleAiffFormat.o \
./Audio/Format/SonikWindowsWaveFormat.o 


# Each subdirectory must supply rules for building sources it contributes
Audio/Format/%.o: ../Audio/Format/%.cpp Audio/Format/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_RELEASE -D__cplusplus=202002L -D_WIN64 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Audio-2f-Format

clean-Audio-2f-Format:
	-$(RM) ./Audio/Format/SonikAppleAiffFormat.d ./Audio/Format/SonikAppleAiffFormat.o ./Audio/Format/SonikWindowsWaveFormat.d ./Audio/Format/SonikWindowsWaveFormat.o

.PHONY: clean-Audio-2f-Format

