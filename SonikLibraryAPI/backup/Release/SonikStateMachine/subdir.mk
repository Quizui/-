################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikStateMachine/SonikStateBase.cpp \
../SonikStateMachine/SonikStateFactory.cpp 

OBJS += \
./SonikStateMachine/SonikStateBase.o \
./SonikStateMachine/SonikStateFactory.o 

CPP_DEPS += \
./SonikStateMachine/SonikStateBase.d \
./SonikStateMachine/SonikStateFactory.d 


# Each subdirectory must supply rules for building sources it contributes
SonikStateMachine/%.o: ../SonikStateMachine/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\StateMachine" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


