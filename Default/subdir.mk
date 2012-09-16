################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../ClassTests.o 

CPP_SRCS += \
../ClassTests.cpp \
../battle.cpp \
../equipment.cpp \
../rpgUtils.cpp 

OBJS += \
./ClassTests.o \
./battle.o \
./equipment.o \
./rpgUtils.o 

CPP_DEPS += \
./ClassTests.d \
./battle.d \
./equipment.d \
./rpgUtils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


