CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bffc
SRC = src/bffc.c src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

time: $(TARGET)
	hyperfine -r 100 ./$(TARGET)

clean:
	@rm -f $(TARGET)
