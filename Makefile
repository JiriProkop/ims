CC = g++
CFLAGS = -std=c++201 -Wall -Wextra
SRC_DIR = src/

crossroad: 
	$(CC) $(CFLAGS) $(SRC_DIR)main.cpp -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(SRC_DIR)*.o crossroad
