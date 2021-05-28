CC = g++
EXEC = asteroid
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread
STD = -std=c++17
S = src
O = obj
B = binLinux

all: $(O) $(B) $(O)/main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/main.o: $(O)/Engine.o
	$(CC) $(S)/main.cpp -c -o $(O)/main.o $(STD) $(FLAGS)

$(O)/Engine.o: $(O)/Munition.o $(O)/Obstacle.o $(O)/Particule.o $(O)/Player.o
	$(CC) $(S)/Engine.cpp -c -o $(O)/Engine.o $(STD) $(FLAGS)

$(O)/Munition.o:
	$(CC) $(S)/Munition.cpp -c -o $(O)/Munition.o $(STD) $(FLAGS)

$(O)/Obstacle.o:
	$(CC) $(S)/Obstacle.cpp -c -o $(O)/Obstacle.o $(STD) $(FLAGS)

$(O)/Particule.o:
	$(CC) $(S)/Particule.cpp -c -o $(O)/Particule.o $(STD) $(FLAGS)

$(O)/Player.o:
	$(CC) $(S)/Player.cpp -c -o $(O)/Player.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
