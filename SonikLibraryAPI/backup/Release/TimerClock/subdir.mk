################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TimerClock/SonikElapsedTimer.cpp 

OBJS += \
./TimerClock/SonikElapsedTimer.o 

CPP_DEPS += \
./TimerClock/SonikElapsedTimer.d 


# Each subdirectory must supply rules for building sources it contributes
TimerClock/%.o: ../TimerClock/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++17 -D_RELEASE -D_WIN32 -D__cplusplus=201703L -ID:/MyLibrary/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


