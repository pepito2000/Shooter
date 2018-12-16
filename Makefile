SRC=main.c

BIN=main



$(BIN): $(SRC)
	

gcc -w -g -std=c99 image.c projectile.c effets.c personnage.c listeB.c listeP.c listeE.c listeR.c son.c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -o main



clean:
	rm -f $(BIN)
