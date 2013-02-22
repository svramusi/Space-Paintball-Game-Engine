################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BaseVisitor.cpp \
../src/CollectGameState.cpp \
../src/Game.cpp \
../src/GameState.cpp \
../src/GameVisitor.cpp \
../src/NavigationVisitor.cpp \
../src/TestCollectGameState.cpp \
../src/Visitable.cpp 

OBJS += \
./src/BaseVisitor.o \
./src/CollectGameState.o \
./src/Game.o \
./src/GameState.o \
./src/GameVisitor.o \
./src/NavigationVisitor.o \
./src/TestCollectGameState.o \
./src/Visitable.o 

CPP_DEPS += \
./src/BaseVisitor.d \
./src/CollectGameState.d \
./src/Game.d \
./src/GameState.d \
./src/GameVisitor.d \
./src/NavigationVisitor.d \
./src/TestCollectGameState.d \
./src/Visitable.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.7 -I/usr/include/c++/4.7/backward -I/usr/local/include -I"/home/amarppatel/workspace/Space-Paintball-Game-Engine/gameassets/includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


