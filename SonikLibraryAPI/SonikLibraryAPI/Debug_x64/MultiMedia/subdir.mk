################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MultiMedia/SonikMM_AudioInfoImple.cpp \
../MultiMedia/SonikMultiMediaInterface.cpp 

CPP_DEPS += \
./MultiMedia/SonikMM_AudioInfoImple.d \
./MultiMedia/SonikMultiMediaInterface.d 

OBJS += \
./MultiMedia/SonikMM_AudioInfoImple.o \
./MultiMedia/SonikMultiMediaInterface.o 


# Each subdirectory must supply rules for building sources it contributes
MultiMedia/%.o: ../MultiMedia/%.cpp MultiMedia/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MultiMedia

clean-MultiMedia:
	-$(RM) ./MultiMedia/SonikMM_AudioInfoImple.d ./MultiMedia/SonikMM_AudioInfoImple.o ./MultiMedia/SonikMultiMediaInterface.d ./MultiMedia/SonikMultiMediaInterface.o

.PHONY: clean-MultiMedia

