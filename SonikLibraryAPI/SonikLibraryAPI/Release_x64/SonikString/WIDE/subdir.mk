################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikString/WIDE/SonikString_WIDE.cpp 

CPP_DEPS += \
./SonikString/WIDE/SonikString_WIDE.d 

OBJS += \
./SonikString/WIDE/SonikString_WIDE.o 


# Each subdirectory must supply rules for building sources it contributes
SonikString/WIDE/%.o: ../SonikString/WIDE/%.cpp SonikString/WIDE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_RELEASE -D__cplusplus=202002L -D_WIN64 -I./WIDE -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikString-2f-WIDE

clean-SonikString-2f-WIDE:
	-$(RM) ./SonikString/WIDE/SonikString_WIDE.d ./SonikString/WIDE/SonikString_WIDE.o

.PHONY: clean-SonikString-2f-WIDE

