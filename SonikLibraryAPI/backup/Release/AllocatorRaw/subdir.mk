################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AllocatorRaw/SonikAllocateRawExAccessCall.cpp 

OBJS += \
./AllocatorRaw/SonikAllocateRawExAccessCall.o 

CPP_DEPS += \
./AllocatorRaw/SonikAllocateRawExAccessCall.d 


# Each subdirectory must supply rules for building sources it contributes
AllocatorRaw/%.o: ../AllocatorRaw/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\Allocate" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


