################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../udpWrap/udpWrap.c 

C_DEPS += \
./udpWrap/udpWrap.d 

OBJS += \
./udpWrap/udpWrap.o 


# Each subdirectory must supply rules for building sources it contributes
udpWrap/%.o: ../udpWrap/%.c udpWrap/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-udpWrap

clean-udpWrap:
	-$(RM) ./udpWrap/udpWrap.d ./udpWrap/udpWrap.o

.PHONY: clean-udpWrap

