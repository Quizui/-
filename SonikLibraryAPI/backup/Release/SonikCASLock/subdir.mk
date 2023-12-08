################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikCASLock/SonikAtomicLock.cpp 

OBJS += \
./SonikCASLock/SonikAtomicLock.o 

CPP_DEPS += \
./SonikCASLock/SonikAtomicLock.d 


# Each subdirectory must supply rules for building sources it contributes
SonikCASLock/%.o: ../SonikCASLock/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\CASLock" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


