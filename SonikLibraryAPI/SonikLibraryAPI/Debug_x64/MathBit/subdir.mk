################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MathBit/MathBit.cpp \
../MathBit/SonikKeyFrameMath.cpp \
../MathBit/SonikMathDistance.cpp \
../MathBit/SonikMathStandard.cpp \
../MathBit/SonikMathTrigonometric.cpp \
../MathBit/SonikNormalize.cpp 

CPP_DEPS += \
./MathBit/MathBit.d \
./MathBit/SonikKeyFrameMath.d \
./MathBit/SonikMathDistance.d \
./MathBit/SonikMathStandard.d \
./MathBit/SonikMathTrigonometric.d \
./MathBit/SonikNormalize.d 

OBJS += \
./MathBit/MathBit.o \
./MathBit/SonikKeyFrameMath.o \
./MathBit/SonikMathDistance.o \
./MathBit/SonikMathStandard.o \
./MathBit/SonikMathTrigonometric.o \
./MathBit/SonikNormalize.o 


# Each subdirectory must supply rules for building sources it contributes
MathBit/%.o: ../MathBit/%.cpp MathBit/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D__cplusplus=202002L -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MathBit

clean-MathBit:
	-$(RM) ./MathBit/MathBit.d ./MathBit/MathBit.o ./MathBit/SonikKeyFrameMath.d ./MathBit/SonikKeyFrameMath.o ./MathBit/SonikMathDistance.d ./MathBit/SonikMathDistance.o ./MathBit/SonikMathStandard.d ./MathBit/SonikMathStandard.o ./MathBit/SonikMathTrigonometric.d ./MathBit/SonikMathTrigonometric.o ./MathBit/SonikNormalize.d ./MathBit/SonikNormalize.o

.PHONY: clean-MathBit

