################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DllFunction/DllMain.cpp 

CPP_DEPS += \
./DllFunction/DllMain.d 

OBJS += \
./DllFunction/DllMain.o 


# Each subdirectory must supply rules for building sources it contributes
DllFunction/%.o: ../DllFunction/%.cpp DllFunction/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_WIN64 -D__SONIK_x86_64__ -D_DEBUG -D__SONIK_DLL_OUTPUT_DEFINE__ -DHAVE_FSEEKO -DFLAC__NO_DLL -I"D:\MyLibrary\include\Audio\SoundSystem" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-DllFunction

clean-DllFunction:
	-$(RM) ./DllFunction/DllMain.d ./DllFunction/DllMain.o

.PHONY: clean-DllFunction

