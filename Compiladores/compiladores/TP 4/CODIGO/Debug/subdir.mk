################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../main.o \
../quadruplas.o \
../tabela.o 

CPP_SRCS += \
../main.cpp \
../quadruplas.cpp \
../tabela.cpp \
../tradutor.cpp 

OBJS += \
./main.o \
./quadruplas.o \
./tabela.o \
./tradutor.o 

CPP_DEPS += \
./main.d \
./quadruplas.d \
./tabela.d \
./tradutor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


