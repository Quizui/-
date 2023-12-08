################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikFileSystems/SonikFileController_SJISx86.cpp \
../SonikFileSystems/SonikFileController_UTF16x86.cpp \
../SonikFileSystems/SonikFileController_UTF8x86.cpp \
../SonikFileSystems/SonikFileController_x86.cpp \
../SonikFileSystems/SonikFileSystems.cpp 

OBJS += \
./SonikFileSystems/SonikFileController_SJISx86.o \
./SonikFileSystems/SonikFileController_UTF16x86.o \
./SonikFileSystems/SonikFileController_UTF8x86.o \
./SonikFileSystems/SonikFileController_x86.o \
./SonikFileSystems/SonikFileSystems.o 

CPP_DEPS += \
./SonikFileSystems/SonikFileController_SJISx86.d \
./SonikFileSystems/SonikFileController_UTF16x86.d \
./SonikFileSystems/SonikFileController_UTF8x86.d \
./SonikFileSystems/SonikFileController_x86.d \
./SonikFileSystems/SonikFileSystems.d 


# Each subdirectory must supply rules for building sources it contributes
SonikFileSystems/%.o: ../SonikFileSystems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++17 -D_RELEASE -D_WIN32 -D__cplusplus=201703L -I"D:\MyLibrary\include\FileSystems" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


