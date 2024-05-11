CC=gcc
breath: src/breath.c
	$(CC) -Wall src/breath.c -obreath -lraylib -lm 
