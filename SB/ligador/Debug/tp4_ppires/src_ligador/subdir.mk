################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tp4_ppires/src_ligador/io.c \
../tp4_ppires/src_ligador/ligador.c \
../tp4_ppires/src_ligador/main.c \
../tp4_ppires/src_ligador/simbolos.c 

OBJS += \
./tp4_ppires/src_ligador/io.o \
./tp4_ppires/src_ligador/ligador.o \
./tp4_ppires/src_ligador/main.o \
./tp4_ppires/src_ligador/simbolos.o 

C_DEPS += \
./tp4_ppires/src_ligador/io.d \
./tp4_ppires/src_ligador/ligador.d \
./tp4_ppires/src_ligador/main.d \
./tp4_ppires/src_ligador/simbolos.d 


# Each subdirectory must supply rules for building sources it contributes
tp4_ppires/src_ligador/%.o: ../tp4_ppires/src_ligador/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


