CC=gcc -g -Wall -Wextra
POST_FLAGS=-lm -lfreetype

CTESTS=$(wildcard ./tests/*.c)
OTESTS=$(CTESTS:.c=.o)
HTESTS=$(wildcard ./tests/include/*.h)

CPROB=$(wildcard ./src/probability/*.c)
HPROB=$(wildcard ./src/probability/include/*.h)
OPROB=$(CPROB:.c=.o)

CCANVAS=$(wildcard ./src/canvas/*.c)
HCANVAS=$(wildcard ./src/canvas/include/*.h)
OCANVAS=$(CCANVAS:.c=.o)

CMAIN=$(wildcard ./src/main/*.c)
OMAIN=$(CMAIN:.c=.o)

EXEFILE=bin/main

all: objects
	$(CC) $(OCANVAS) $(OMAIN) $(OTESTS) $(OPROB) -o $(EXEFILE) $(POST_FLAGS)

objects: $(HCANVAS) $(CCANVAS) $(CMOVE) $(CMAIN) $(CTESTS) $(HTESTS) $(HPROB) $(CPROB)
	$(CC) -c ./src/canvas/pixel.c -o ./src/canvas/pixel.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/node.c -o ./src/canvas/node.o $(POST_FLAGS)
	$(CC) -c ./src/probability/erdos_renyi.c -o ./src/probability/erdos_renyi.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/canvas.c -o ./src/canvas/canvas.o $(POST_FLAGS)
	$(CC) -c ./tests/connections.c -o ./tests/connections.o $(POST_FLAGS)
	$(CC) -c ./src/main/main.c -o ./src/main/main.o $(POST_FLAGS)

vim:
	nvim $(CCANVAS) $(CMAIN) $(CTESTS) $(CPROB)

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
	- rm $(OPROB)
	- rm $(OTESTS)
	- rm $(EXEFILE)
