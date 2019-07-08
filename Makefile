GAMENAME = ffsdl
CC = g++
RM = rm -rf
INCLUDE = /usr/include/SDL

all: build
	
build:
	$(CC)  *.cpp -g -o $(GAMENAME) -I$(INCLUDE) -lSDL2 -lSDL2_image -lSDL2_mixer -lm

run:
	./$(GAMENAME)

clean:
	$(RM) ./$(GAMENAME) *.o