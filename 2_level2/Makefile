edit:main.o kbd.o command.o display.o /
	insert.o search.o files.o utils.o
	$(CC) -o edit main.o kbd.o command.o display.o /
	insert.o search.o files.o utils.o

main.o:main.c defs.h
	$(CC) -c main.c

clean:
	rm -rf *.o 