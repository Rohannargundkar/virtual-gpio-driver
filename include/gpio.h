//definitions/API
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_INPUT 0U
#define GPIO_OUTPUT 1U

#define GPIO_LOW 0U
#define GPIO_HIGH 1U

#define GPIO_MAX_PINS 8U

typedef struct
{
    uint32_t DATA;
    uint32_t DIRECTION;  
    uint32_t INT_ENABLE;
    uint32_t INT_STATUS;    
}GPIO_Registers;

void gpio_init(void);
int gpio_set_direction(uint8_t pin,uint8_t direction);
int gpio_write(uint8_t pin,uint8_t value);
int gpio_read(uint8_t pin);
int gpio_simulate_input(uint8_t pin,uint8_t value);
int gpio_enable_interrupt(uint8_t pin);
int gpio_disable_interrupt(uint8_t pin);
int gpio_get_interrupt_status(uint8_t pin);
void gpio_clear_interrupt(uint8_t pin);
void gpio_dump_registers(void);
uint32_t gpio_hw_read_data(void);
uint32_t gpio_hw_read_direction(void);
uint32_t gpio_hw_read_int_enable(void);
uint32_t gpio_hw_read_int_status(void);
#endif


