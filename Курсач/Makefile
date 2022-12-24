all: build clean

build: main.o texttools.o sortsent.o samewords.o removeuncapitalized.o maskfinder.o linuxrun.o
	gcc main.o texttools.o sortsent.o samewords.o removeuncapitalized.o maskfinder.o linuxrun.o -o course_work

main.o: main.c texttools.h sortsent.h samewords.h removeuncapitalized.h maskfinder.h linuxrun.h
	gcc -c main.c

texttools.o: textools.c texttools.h
	gcc -c texttools.c

sortsent.o: sortsent.c sortsent.h
	gcc -c sortsent.c

samewords.o: samewords.c samewords.h
	gcc -c samewords.c

removeuncapitalized.o: removeuncapitalized.c removeuncapitalized.h
	gcc -c removeuncapitalized.c

maskfinder.o: maskfinder.c maskfinder.o
	gcc -c maskfinder.c

linuxrun.o: linuxrun.c linuxrun.h
	gcc -c linuxrun.c

clean:
	rm *.o
