#include <stdio.h>
#include "gpio.h"

int main(void)
{
    int result;
    int value;

    printf("=================================\n");
    printf(" Virtual GPIO Driver Simulator\n");
    printf("=================================\n\n");

    gpio_init();

    /* ---------------- OUTPUT TEST ---------------- */

    printf("[TEST] Configure GPIO0 as OUTPUT\n");

    result = gpio_set_direction(0, GPIO_OUTPUT);

    if (result == 0)
        printf("PASS\n\n");
    else
    {
        printf("FAIL\n\n");
        return 1;
    }

    printf("[TEST] Write GPIO0 HIGH\n");

    result = gpio_write(0, GPIO_HIGH);

    if (result == 0)
        printf("GPIO0 = HIGH\nPASS\n\n");
    else
    {
        printf("FAIL\n\n");
        return 1;
    }

    printf("[TEST] Read GPIO0\n");

    value = gpio_read(0);

    if (value == GPIO_HIGH)
        printf("GPIO0 read value = HIGH\nPASS\n\n");
    else
    {
        printf("FAIL\n\n");
        return 1;
    }

    /* ---------------- INPUT TEST ---------------- */

    printf("[TEST] Configure GPIO1 as INPUT\n");

    result = gpio_set_direction(1, GPIO_INPUT);

    if (result == 0)
        printf("PASS\n\n");
    else
    {
        printf("FAIL\n\n");
        return 1;
    }

printf("[TEST] Simulate external HIGH signal on GPIO1\n");

result = gpio_simulate_input(1, GPIO_HIGH);

if (result == 0)
{
    printf("GPIO1 external signal = HIGH\n");
    printf("PASS\n\n");
}
else
{
    printf("gpio_simulate_input() returned %d\n", result);
    printf("FAIL\n\n");
    return 1;
}

printf("[TEST] Read GPIO1\n");

value = gpio_read(1);

printf("DEBUG: GPIO1 read returned %d\n", value);

if (value == GPIO_HIGH)
{
    printf("GPIO1 read value = HIGH\n");
    printf("PASS\n\n");
}
else
{
    printf("GPIO1 read value = LOW\n");
    printf("FAIL\n\n");
    return 1;
}

printf("[TEST] Enable interrupt on GPIO1\n");

result = gpio_enable_interrupt(1);

if (result == 0)
{
    printf("PASS\n\n");
}
else
{
    printf("FAIL\n\n");
    return 1;
}

printf("[TEST] Generate GPIO1 interrupt\n");

result = gpio_simulate_input(1, GPIO_LOW);

if (result == 0)
{
    printf("External GPIO1 event generated\n");
    printf("PASS\n\n");
}
else
{
    printf("FAIL\n\n");
    return 1;
}

printf("[TEST] Check GPIO1 interrupt status\n");

value = gpio_get_interrupt_status(1);

if (value == 1)
{
    printf("GPIO1 interrupt status = ACTIVE\n");
    printf("PASS\n\n");
}
else
{
    printf("GPIO1 interrupt status = INACTIVE\n");
    printf("FAIL\n\n");
    return 1;
}

printf("[TEST] Clear GPIO1 interrupt\n");

gpio_clear_interrupt(1);

value = gpio_get_interrupt_status(1);

if (value == 0)
{
    printf("GPIO1 interrupt status = CLEARED\n");
    printf("PASS\n\n");
}
else
{
    printf("GPIO interrupt status = STILL ACTIVE\n");    
    printf("FAIL\n\n");
    return 1;
}

printf("=================================\n");
printf(" GPIO INPUT/OUTPUT TEST COMPLETE\n");
printf("=================================\n");

printf("[TEST] Invalid GPIO pin\n");

result = gpio_set_direction(8, GPIO_OUTPUT);

if (result == -1)
{
    printf("Invalid pin rejected correctly\n");
    printf("PASS\n\n");
}
else
{
    printf("Invalid pin was accepted\n");
    printf("FAIL\n\n");
    return 1;
}


printf("[TEST] Write to INPUT pin\n");

result = gpio_write(1, GPIO_HIGH);

if (result == -2)
{
    printf("Write to INPUT rejected correctly\n");
    printf("PASS\n\n");
}
else
{
    printf("Write to INPUT was accepted\n");
    printf("FAIL\n\n");
    return 1;
}


printf("[TEST] Invalid GPIO direction\n");

result = gpio_set_direction(2, 5);

if (result == -3)
{
    printf("Invalid direction rejected correctly\n");
    printf("PASS\n\n");
}
else
{
    printf("Invalid direction was accepted\n");
    printf("FAIL\n\n");
    return 1;
}
printf("[TEST] Dump virtual GPIO registers\n");

gpio_dump_registers();

printf("[TEST] Direct virtual hardware register access\n");

printf("DATA       = 0x%08X\n", gpio_hw_read_data());
printf("DIRECTION  = 0x%08X\n", gpio_hw_read_direction());
printf("INT_ENABLE = 0x%08X\n", gpio_hw_read_int_enable());
printf("INT_STATUS = 0x%08X\n", gpio_hw_read_int_status());

printf("Register access PASS\n\n");
printf("=================================\n");
printf(" GPIO DRIVER TEST COMPLETE\n");
printf("=================================\n");

return 0;
}
