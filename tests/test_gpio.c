#include <stdio.h>
#include "gpio.h"

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(condition, message)                 \
    do                                           \
    {                                            \
        if (condition)                           \
        {                                        \
            printf("[PASS] %s\n", message);      \
            tests_passed++;                     \
        }                                        \
        else                                     \
        {                                        \
            printf("[FAIL] %s\n", message);      \
            tests_failed++;                     \
        }                                        \
    } while (0)


int main(void)
{
    printf("\n");
    printf("=================================\n");
    printf(" GPIO DRIVER AUTOMATED TESTS\n");
    printf("=================================\n\n");

    gpio_init();

    /* Test 1: Configure GPIO0 as OUTPUT */
    TEST(
        gpio_set_direction(0, GPIO_OUTPUT) == 0,
        "Configure GPIO0 as OUTPUT"
    );

    /* Test 2: Write GPIO0 HIGH */
    TEST(
        gpio_write(0, GPIO_HIGH) == 0,
        "Write GPIO0 HIGH"
    );

    /* Test 3: Read GPIO0 */
    TEST(
        gpio_read(0) == GPIO_HIGH,
        "Read GPIO0 HIGH"
    );

    /* Test 4: Configure GPIO1 as INPUT */
    TEST(
        gpio_set_direction(1, GPIO_INPUT) == 0,
        "Configure GPIO1 as INPUT"
    );

    /* Test 5: Simulate external HIGH */
    TEST(
        gpio_simulate_input(1, GPIO_HIGH) == 0,
        "Simulate external HIGH on GPIO1"
    );

    /* Test 6: Read GPIO1 */
    TEST(
        gpio_read(1) == GPIO_HIGH,
        "Read GPIO1 HIGH"
    );

    /* Test 7: Enable interrupt */
    TEST(
        gpio_enable_interrupt(1) == 0,
        "Enable interrupt on GPIO1"
    );

    /* Test 8: Generate interrupt */
    gpio_simulate_input(1, GPIO_LOW);

    TEST(
        gpio_get_interrupt_status(1) == 1,
        "GPIO1 interrupt generated"
    );

    /* Test 9: Clear interrupt */
    gpio_clear_interrupt(1);

    TEST(
        gpio_get_interrupt_status(1) == 0,
        "GPIO1 interrupt cleared"
    );

    /* Test 10: Invalid pin */
    TEST(
        gpio_set_direction(8, GPIO_OUTPUT) == -1,
        "Reject invalid GPIO pin"
    );

    /* Test 11: Write to input */
    TEST(
        gpio_write(1, GPIO_HIGH) == -2,
        "Reject write to INPUT pin"
    );

    /* Test 12: Invalid direction */
    TEST(
        gpio_set_direction(2, 5) == -3,
        "Reject invalid GPIO direction"
    );

    printf("\n=================================\n");
    printf(" TEST SUMMARY\n");
    printf("=================================\n");
    printf("Tests passed : %d\n", tests_passed);
    printf("Tests failed : %d\n", tests_failed);
    printf("=================================\n");

    if (tests_failed == 0)
    {
        printf("ALL TESTS PASSED\n");
        return 0;
    }

    printf("SOME TESTS FAILED\n");
    return 1;
}
