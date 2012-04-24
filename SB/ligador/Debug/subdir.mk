################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../io.c \
../ligador.c \
../main.c \
../simbolos.c 

OBJ_SRCS += \
../calculo.obj \
../div.obj \
../main.obj \
../mult.obj \
../pow.obj \
../soma.obj \
../sub.obj 

OBJS += \
./io.o \
./ligador.o \
./main.o \
./simbolos.o 

C_DEPS += \
./io.d \
./ligador.d \
./main.d \
./simbolos.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


