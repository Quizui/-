################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../OpenALSource/open_al_interface.cpp 

CPP_DEPS += \
./OpenALSource/open_al_interface.d 

OBJS += \
./OpenALSource/open_al_interface.o 


# Each subdirectory must supply rules for building sources it contributes
OpenALSource/%.o: ../OpenALSource/%.cpp OpenALSource/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++17 -D_DEBUG -D__SONIK_x86_64__ -D_WIN64 -DHAVE_FSEEKO -DFLAC__NO_DLL -I"D:\MyLibrary\include\Audio\SoundSystem" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-OpenALSource

clean-OpenALSource:
	-$(RM) ./OpenALSource/open_al_interface.d ./OpenALSource/open_al_interface.o

.PHONY: clean-OpenALSource

