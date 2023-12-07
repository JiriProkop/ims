CC = g++
CFLAGS = -std=c++20 -Wall -Wextra
SRC_DIR = src/

crossroad: $(SRC_DIR)grid.o $(SRC_DIR)movable.o
	$(CC) $(CFLAGS) $(SRC_DIR)grid.o $(SRC_DIR)movable.o $(SRC_DIR)main.cpp -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)*.o crossroad
