# Declaration de variables
FILES=tmp/shogi.o tmp/partie.o
GFLAGS=-Wall

all: tmp/shogi.o tmp/partie.o
	gcc -g $(GFLAGS) $(FILES) -o shogi

tmp/shogi.o: src/shogi.c
	gcc -c $(GFLAGS) src/shogi.c -o tmp/shogi.o

tmp/partie.o: src/partie.c src/partie.h
	gcc -c $(GFLAGS) src/partie.c -o tmp/partie.o

clean:
	rm tmp/*.o *~
