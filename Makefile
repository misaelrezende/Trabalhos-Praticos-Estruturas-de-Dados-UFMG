CC = gcc
CFLAGS = -Wall
compile_binaries: client server

client: client.o
	@$(CC) $(CFLAGS) -o client src/build/client.o

client.o: src/client.c
	@mkdir -p src/build
	@$(CC) $(CFLAGS) -c src/client.c -o src/build/client.o

server: server.o
	@$(CC) $(CFLAGS) -o server src/build/server.o

server.o: src/server.c
	@mkdir -p src/build
	@$(CC) $(CFLAGS) -c src/server.c -o src/build/server.o

clean:
	@rm -rf src/build/ client server
