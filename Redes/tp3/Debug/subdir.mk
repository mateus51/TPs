################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../client.c \
../message.c \
../receiver.c \
../sender.c \
../server.c \
../sig_listener.c \
../time.c \
../tp_socket.c 

OBJS += \
./client.o \
./message.o \
./receiver.o \
./sender.o \
./server.o \
./sig_listener.o \
./time.o \
./tp_socket.o 

C_DEPS += \
./client.d \
./message.d \
./receiver.d \
./sender.d \
./server.d \
./sig_listener.d \
./time.d \
./tp_socket.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


