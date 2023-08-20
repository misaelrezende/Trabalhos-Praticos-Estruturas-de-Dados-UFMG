CC = gcc
CFLAGS = -Wall
compile_binaries: equipment server

equipment: equipment.o
	@$(CC) $(CFLAGS) -o equipment src/build/equipment.o

equipment.o: src/equipment.c
	@mkdir -p src/build
	@$(CC) $(CFLAGS) -c src/equipment.c -o src/build/equipment.o

server: server.o
	@$(CC) $(CFLAGS) -o server src/build/server.o

server.o: src/server.c
	@mkdir -p src/build
	@$(CC) $(CFLAGS) -c src/server.c -o src/build/server.o

clean:
	@rm -rf src/build/ equipment server
