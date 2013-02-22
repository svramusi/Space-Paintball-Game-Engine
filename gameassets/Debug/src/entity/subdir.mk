################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/entity/Astronaut.cpp \
../src/entity/Character.cpp \
../src/entity/Entity.cpp \
../src/entity/OuterSpace.cpp \
../src/entity/Place.cpp \
../src/entity/Planet.cpp \
../src/entity/Prop.cpp \
../src/entity/SpaceShip.cpp \
../src/entity/SuperHero.cpp 

OBJS += \
./src/entity/Astronaut.o \
./src/entity/Character.o \
./src/entity/Entity.o \
./src/entity/OuterSpace.o \
./src/entity/Place.o \
./src/entity/Planet.o \
./src/entity/Prop.o \
./src/entity/SpaceShip.o \
./src/entity/SuperHero.o 

CPP_DEPS += \
./src/entity/Astronaut.d \
./src/entity/Character.d \
./src/entity/Entity.d \
./src/entity/OuterSpace.d \
./src/entity/Place.d \
./src/entity/Planet.d \
./src/entity/Prop.d \
./src/entity/SpaceShip.d \
./src/entity/SuperHero.d 


# Each subdirectory must supply rules for building sources it contributes
src/entity/%.o: ../src/entity/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.7 -I/usr/include/c++/4.7/backward -I/usr/local/include -I"/home/amarppatel/workspace/Space-Paintball-Game-Engine/gameassets/includes" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


