################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../espacial.o \
../io.o \
../lista.o \
../main.o \
../temporal.o \
../video.o 

C_SRCS += \
../espacial.c \
../io.c \
../lista.c \
../main.c \
../statistics.c \
../temporal.c \
../video.c 

OBJS += \
./espacial.o \
./io.o \
./lista.o \
./main.o \
./statistics.o \
./temporal.o \
./video.o 

C_DEPS += \
./espacial.d \
./io.d \
./lista.d \
./main.d \
./statistics.d \
./temporal.d \
./video.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


