CC=g++
CFLAGS=-g -Wall

make: 
	$(CC) $(CFLAGS) PuzzleSolver.h PuzzleSolver.cpp Source.cpp -o Out.exe

run:
	./Out.exe $(FILE)
	
clean:
	$(RM) -f *.o *~ Out.exe
