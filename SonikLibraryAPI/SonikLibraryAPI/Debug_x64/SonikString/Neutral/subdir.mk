################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/Neutral/SonikString_CHR16.cpp \
../SonikString/Neutral/SonikString_CHR32.cpp 

CPP_DEPS += \
./SonikString/Neutral/SonikString_CHR16.d \
./SonikString/Neutral/SonikString_CHR32.d 

OBJS += \
./SonikString/Neutral/SonikString_CHR16.o \
./SonikString/Neutral/SonikString_CHR32.o 


# Each subdirectory must supply rules for building sources it contributes
SonikString/Neutral/%.o: ../SonikString/Neutral/%.cpp SonikString/Neutral/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D_WIN64 -I./Neutral -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikString-2f-Neutral

clean-SonikString-2f-Neutral:
	-$(RM) ./SonikString/Neutral/SonikString_CHR16.d ./SonikString/Neutral/SonikString_CHR16.o ./SonikString/Neutral/SonikString_CHR32.d ./SonikString/Neutral/SonikString_CHR32.o

.PHONY: clean-SonikString-2f-Neutral

