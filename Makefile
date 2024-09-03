CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bffc
SRC = src/bffc.c

all: $(TARGET)

test: $(SRC) src/test_bff.c
	$(CC) $(CFLAGS) -o $@ $^
	./test

$(TARGET): $(SRC) src/main.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) src/main.c

time: $(TARGET)
	hyperfine -r 100 ./$(TARGET)

clean:
	@rm -f $(TARGET) test
