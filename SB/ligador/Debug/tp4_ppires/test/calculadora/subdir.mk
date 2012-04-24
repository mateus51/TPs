################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../tp4_ppires/test/calculadora/div.asm \
../tp4_ppires/test/calculadora/main.asm \
../tp4_ppires/test/calculadora/mult.asm \
../tp4_ppires/test/calculadora/pow.asm \
../tp4_ppires/test/calculadora/soma.asm \
../tp4_ppires/test/calculadora/sub.asm 

OBJS += \
./tp4_ppires/test/calculadora/div.o \
./tp4_ppires/test/calculadora/main.o \
./tp4_ppires/test/calculadora/mult.o \
./tp4_ppires/test/calculadora/pow.o \
./tp4_ppires/test/calculadora/soma.o \
./tp4_ppires/test/calculadora/sub.o 


# Each subdirectory must supply rules for building sources it contributes
tp4_ppires/test/calculadora/%.o: ../tp4_ppires/test/calculadora/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


