################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikFileSystems/SonikFileController_SJISx64.cpp \
../SonikFileSystems/SonikFileController_SJISx86.cpp \
../SonikFileSystems/SonikFileController_UTF16x64.cpp \
../SonikFileSystems/SonikFileController_UTF16x86.cpp \
../SonikFileSystems/SonikFileController_UTF8x64.cpp \
../SonikFileSystems/SonikFileController_UTF8x86.cpp \
../SonikFileSystems/SonikFileController_x64.cpp \
../SonikFileSystems/SonikFileController_x86.cpp \
../SonikFileSystems/SonikFileSystems.cpp 

CPP_DEPS += \
./SonikFileSystems/SonikFileController_SJISx64.d \
./SonikFileSystems/SonikFileController_SJISx86.d \
./SonikFileSystems/SonikFileController_UTF16x64.d \
./SonikFileSystems/SonikFileController_UTF16x86.d \
./SonikFileSystems/SonikFileController_UTF8x64.d \
./SonikFileSystems/SonikFileController_UTF8x86.d \
./SonikFileSystems/SonikFileController_x64.d \
./SonikFileSystems/SonikFileController_x86.d \
./SonikFileSystems/SonikFileSystems.d 

OBJS += \
./SonikFileSystems/SonikFileController_SJISx64.o \
./SonikFileSystems/SonikFileController_SJISx86.o \
./SonikFileSystems/SonikFileController_UTF16x64.o \
./SonikFileSystems/SonikFileController_UTF16x86.o \
./SonikFileSystems/SonikFileController_UTF8x64.o \
./SonikFileSystems/SonikFileController_UTF8x86.o \
./SonikFileSystems/SonikFileController_x64.o \
./SonikFileSystems/SonikFileController_x86.o \
./SonikFileSystems/SonikFileSystems.o 


# Each subdirectory must supply rules for building sources it contributes
SonikFileSystems/%.o: ../SonikFileSystems/%.cpp SonikFileSystems/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikFileSystems

clean-SonikFileSystems:
	-$(RM) ./SonikFileSystems/SonikFileController_SJISx64.d ./SonikFileSystems/SonikFileController_SJISx64.o ./SonikFileSystems/SonikFileController_SJISx86.d ./SonikFileSystems/SonikFileController_SJISx86.o ./SonikFileSystems/SonikFileController_UTF16x64.d ./SonikFileSystems/SonikFileController_UTF16x64.o ./SonikFileSystems/SonikFileController_UTF16x86.d ./SonikFileSystems/SonikFileController_UTF16x86.o ./SonikFileSystems/SonikFileController_UTF8x64.d ./SonikFileSystems/SonikFileController_UTF8x64.o ./SonikFileSystems/SonikFileController_UTF8x86.d ./SonikFileSystems/SonikFileController_UTF8x86.o ./SonikFileSystems/SonikFileController_x64.d ./SonikFileSystems/SonikFileController_x64.o ./SonikFileSystems/SonikFileController_x86.d ./SonikFileSystems/SonikFileController_x86.o ./SonikFileSystems/SonikFileSystems.d ./SonikFileSystems/SonikFileSystems.o

.PHONY: clean-SonikFileSystems

