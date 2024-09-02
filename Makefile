CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bffc
SRC = src/bffc.c

all: $(TARGET) src/main.h

test: $(SRC) src/test_bff.c
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

time: $(TARGET)
	hyperfine -r 100 ./$(TARGET)

clean:
	@rm -f $(TARGET) test
