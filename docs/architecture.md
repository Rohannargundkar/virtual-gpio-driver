# System Architecture

## Overview

The Virtual GPIO Driver and Hardware Simulator models a simple GPIO peripheral entirely in software using C.

The project separates the application/test layer, GPIO driver layer, and virtual hardware/register layer.

## Architecture

```text
+-----------------------------+
|     Application / Tests     |
+--------------+--------------+
               |
               v
+-----------------------------+
|       GPIO Driver API       |
|-----------------------------|
| gpio_init()                 |
| gpio_set_direction()        |
| gpio_write()                |
| gpio_read()                 |
| gpio_simulate_input()       |
| gpio_enable_interrupt()     |
| gpio_clear_interrupt()      |
+--------------+--------------+
               |
               v
+-----------------------------+
|     Virtual GPIO Hardware   |
|-----------------------------|
| DATA                        |
| DIRECTION                   |
| INT_ENABLE                  |
| INT_STATUS                  |
+--------------+--------------+
               |
               v
+-----------------------------+
|       Virtual GPIO Pins     |
+-----------------------------+
