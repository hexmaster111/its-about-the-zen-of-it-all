CC=gcc
breath: breath.c
	$(CC) -o breath breath.c -lm -lraylib