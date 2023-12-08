################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikFrameControl/SonikFrameControl.cpp 

OBJS += \
./SonikFrameControl/SonikFrameControl.o 

CPP_DEPS += \
./SonikFrameControl/SonikFrameControl.d 


# Each subdirectory must supply rules for building sources it contributes
SonikFrameControl/%.o: ../SonikFrameControl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\FrameControl" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


