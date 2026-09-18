# Register-Level Virtual GPIO Driver and Hardware Simulator in C

## Overview

This project implements a **virtual GPIO peripheral and device driver in C** that models the interaction between application software and hardware registers without requiring a physical microcontroller.

The project simulates GPIO configuration, digital input/output operations, external input signals, interrupt handling, register access, error conditions, and automated driver testing.

It is designed to demonstrate concepts used in **embedded C, device drivers, hardware abstraction, register-level programming, and virtual hardware modeling**.

---

## Objectives

* Understand how a device driver interacts with hardware registers.
* Model a GPIO peripheral using C structures and bit manipulation.
* Separate the application layer from the driver layer.
* Simulate external hardware signals on GPIO input pins.
* Simulate GPIO interrupts.
* Implement error handling for invalid hardware operations.
* Build and test the driver using GCC and Make.
* Develop an automated test suite for driver validation.

---

## System Architecture

```text
                 Application / Test Program
                          │
                          ▼
                 GPIO Driver API
                          │
                          ▼
              Virtual GPIO Registers
          ┌──────────┬──────────┬──────────┐
          │          │          │          │
         DATA     DIRECTION  INT_ENABLE INT_STATUS
          │          │          │          │
          └──────────┴──────────┴──────────┘
                          │
                          ▼
                  Virtual GPIO Hardware
                          │
                    Virtual GPIO Pins
```

The application interacts with the GPIO driver through APIs. The driver manipulates the virtual register set to model hardware behavior.

---

## Features

### GPIO Configuration

* Configure individual GPIO pins as INPUT or OUTPUT.
* Support for 8 virtual GPIO pins.
* Validation of pin numbers and configuration values.

### GPIO Output

* Write HIGH or LOW to an output GPIO.
* Prevent writing to pins configured as INPUT.

### GPIO Input Simulation

* Simulate an external HIGH or LOW signal.
* Read the resulting GPIO state through the driver.

### Interrupt Simulation

* Enable interrupts for individual GPIO pins.
* Generate a virtual interrupt when an external input event occurs.
* Read interrupt status.
* Clear interrupt status.

### Virtual Hardware Registers

The simulated GPIO peripheral contains four registers:

| Address | Register     | Description                     |
| ------- | ------------ | ------------------------------- |
| `0x00`  | `DATA`       | GPIO pin data                   |
| `0x04`  | `DIRECTION`  | GPIO input/output configuration |
| `0x08`  | `INT_ENABLE` | Interrupt enable bits           |
| `0x0C`  | `INT_STATUS` | Interrupt status bits           |

Each GPIO pin is represented by one bit in the corresponding register.

---

## Bit-Level Register Model

For example, configuring GPIO0 as an output sets bit 0 of the `DIRECTION` register:

```text
DIRECTION = 00000001
           └───────┘
              GPIO0
```

Writing GPIO0 HIGH sets bit 0 of the `DATA` register:

```text
DATA = 00000001
       └───────┘
          GPIO0
```

This models the type of bit-level register manipulation commonly used in embedded systems.

---

## Driver API

The driver provides APIs including:

```c
gpio_init();

gpio_set_direction();

gpio_write();

gpio_read();

gpio_simulate_input();

gpio_enable_interrupt();

gpio_disable_interrupt();

gpio_get_interrupt_status();

gpio_clear_interrupt();

gpio_dump_registers();
```

Additional hardware-level register access functions are provided for inspecting the virtual peripheral state.

---

## Error Handling

The driver validates hardware operations and returns error codes for invalid requests.

| Error Code | Meaning                |
| ---------- | ---------------------- |
| `0`        | Success                |
| `-1`       | Invalid GPIO pin       |
| `-2`       | Invalid GPIO operation |
| `-3`       | Invalid GPIO direction |

Example:

```c
gpio_write(1, GPIO_HIGH);
```

If GPIO1 is configured as an INPUT, the driver rejects the operation instead of modifying the virtual hardware state.

---

## Automated Testing

A separate test application is provided in:

```text
tests/test_gpio.c
```

The test suite verifies:

* GPIO output configuration
* GPIO HIGH write
* GPIO HIGH read
* GPIO input configuration
* External input simulation
* Input reading
* Interrupt enabling
* Interrupt generation
* Interrupt clearing
* Invalid GPIO pin handling
* Invalid write operation
* Invalid direction handling

### Test Result

```text
=================================
 TEST SUMMARY
=================================
Tests passed : 12
Tests failed : 0
=================================
ALL TESTS PASSED
```

---

## Project Structure

```text
virtual-gpio-driver/
│
├── main.c
├── Makefile
├── README.md
├── .gitignore
│
├── include/
│   └── gpio.h
│
├── src/
│   └── gpio.c
│
├── tests/
│   └── test_gpio.c
│
└── docs/
    └── architecture.md
```

### Directory Description

* `main.c` — Demonstration application for the virtual GPIO driver.
* `include/gpio.h` — GPIO register definitions, constants, and driver API declarations.
* `src/gpio.c` — GPIO driver and virtual hardware implementation.
* `tests/test_gpio.c` — Automated driver test suite.
* `Makefile` — Build and test automation.
* `docs/architecture.md` — System architecture documentation.

---

## Building the Project

Clone the repository and enter the project directory:

```bash
git clone <repository-url>
cd virtual-gpio-driver
```

Build the simulator:

```bash
make
```

Run the simulator:

```bash
./gpio_sim
```

Run the automated tests:

```bash
make test
```

Clean generated build files:

```bash
make clean
```

---

## Technologies and Concepts

### Programming

* C
* Structures
* Functions
* Header/source separation
* Error handling
* Bit manipulation

### Embedded Systems

* GPIO peripherals
* Hardware registers
* Register maps
* Hardware abstraction
* Interrupt concepts
* Input/output configuration
* Memory-mapped I/O concepts

### Development Environment

* Linux
* GCC
* Make
* Git
* GitHub

### Testing

* Automated test cases
* Positive testing
* Negative testing
* Driver validation

---

## Skills Demonstrated

This project demonstrates practical understanding of:

* Embedded C programming
* Device-driver architecture
* Register-level programming concepts
* Hardware/software interface modeling
* Bitwise operations
* GPIO peripheral behavior
* Interrupt handling concepts
* Modular C project organization
* Linux-based development
* Build systems using Make
* Automated software testing
* Git and GitHub workflow

---

## Future Improvements

Possible extensions include:

* Timer peripheral simulation
* UART peripheral simulation
* SPI/I2C peripheral models
* Interrupt controller abstraction
* Multiple virtual peripherals
* Memory-mapped address space simulation
* Hardware register access layer
* Peripheral event scheduler
* Python-based test automation
* Virtual MCU platform combining multiple peripherals

---

## Author

**Rohan Nargundkar**

Electronics and Communication Engineering

---

## Project Purpose

This project was developed as a practical exercise in **embedded software, device drivers, and virtual hardware modeling**, with the objective of understanding how software interfaces with hardware at the register level.
