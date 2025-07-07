################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/hal_adc.c \
../Inc/hal_dma.c \
../Inc/hal_gpio.c \
../Inc/hal_i2c.c \
../Inc/hal_rcc.c \
../Inc/hal_spi.c \
../Inc/hal_systick.c \
../Inc/hal_uart.c 

OBJS += \
./Inc/hal_adc.o \
./Inc/hal_dma.o \
./Inc/hal_gpio.o \
./Inc/hal_i2c.o \
./Inc/hal_rcc.o \
./Inc/hal_spi.o \
./Inc/hal_systick.o \
./Inc/hal_uart.o 

C_DEPS += \
./Inc/hal_adc.d \
./Inc/hal_dma.d \
./Inc/hal_gpio.d \
./Inc/hal_i2c.d \
./Inc/hal_rcc.d \
./Inc/hal_spi.d \
./Inc/hal_systick.d \
./Inc/hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -DNUCLEO_F303RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/hal_adc.cyclo ./Inc/hal_adc.d ./Inc/hal_adc.o ./Inc/hal_adc.su ./Inc/hal_dma.cyclo ./Inc/hal_dma.d ./Inc/hal_dma.o ./Inc/hal_dma.su ./Inc/hal_gpio.cyclo ./Inc/hal_gpio.d ./Inc/hal_gpio.o ./Inc/hal_gpio.su ./Inc/hal_i2c.cyclo ./Inc/hal_i2c.d ./Inc/hal_i2c.o ./Inc/hal_i2c.su ./Inc/hal_rcc.cyclo ./Inc/hal_rcc.d ./Inc/hal_rcc.o ./Inc/hal_rcc.su ./Inc/hal_spi.cyclo ./Inc/hal_spi.d ./Inc/hal_spi.o ./Inc/hal_spi.su ./Inc/hal_systick.cyclo ./Inc/hal_systick.d ./Inc/hal_systick.o ./Inc/hal_systick.su ./Inc/hal_uart.cyclo ./Inc/hal_uart.d ./Inc/hal_uart.o ./Inc/hal_uart.su

.PHONY: clean-Inc

