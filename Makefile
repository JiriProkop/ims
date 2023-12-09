CC = g++
CFLAGS = -std=c++20 -Wall -Wextra
SRC_DIR = src/
OUTPUT_DIR = output/

crossroad: $(SRC_DIR)grid.o $(SRC_DIR)movable.o $(SRC_DIR)image.o $(SRC_DIR)simulation.o
	$(CC) $(CFLAGS) $(SRC_DIR)grid.o $(SRC_DIR)movable.o $(SRC_DIR)image.o $(SRC_DIR)simulation.o $(SRC_DIR)main.cpp -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)*.o $(OUTPUT_DIR)* crossroad
