################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tp4_ppires/src_montador/io.c \
../tp4_ppires/src_montador/main.c \
../tp4_ppires/src_montador/montador.c 

OBJS += \
./tp4_ppires/src_montador/io.o \
./tp4_ppires/src_montador/main.o \
./tp4_ppires/src_montador/montador.o 

C_DEPS += \
./tp4_ppires/src_montador/io.d \
./tp4_ppires/src_montador/main.d \
./tp4_ppires/src_montador/montador.d 


# Each subdirectory must supply rules for building sources it contributes
tp4_ppires/src_montador/%.o: ../tp4_ppires/src_montador/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


