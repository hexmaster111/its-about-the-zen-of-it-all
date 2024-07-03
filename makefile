CC=gcc
#FLAGS=-ggdb -Wall
FLAGS=-Wall
RAYLIB = `pkg-config --libs --cflags raylib`
#linux use this
#RAYLIB = -lraylib

chart:src/chartdemo.c src/chart.c
	$(CC) $(FLAGS) src/chartdemo.c src/chart.c -ochart $(RAYLIB) -lm 

breath: src/breath.c src/heart_rate_repeter_com.c
	$(CC) $(FLAGS) src/breath.c src/heart_rate_repeter_com.c -obreath $(RAYLIB) -lm 

hbview: src/hbview.c src/heart_rate_repeter_com.c src/chart.c
	$(CC) $(FLAGS) src/chart.c src/hbview.c src/heart_rate_repeter_com.c -ohbview $(RAYLIB) -lm 
