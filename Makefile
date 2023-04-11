CC=gcc -g -Wall -Wextra
UBCC=gcc -g -Wall -Wextra -I/usr/include/freetype2
POST_FLAGS=-lm -lfreetype -lpng

CTESTS=$(wildcard ./tests/*.c)
OTESTS=$(CTESTS:.c=.o)
HTESTS=$(wildcard ./tests/include/*.h)

CFIO=$(wildcard ./src/file_io/*.c)
OFIO=$(CFIO:.c=.o)
HFIO=$(wildcard ./src/file_io/include/*.h)

CPROB=$(wildcard ./src/probability/*.c)
HPROB=$(wildcard ./src/probability/include/*.h)
OPROB=$(CPROB:.c=.o)

CCANVAS=$(wildcard ./src/canvas/*.c)
HCANVAS=$(wildcard ./src/canvas/include/*.h)
OCANVAS=$(CCANVAS:.c=.o)

CFPP=$(wildcard ./src/file_preprocessing/*.c)
HFPP=$(wildcard ./src/file_preprocessing/include/*.h)
OFPP=$(CFPP:.c=.o)

CMAIN=$(wildcard ./src/main/*.c)
OMAIN=$(CMAIN:.c=.o)

TARGETS=example_config/config_one example_config/config_two example_config/config_three example_config/config_four
EXEFILE=bin/main

all: objects
	$(CC) $(OCANVAS) $(OMAIN) $(OTESTS) $(OPROB) $(OFPP) $(OFIO) -o $(EXEFILE) $(POST_FLAGS)

objects: $(HCANVAS) $(CCANVAS) $(CMOVE) $(CMAIN) $(CFPP) $(HFPP) $(CTESTS) $(HTESTS) $(HPROB) $(CPROB) $(HFIO) $(CFIO)
	$(CC) -c ./src/canvas/pixel.c -o ./src/canvas/pixel.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/node.c -o ./src/canvas/node.o $(POST_FLAGS)
	$(CC) -c ./src/file_io/file_io.c -o ./src/file_io/file_io.o $(POST_FLAGS)
	$(CC) -c ./src/file_preprocessing/file_preprocessing.c -o ./src/file_preprocessing/file_preprocessing.o $(POST_FLAGS)
	$(CC) -c ./src/probability/erdos_renyi.c -o ./src/probability/erdos_renyi.o $(POST_FLAGS)
	$(CC) -c ./src/canvas/canvas.c -o ./src/canvas/canvas.o $(POST_FLAGS)
	$(CC) -c ./tests/connections.c -o ./tests/connections.o $(POST_FLAGS)
	$(CC) -c ./src/main/main.c -o ./src/main/main.o $(POST_FLAGS)

vim:
	nvim $(CCANVAS) $(CMAIN) $(CTESTS) $(CPROB) $(CFIO)

vimh:
	nvim $(HFILES) 

run:
	$(EXEFILE)

run-configs:
	$(EXEFILE) $(TARGETS)

debug:
	gdb -q $(EXEFILE)

memcheck:
	valgrind $(EXEFILE) $(TARGETS) --leak-check=full --read-var-info

feh:
	feh docs/uml.png&

plant:
	plantuml docs/uml.txt
	convert docs/uml.png -channel RGB -negate docs/uml.png

git-update:
	git add Makefile README.md src/ nix/ tests/ example_config/ reference_images/

clean:
	- rm $(OCANVAS)
	- rm $(OFIO)
	- rm $(OFPP)
	- rm $(OMAIN)
	- rm $(OPROB)
	- rm $(OTESTS)
	- rm $(EXEFILE)
