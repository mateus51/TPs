################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../benchmark.c \
../fb.c \
../io.c \
../main.c \
../pd.c \
../show.c 

OBJS += \
./benchmark.o \
./fb.o \
./io.o \
./main.o \
./pd.o \
./show.o 

C_DEPS += \
./benchmark.d \
./fb.d \
./io.d \
./main.d \
./pd.d \
./show.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


