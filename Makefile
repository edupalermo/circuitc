all: bin/server bin/client bin/test

bin/server: src/server.c src/protocol.h
	gcc -o bin/server src/server.c -lpthread

bin/client: src/client.c
	gcc -o bin/client src/client.c -lpthread

bin/test: src/test.c
	gcc -o bin/test src/test.c

clean:
	rm -f bin/client bin/server
