



all:
	@gcc -c main.c
	@gcc main.o -o tetris
	@clear
	@./tetris


clean:
	rm -rf main.o tetris
