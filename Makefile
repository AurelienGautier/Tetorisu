# g++ src/*.cpp -o prog -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

CC = g++
EXEC = prog
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
SFML = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all : $(EXEC)

src/%.o : src/%.cpp
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(SFML)

clean :
	rm -f src/*.o
	rm prog