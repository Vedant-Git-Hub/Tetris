CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c buff_op.c port.c
OBJ = $(patsubst %.c, build/%.o, $(SRC))

TARGET = tetris

all: $(TARGET)

# Final linking step
$(TARGET): $(OBJ)
	@$(CC) $(OBJ) -o $(TARGET)

# Rule to build object files inside build/
build/%.o: %.c | build
	@$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if missing
build:
	@mkdir -p build

run: $(TARGET)
	@clear
	@./$(TARGET)

clean:
	rm -rf build $(TARGET)

