
SRC = backendPieces.c randomGenerator.c scoreSystem.c menu.c frontendPieces.c Cetraminos.c
OBJ = backendPieces.o randomGenerator.o scoreSystem.o menu.o frontendPieces.o Cetraminos.o

CFLAGS = -O3 -D_DEBUG -Dlinux -c -I/usr/include/SDL3
LDFLAGS = -lSDL3 -lSDL3_ttf 

all: Cetraminos
Cetraminos: $(OBJ)
	@echo Linking...
	@rm -f Cetraminos
	@gcc $(OBJ) $(LDFLAGS) -o Cetraminos
	@echo Linkking OK...

clean:
	@echo Cleaning
	@rm -f *.o

