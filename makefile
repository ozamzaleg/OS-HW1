OBJECTS = stat1 stat2 child2 
VERSION1 = stat1
VERSION2 = stat2 child2

CC = gcc
CFLAGS = -Wall -o

all: clean $(OBJECTS)

clean: 
	rm -rf *.o $(OBJECTS)

version1: $(VERSION1)

version2: $(VERSION2)

stat1: stat1.c func.c generalfunc.c communication.c
	$(CC) $(CFLAGS) stat1 stat1.c func.c generalfunc.c communication.c
	
stat2: stat2.c func.c generalfunc.c 
	$(CC) $(CFLAGS) stat2 stat2.c func.c generalfunc.c 
		
child2: child2.c func.c communication.c
	$(CC) $(CFLAGS) child2 child2.c func.c communication.c
