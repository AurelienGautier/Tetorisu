# g++ src/*.cpp -o prog -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

CC = g++
EXEC = prog
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)

SFML = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all : $(EXEC)

obj/%.o : src/%.cpp
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(SFML)

clean :
	rm -f obj/*.o
	rm prog