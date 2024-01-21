################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/UTF8/SonikString_UTF8.cpp 

CPP_DEPS += \
./SonikString/UTF8/SonikString_UTF8.d 

OBJS += \
./SonikString/UTF8/SonikString_UTF8.o 


# Each subdirectory must supply rules for building sources it contributes
SonikString/UTF8/%.o: ../SonikString/UTF8/%.cpp SonikString/UTF8/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_RELEASE -D__cplusplus=202002L -D_WIN64 -I./UTF8 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikString-2f-UTF8

clean-SonikString-2f-UTF8:
	-$(RM) ./SonikString/UTF8/SonikString_UTF8.d ./SonikString/UTF8/SonikString_UTF8.o

.PHONY: clean-SonikString-2f-UTF8

