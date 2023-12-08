################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Mixer/SonikAudio_Mixer.cpp 

CPP_DEPS += \
./Mixer/SonikAudio_Mixer.d 

OBJS += \
./Mixer/SonikAudio_Mixer.o 


# Each subdirectory must supply rules for building sources it contributes
Mixer/%.o: ../Mixer/%.cpp Mixer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_WIN64 -D__SONIK_x86_64__ -D_RELEASE -D__cplusplus=202002L -DHAVE_FSEEKO -DFLAC__NO_DLL -I"D:\MyLibrary\include\Audio\SoundSystem\Accesser" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Mixer

clean-Mixer:
	-$(RM) ./Mixer/SonikAudio_Mixer.d ./Mixer/SonikAudio_Mixer.o

.PHONY: clean-Mixer

