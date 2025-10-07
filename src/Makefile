SRC = backendPieces.c randomGenerator.c scoreSystem.c menu.c frontendPieces.c Cetraminos.c music.c
OBJ = backendPieces.o randomGenerator.o scoreSystem.o menu.o frontendPieces.o Cetraminos.o music.o

CFLAGS = -O3 -c -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lSDL2_ttf  -lSDL2_mixer

all: Cetraminos
Cetraminos: $(OBJ)
	@echo Linking...
	@rm -f Cetraminos
	@gcc $(OBJ) $(LDFLAGS) -o Cetraminos
	@echo Linkking OK...
	@echo Cleaning
	@rm -f *.o

clean:
	@echo Cleaning
	@rm -f *.o
