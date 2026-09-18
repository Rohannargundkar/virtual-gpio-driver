CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

TARGET = gpio_sim
TEST_TARGET = test_gpio

SRC = main.c src/gpio.c

OBJ = main.o gpio.o


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


main.o: main.c include/gpio.h
	$(CC) $(CFLAGS) -c main.c -o main.o


gpio.o: src/gpio.c include/gpio.h
	$(CC) $(CFLAGS) -c src/gpio.c -o gpio.o


clean:
	rm -f $(OBJ) $(TARGET)

test:
	$(CC) $(CFLAGS) tests/test_gpio.c src/gpio.c -o $(TEST_TARGET)
	./$(TEST_TARGET)
