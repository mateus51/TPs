################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../TADeleicao.o \
../io.o \
../kemeny_young.o \
../main.o 

C_SRCS += \
../TADeleicao.c \
../io.c \
../kemeny_young.c \
../main.c 

OBJS += \
./TADeleicao.o \
./io.o \
./kemeny_young.o \
./main.o 

C_DEPS += \
./TADeleicao.d \
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


