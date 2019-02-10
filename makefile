CC = g++-7
CFLAGS = -Wall -std=c++1z -g
EXEC_NAME = bin/timeLine
OBJECTS = bin/objects/
DIR = bin bin/objects
OBJ_FILES =  $(OBJECTS)main.o $(OBJECTS)joueur.o $(OBJECTS)iamanager.o $(OBJECTS)mainJoueur.o $(OBJECTS)jeu.o $(OBJECTS)pileCarte.o $(OBJECTS)carte.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)


$(EXEC_NAME) : $(DIR) $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

$(OBJECTS)%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(DIR) :
	mkdir bin
	mkdir bin/objects