################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikWorkThread/SonikWorkThreadEx.cpp \
../SonikWorkThread/SonikWorkThreadManagerEx.cpp 

CPP_DEPS += \
./SonikWorkThread/SonikWorkThreadEx.d \
./SonikWorkThread/SonikWorkThreadManagerEx.d 

OBJS += \
./SonikWorkThread/SonikWorkThreadEx.o \
./SonikWorkThread/SonikWorkThreadManagerEx.o 


# Each subdirectory must supply rules for building sources it contributes
SonikWorkThread/%.o: ../SonikWorkThread/%.cpp SonikWorkThread/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D__cplusplus=202002L -D_WIN64 -I"D:\MyLibrary\include\Thread" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikWorkThread

clean-SonikWorkThread:
	-$(RM) ./SonikWorkThread/SonikWorkThreadEx.d ./SonikWorkThread/SonikWorkThreadEx.o ./SonikWorkThread/SonikWorkThreadManagerEx.d ./SonikWorkThread/SonikWorkThreadManagerEx.o

.PHONY: clean-SonikWorkThread

