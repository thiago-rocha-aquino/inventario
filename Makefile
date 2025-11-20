

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = inventory
SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all: $(BUILD_DIR) $(DATA_DIR) $(TARGET)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(DATA_DIR):
	mkdir -p $(DATA_DIR)


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful! Run with: ./$(TARGET)"


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


run: all
	./$(TARGET)


clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete"

clean-all: clean
	rm -rf $(DATA_DIR)
	@echo "All files cleaned"


rebuild: clean all

.PHONY: all run clean clean-all rebuild
