################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../automata_constructor.o \
../io.o \
../main.o 

C_SRCS += \
../automata_constructor.c \
../io.c \
../main.c \
../tp1-2.c 

OBJS += \
./automata_constructor.o \
./io.o \
./main.o \
./tp1-2.o 

C_DEPS += \
./automata_constructor.d \
./io.d \
./main.d \
./tp1-2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


