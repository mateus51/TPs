################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tp3_ppires/src/expansor.c \
../tp3_ppires/src/io.c \
../tp3_ppires/src/macro.c \
../tp3_ppires/src/main.c 

OBJS += \
./tp3_ppires/src/expansor.o \
./tp3_ppires/src/io.o \
./tp3_ppires/src/macro.o \
./tp3_ppires/src/main.o 

C_DEPS += \
./tp3_ppires/src/expansor.d \
./tp3_ppires/src/io.d \
./tp3_ppires/src/macro.d \
./tp3_ppires/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
tp3_ppires/src/%.o: ../tp3_ppires/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


