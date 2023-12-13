################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/SonikString.cpp \
../SonikString/SonikStringConvert.cpp 

CPP_DEPS += \
./SonikString/SonikString.d \
./SonikString/SonikStringConvert.d 

OBJS += \
./SonikString/SonikString.o \
./SonikString/SonikStringConvert.o 


# Each subdirectory must supply rules for building sources it contributes
SonikString/%.o: ../SonikString/%.cpp SonikString/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_RELEASE -D__cplusplus=202002L -D_WIN64 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikString

clean-SonikString:
	-$(RM) ./SonikString/SonikString.d ./SonikString/SonikString.o ./SonikString/SonikStringConvert.d ./SonikString/SonikStringConvert.o

.PHONY: clean-SonikString

