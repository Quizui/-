################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/UTF16/SonikStringUTF16.cpp 

CPP_DEPS += \
./SonikString/UTF16/SonikStringUTF16.d 

OBJS += \
./SonikString/UTF16/SonikStringUTF16.o 


# Each subdirectory must supply rules for building sources it contributes
SonikString/UTF16/%.o: ../SonikString/UTF16/%.cpp SonikString/UTF16/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D_WIN64 -I./UTF16 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikString-2f-UTF16

clean-SonikString-2f-UTF16:
	-$(RM) ./SonikString/UTF16/SonikStringUTF16.d ./SonikString/UTF16/SonikStringUTF16.o

.PHONY: clean-SonikString-2f-UTF16

