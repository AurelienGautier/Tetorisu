# g++ src/*.cpp -o prog -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

CXX = g++
EXEC = prog
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)

SFML = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all : $(EXEC)

obj/%.o : src/%.cpp
	$(CXX) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CXX) -o $@ $^ $(SFML)

clean :
	rm -f obj/*.o
	rm prog