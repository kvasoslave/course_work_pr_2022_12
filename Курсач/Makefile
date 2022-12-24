all: build clean

build: main.o texttools.o sortsent.o samewords.o removeuncapitalized.o maskfinder.o windowsrun.o
	gcc main.o texttools.o sortsent.o samewords.o removeuncapitalized.o maskfinder.o windowsrun.o -o course_work

main.o: main.c texttools.h sortsent.h samewords.h removeuncapitalized.h maskfinder.h windowsrun.h
	gcc -c main.c

texttools.o: texttools.c texttools.h
	gcc -c texttools.c

sortsent.o: sortsent.c sortsent.h
	gcc -c sortsent.c

samewords.o: samewords.c samewords.h
	gcc -c samewords.c

removeuncapitalized.o: removeuncapitalized.c removeuncapitalized.h
	gcc -c removeuncapitalized.c

maskfinder.o: maskfinder.c maskfinder.h
	gcc -c maskfinder.c

linuxrun.o: windowsrun.c windowsrun.h
	gcc -c windowsrun.c

clean:
	rm *.o
