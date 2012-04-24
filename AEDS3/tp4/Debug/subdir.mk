################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../benchmark.o \
../fractal.o \
../grafo.o \
../io.o \
../main.o 

C_SRCS += \
../benchmark.c \
../fractal.c \
../grafo.c \
../io.c \
../main.c 

OBJS += \
./benchmark.o \
./fractal.o \
./grafo.o \
./io.o \
./main.o 

C_DEPS += \
./benchmark.d \
./fractal.d \
./grafo.d \
./io.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


