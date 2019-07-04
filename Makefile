GAMENAME = ffsdl
CC = g++
RM = rm -rf
INCLUDE = /usr/include/SDL

all: build
	
build:
	$(CC)  *.cpp -g -o $(GAMENAME) -I$(INCLUDE) -lSDL2 -lSDL2_image -lm

run:
	./$(GAMENAME)

clean:
	$(RM) ./$(GAMENAME) *.o