//virtual GPIO hardware + driver
#include "gpio.h"
#include <stdio.h>

static GPIO_Registers gpio_regs;

void  gpio_init(void)
{
    gpio_regs.DATA = 0U;
    gpio_regs.DIRECTION = 0U;
    gpio_regs.INT_ENABLE = 0U;
    gpio_regs.INT_STATUS = 0U;    
}

int gpio_set_direction(uint8_t pin, uint8_t direction)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    if (direction == GPIO_OUTPUT)
    {
        gpio_regs.DIRECTION |= (1U << pin);
    }
    else if (direction == GPIO_INPUT)
    {
        gpio_regs.DIRECTION &= ~(1U << pin);
    }
    else
    {
        return -3;           
    }
    return 0;
}

int gpio_write(uint8_t pin, uint8_t value)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    /* GPIO must be configured as OUTPUT */
    if ((gpio_regs.DIRECTION & (1U << pin)) == 0U)
    {
        return -2;
    }

    if (value == GPIO_HIGH)
    {
        gpio_regs.DATA |= (1U << pin);
    }
    else
    {
        gpio_regs.DATA &= ~(1U << pin);
    }

    return 0;
}

int gpio_read(uint8_t pin)
{
    if(pin >= GPIO_MAX_PINS)
    {
        return -1;    
    }
    
    return(gpio_regs.DATA >> pin) & 1U;
}

int gpio_simulate_input(uint8_t pin, uint8_t value)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    /* Pin must be configured as INPUT */
    if ((gpio_regs.DIRECTION & (1U << pin)) != 0U)
    {
        return -2;
    }

    /* Update virtual input data */
    if (value == GPIO_HIGH)
    {
        gpio_regs.DATA |= (1U << pin);
    }
    else
    {
        gpio_regs.DATA &= ~(1U << pin);
    }

    /* Generate interrupt if enabled */
    if ((gpio_regs.INT_ENABLE & (1U << pin)) != 0U)
    {
        gpio_regs.INT_STATUS |= (1U << pin);
    }

    return 0;
}

int gpio_enable_interrupt(uint8_t pin)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    gpio_regs.INT_ENABLE |= (1U << pin);

    return 0;
}


int gpio_disable_interrupt(uint8_t pin)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    gpio_regs.INT_ENABLE &= ~(1U << pin);

    return 0;
}


int gpio_get_interrupt_status(uint8_t pin)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return -1;
    }

    return (gpio_regs.INT_STATUS >> pin) & 1U;
}


void gpio_clear_interrupt(uint8_t pin)
{
    if (pin >= GPIO_MAX_PINS)
    {
        return;
    }

    gpio_regs.INT_STATUS &= ~(1U << pin);
}

void gpio_dump_registers(void)
{
    printf("\n========== GPIO REGISTERS ==========\n");
    printf("DATA       : 0x%08X\n", gpio_regs.DATA);
    printf("DIRECTION  : 0x%08X\n", gpio_regs.DIRECTION);
    printf("INT_ENABLE : 0x%08X\n", gpio_regs.INT_ENABLE);
    printf("INT_STATUS : 0x%08X\n", gpio_regs.INT_STATUS);
    printf("====================================\n\n");
}


uint32_t gpio_hw_read_data(void)
{
    return gpio_regs.DATA;
}

uint32_t gpio_hw_read_direction(void)
{
    return gpio_regs.DIRECTION;
}

uint32_t gpio_hw_read_int_enable(void)
{
    return gpio_regs.INT_ENABLE;
}

uint32_t gpio_hw_read_int_status(void)
{
    return gpio_regs.INT_STATUS;
}










