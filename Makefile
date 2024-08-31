CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bffc
SRC = bffc.c main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

time: $(TARGET)
	hyperfine -r 100 ./$(TARGET)

clean:
	@rm -f $(TARGET)
