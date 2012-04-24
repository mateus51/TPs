################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../benchmark.c \
../eleicao.c \
../enumerations.c \
../io.c \
../kemeny_young.c \
../main.c 

OBJS += \
./benchmark.o \
./eleicao.o \
./enumerations.o \
./io.o \
./kemeny_young.o \
./main.o 

C_DEPS += \
./benchmark.d \
./eleicao.d \
./enumerations.d \
./io.d \
./kemeny_young.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


