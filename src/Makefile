SRC = backendPieces.c frontendPieces.c main.c music.c randomGenerator.c scoreSystem.c Cetraminos.c menu.c GString.c
OBJ = backendPieces.o frontendPieces.o main.o music.o randomGenerator.o scoreSystem.o Cetraminos.o menu.o GString.o
CFLAGS = -O3 -c -I/usr/include/SDL2 -Wall -Wextra 
LDFLAGS = -lm -lSDL2 -lSDL2_ttf  -lSDL2_mixer

all: Cetraminos
Cetraminos: $(OBJ)
	@echo Linking...
	@rm -f Cetraminos
	@gcc $(OBJ) $(LDFLAGS) -o Cetraminos
	@echo Linkking OK...
#	@echo Cleaning
#	@rm -f *.o

clean:
	@echo Cleaning
	@rm -f *.o
