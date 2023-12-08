################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AudioLoadFunction/Format/SonikAppleAiffFormat.cpp \
../AudioLoadFunction/Format/SonikWindowsWaveFormat.cpp 

CPP_DEPS += \
./AudioLoadFunction/Format/SonikAppleAiffFormat.d \
./AudioLoadFunction/Format/SonikWindowsWaveFormat.d 

OBJS += \
./AudioLoadFunction/Format/SonikAppleAiffFormat.o \
./AudioLoadFunction/Format/SonikWindowsWaveFormat.o 


# Each subdirectory must supply rules for building sources it contributes
AudioLoadFunction/Format/%.o: ../AudioLoadFunction/Format/%.cpp AudioLoadFunction/Format/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_RELEASE -D__cplusplus=202002L -D__SONIK_x86_64__=1 -D_WIN64 -I"D:\MyLibrary\include\Audio\AudioFormat\Format" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-AudioLoadFunction-2f-Format

clean-AudioLoadFunction-2f-Format:
	-$(RM) ./AudioLoadFunction/Format/SonikAppleAiffFormat.d ./AudioLoadFunction/Format/SonikAppleAiffFormat.o ./AudioLoadFunction/Format/SonikWindowsWaveFormat.d ./AudioLoadFunction/Format/SonikWindowsWaveFormat.o

.PHONY: clean-AudioLoadFunction-2f-Format

