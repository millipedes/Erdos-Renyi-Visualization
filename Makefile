CC=gcc -g -Wall -Wextra
POST_FLAGS=-lm -lfreetype

CCANVAS=$(wildcard ./src/canvas/*.c)
HCANVAS=$(wildcard ./src/canvas/include/*.h)
OCANVAS=$(CCANVAS:.c=.o)

CMOVE=$(wildcard ./src/move/*.c)
HMOVE=$(wildcard ./src/move/include/*.h)
OMOVE=$(CMOVE:.c=.o)

CMAIN=$(wildcard ./src/main/*.c)
OMAIN=$(CMAIN:.c=.o)

EXEFILE=bin/main

all: objects
	$(CC) $(OCANVAS) $(OMOVE) $(OMAIN) -o $(EXEFILE) $(POST_FLAGS)

objects: $(HCANVAS) $(HMOVE) $(CCANVAS) $(CMOVE) $(CMAIN)
	$(CC) -c ./src/move/move.c -o ./src/move/move.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/pixel.c -o ./src/canvas/pixel.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/node.c -o ./src/canvas/node.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/canvas.c -o ./src/canvas/canvas.o $(POST_FLAGS)
	$(CC) -c ./src/main/main.c -o ./src/main/main.o $(POST_FLAGS)

vim:
	nvim $(CCANVAS) $(CMOVE) $(CMAIN)

vimh:
	nvim $(HFILES) 

run:
	$(EXEFILE)

debug:
	gdb -q $(EXEFILE)

memcheck:
	valgrind $(EXEFILE) --leak-check=full --read-var-info

feh:
	feh docs/uml.png&

plant:
	plantuml docs/uml.txt
	convert docs/uml.png -channel RGB -negate docs/uml.png

git-update:
	git add Makefile README.md src/ nix/

clean:
	- rm $(OCANVAS)
	- rm $(OMAIN)
	- rm $(OMOVE)
	- rm $(EXEFILE)
