CC = /usr/bin/g++
SRC = *.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -g
LDFLAGS = -lwiringPi
EXE=tempctrl

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm $(OBJ)
