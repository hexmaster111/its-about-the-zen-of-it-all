CC=gcc

chart:src/chart.c
	$(CC) -ggdb -Wall src/chart.c -ochart -lraylib -lm 



breath: src/breath.c src/heart_rate_repeter_com.c
	$(CC) -ggdb -Wall src/breath.c src/heart_rate_repeter_com.c -obreath -lraylib -lm 
