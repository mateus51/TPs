################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tp_3/benchmark.c \
../tp_3/fb.c \
../tp_3/io.c \
../tp_3/main.c \
../tp_3/pd.c \
../tp_3/show.c 

OBJS += \
./tp_3/benchmark.o \
./tp_3/fb.o \
./tp_3/io.o \
./tp_3/main.o \
./tp_3/pd.o \
./tp_3/show.o 

C_DEPS += \
./tp_3/benchmark.d \
./tp_3/fb.d \
./tp_3/io.d \
./tp_3/main.d \
./tp_3/pd.d \
./tp_3/show.d 


# Each subdirectory must supply rules for building sources it contributes
tp_3/%.o: ../tp_3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


