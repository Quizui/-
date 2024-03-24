################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Player/SonikAudioPlayer.cpp \
../Player/SonikAudioPlayer_ControlData.cpp 

CPP_DEPS += \
./Player/SonikAudioPlayer.d \
./Player/SonikAudioPlayer_ControlData.d 

OBJS += \
./Player/SonikAudioPlayer.o \
./Player/SonikAudioPlayer_ControlData.o 


# Each subdirectory must supply rules for building sources it contributes
Player/%.o: ../Player/%.cpp Player/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_WIN64 -D__SONIK_x86_64__ -D_RELEASE -D__cplusplus=202002L -DHAVE_FSEEKO -DFLAC__NO_DLL -I"D:\MyLibrary\include\Audio\SoundSystem\Player" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Player

clean-Player:
	-$(RM) ./Player/SonikAudioPlayer.d ./Player/SonikAudioPlayer.o ./Player/SonikAudioPlayer_ControlData.d ./Player/SonikAudioPlayer_ControlData.o

.PHONY: clean-Player

