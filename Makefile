CC = /usr/bin/g++
SRC = *.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -g

# This flag is being passed to silence a note during compilation, indicating changes in the design of std::list.
# Essentually, if you have errors compiling, you may need to rebuild your c++ libraries.
CFLAGS += -Wno-psabi

# Currently this is the only non-gnu dependancey.  It is also depriciated, I would prefer to get rid of it
# however I was not able to find good documentation for the I2C 1602 LCD screen
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
