SRC_DIR=./src
BIN_DIR=./bin
TARGET=$(BIN_DIR)/main.out

CC=gcc
CFLAGS=-o $(TARGET) -I./headers -lm

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRC_DIR)/*.c
	$(CC) $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
