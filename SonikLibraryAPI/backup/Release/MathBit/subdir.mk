################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MathBit/MathBit.cpp \
../MathBit/SonikKeyFrameMath.cpp \
../MathBit/SonikMathDistance.cpp \
../MathBit/SonikMathTrigonometric.cpp \
../MathBit/SonikNormalize.cpp 

OBJS += \
./MathBit/MathBit.o \
./MathBit/SonikKeyFrameMath.o \
./MathBit/SonikMathDistance.o \
./MathBit/SonikMathTrigonometric.o \
./MathBit/SonikNormalize.o 

CPP_DEPS += \
./MathBit/MathBit.d \
./MathBit/SonikKeyFrameMath.d \
./MathBit/SonikMathDistance.d \
./MathBit/SonikMathTrigonometric.d \
./MathBit/SonikNormalize.d 


# Each subdirectory must supply rules for building sources it contributes
MathBit/%.o: ../MathBit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\Bits" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


