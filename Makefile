CC = g++
CFLAGS = -std=c++20 -Wall -Wextra
SRC_DIR = src/
OUTPUT_DIR = output/

run: $(SRC_DIR)grid.o $(SRC_DIR)movable.o $(SRC_DIR)image.o $(SRC_DIR)simulation.o $(SRC_DIR)arguments.o
	$(CC) $(CFLAGS) $(SRC_DIR)grid.o $(SRC_DIR)movable.o $(SRC_DIR)image.o $(SRC_DIR)simulation.o $(SRC_DIR)arguments.o $(SRC_DIR)main.cpp -o crossroad

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)*.o $(OUTPUT_DIR)* crossroad

zip:
	zip -r T8_xproko47_xcerba00.zip src output Makefile output.txt simulate.py dokumentace.pdf
