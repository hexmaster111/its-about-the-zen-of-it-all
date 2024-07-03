CC=gcc

chart:src/chartdemo.c src/chart.c
	$(CC) -ggdb -Wall src/chartdemo.c src/chart.c -ochart -lraylib -lm 

breath: src/breath.c src/heart_rate_repeter_com.c
	$(CC) -ggdb -Wall src/breath.c src/heart_rate_repeter_com.c -obreath -lraylib -lm 


hbview: src/hbview.c src/heart_rate_repeter_com.c src/chart.c
	$(CC) -ggdb -Wall src/chart.c src/hbview.c src/heart_rate_repeter_com.c -obreath -lraylib -lm 
