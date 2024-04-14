################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikFileSystems/SonikFileController.cpp \
../SonikFileSystems/SonikFileSystems.cpp 

CPP_DEPS += \
./SonikFileSystems/SonikFileController.d \
./SonikFileSystems/SonikFileSystems.d 

OBJS += \
./SonikFileSystems/SonikFileController.o \
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
	-$(RM) ./SonikFileSystems/SonikFileController.d ./SonikFileSystems/SonikFileController.o ./SonikFileSystems/SonikFileSystems.d ./SonikFileSystems/SonikFileSystems.o

.PHONY: clean-SonikFileSystems

