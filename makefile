CC = gcc -Wall -Wextra 
CFLAGS = -lm
BIN = main

$(BIN): main.o arbre.o fifo.o point.o
	$(CC) $^ -o $@ $(CFLAGS)

main.o: main.c
	$(CC) $< -c

arbre.o: arbre.c arbre.h
	$(CC) $< -c

fifo.o: fifo.c fifo.h
	$(CC) $< -c

point.o: point.c point.h
	$(CC) $< -c

clean:
	rm -rf ./*.o $(BIN)
