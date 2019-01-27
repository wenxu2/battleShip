test: player.o battleship.o
	gcc player.o battleship.o -o test -g

player.o: player.c battleship.c battleship.h
	gcc -Wall -c player.c -g

battleship.o: battleship.c battleship.h
	gcc -Wall -c battleship.c -g

clean: 
	rm *.o test
