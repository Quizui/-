################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Allocator/SonikAllocateExAccessCall.cpp \
../Allocator/SonikAllocateFreeBlock.cpp \
../Allocator/SonikBaundaryBlock.cpp \
../Allocator/SonikBaundaryTagAllocateEx.cpp \
../Allocator/SonikFreeBlockManager.cpp 

OBJS += \
./Allocator/SonikAllocateExAccessCall.o \
./Allocator/SonikAllocateFreeBlock.o \
./Allocator/SonikBaundaryBlock.o \
./Allocator/SonikBaundaryTagAllocateEx.o \
./Allocator/SonikFreeBlockManager.o 

CPP_DEPS += \
./Allocator/SonikAllocateExAccessCall.d \
./Allocator/SonikAllocateFreeBlock.d \
./Allocator/SonikBaundaryBlock.d \
./Allocator/SonikBaundaryTagAllocateEx.d \
./Allocator/SonikFreeBlockManager.d 


# Each subdirectory must supply rules for building sources it contributes
Allocator/%.o: ../Allocator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201703L -D_WIN32 -D_RELEASE -I"D:\MyLibrary\include\Allocate" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


