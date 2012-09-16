################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Beings/Being.cpp \
../Beings/Humanoid.cpp \
../Beings/character.cpp \
../Beings/enemy.cpp 

OBJS += \
./Beings/Being.o \
./Beings/Humanoid.o \
./Beings/character.o \
./Beings/enemy.o 

CPP_DEPS += \
./Beings/Being.d \
./Beings/Humanoid.d \
./Beings/character.d \
./Beings/enemy.d 


# Each subdirectory must supply rules for building sources it contributes
Beings/%.o: ../Beings/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


