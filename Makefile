CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bffc
SRC = bffc.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	@rm -f $(TARGET)
