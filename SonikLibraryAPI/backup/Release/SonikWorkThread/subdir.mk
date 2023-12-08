################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikWorkThread/SonikWorkThreadEx.cpp \
../SonikWorkThread/SonikWorkThreadManagerEx.cpp 

OBJS += \
./SonikWorkThread/SonikWorkThreadEx.o \
./SonikWorkThread/SonikWorkThreadManagerEx.o 

CPP_DEPS += \
./SonikWorkThread/SonikWorkThreadEx.d \
./SonikWorkThread/SonikWorkThreadManagerEx.d 


# Each subdirectory must supply rules for building sources it contributes
SonikWorkThread/%.o: ../SonikWorkThread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\Thread" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


