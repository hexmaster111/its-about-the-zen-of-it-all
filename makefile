CC=gcc
breath: src/breath.c src/heart_rate_repeter_com.c
	$(CC) -Wall src/breath.c src/heart_rate_repeter_com.c -obreath -lraylib -lm 
