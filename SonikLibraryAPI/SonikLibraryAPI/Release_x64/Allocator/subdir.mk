################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Allocator/SonikAllocateExAccessCall.cpp \
../Allocator/SonikAllocateExAccessCall_x64.cpp \
../Allocator/SonikAllocateFreeBlock.cpp \
../Allocator/SonikAllocateFreeBlock_x64.cpp \
../Allocator/SonikAllocateRawExAccessCall.cpp \
../Allocator/SonikAllocateRawExAccessCall_x64.cpp \
../Allocator/SonikBaundaryBlock.cpp \
../Allocator/SonikBaundaryBlock_x64.cpp \
../Allocator/SonikBaundaryTagAllocateEx.cpp \
../Allocator/SonikBaundaryTagAllocateEx_x64.cpp \
../Allocator/SonikFreeBlockManager.cpp \
../Allocator/SonikFreeBlockManager_x64.cpp 

CPP_DEPS += \
./Allocator/SonikAllocateExAccessCall.d \
./Allocator/SonikAllocateExAccessCall_x64.d \
./Allocator/SonikAllocateFreeBlock.d \
./Allocator/SonikAllocateFreeBlock_x64.d \
./Allocator/SonikAllocateRawExAccessCall.d \
./Allocator/SonikAllocateRawExAccessCall_x64.d \
./Allocator/SonikBaundaryBlock.d \
./Allocator/SonikBaundaryBlock_x64.d \
./Allocator/SonikBaundaryTagAllocateEx.d \
./Allocator/SonikBaundaryTagAllocateEx_x64.d \
./Allocator/SonikFreeBlockManager.d \
./Allocator/SonikFreeBlockManager_x64.d 

OBJS += \
./Allocator/SonikAllocateExAccessCall.o \
./Allocator/SonikAllocateExAccessCall_x64.o \
./Allocator/SonikAllocateFreeBlock.o \
./Allocator/SonikAllocateFreeBlock_x64.o \
./Allocator/SonikAllocateRawExAccessCall.o \
./Allocator/SonikAllocateRawExAccessCall_x64.o \
./Allocator/SonikBaundaryBlock.o \
./Allocator/SonikBaundaryBlock_x64.o \
./Allocator/SonikBaundaryTagAllocateEx.o \
./Allocator/SonikBaundaryTagAllocateEx_x64.o \
./Allocator/SonikFreeBlockManager.o \
./Allocator/SonikFreeBlockManager_x64.o 


# Each subdirectory must supply rules for building sources it contributes
Allocator/%.o: ../Allocator/%.cpp Allocator/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_RELEASE -D__cplusplus=202002L -D__SONIK_x86_64__=1 -D_WIN64 -I"D:\MyLibrary\include\Allocate" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Allocator

clean-Allocator:
	-$(RM) ./Allocator/SonikAllocateExAccessCall.d ./Allocator/SonikAllocateExAccessCall.o ./Allocator/SonikAllocateExAccessCall_x64.d ./Allocator/SonikAllocateExAccessCall_x64.o ./Allocator/SonikAllocateFreeBlock.d ./Allocator/SonikAllocateFreeBlock.o ./Allocator/SonikAllocateFreeBlock_x64.d ./Allocator/SonikAllocateFreeBlock_x64.o ./Allocator/SonikAllocateRawExAccessCall.d ./Allocator/SonikAllocateRawExAccessCall.o ./Allocator/SonikAllocateRawExAccessCall_x64.d ./Allocator/SonikAllocateRawExAccessCall_x64.o ./Allocator/SonikBaundaryBlock.d ./Allocator/SonikBaundaryBlock.o ./Allocator/SonikBaundaryBlock_x64.d ./Allocator/SonikBaundaryBlock_x64.o ./Allocator/SonikBaundaryTagAllocateEx.d ./Allocator/SonikBaundaryTagAllocateEx.o ./Allocator/SonikBaundaryTagAllocateEx_x64.d ./Allocator/SonikBaundaryTagAllocateEx_x64.o ./Allocator/SonikFreeBlockManager.d ./Allocator/SonikFreeBlockManager.o ./Allocator/SonikFreeBlockManager_x64.d ./Allocator/SonikFreeBlockManager_x64.o

.PHONY: clean-Allocator

