################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/SonikString.cpp \
../SonikString/SonikStringConvert.cpp 

OBJS += \
./SonikString/SonikString.o \
./SonikString/SonikStringConvert.o 

CPP_DEPS += \
./SonikString/SonikString.d \
./SonikString/SonikStringConvert.d 


# Each subdirectory must supply rules for building sources it contributes
SonikString/%.o: ../SonikString/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_RELEASE -I"D:\MyLibrary\include\SonikString" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


