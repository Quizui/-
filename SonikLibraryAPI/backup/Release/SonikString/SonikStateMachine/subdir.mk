################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/SonikStateMachine/SonikStateBase.cpp \
../SonikString/SonikStateMachine/SonikStateFactory.cpp 

OBJS += \
./SonikString/SonikStateMachine/SonikStateBase.o \
./SonikString/SonikStateMachine/SonikStateFactory.o 

CPP_DEPS += \
./SonikString/SonikStateMachine/SonikStateBase.d \
./SonikString/SonikStateMachine/SonikStateFactory.d 


# Each subdirectory must supply rules for building sources it contributes
SonikString/SonikStateMachine/%.o: ../SonikString/SonikStateMachine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D_RELEASE -D__cplusplus=201103L -D_WIN32 -I"D:\MyLibrary\include\StateMachine" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


