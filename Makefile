CC = g++

CompileParms = -c -Wall

OBJS = standaard.o bomberman.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Bomberman

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

bomberman.o: bomberman.cc standaard.h bomberman.h
	$(CC) $(CompileParms)  bomberman.cc

main.o: main.cc standaard.h bomberman.h
	$(CC) $(CompileParms)  main.cc

