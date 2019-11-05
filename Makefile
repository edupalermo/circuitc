all: bin/server bin/client

bin/server: src/server.c
	gcc -o bin/server src/server.c -lpthread

bin/client: src/client.c
	gcc -o bin/client src/client.c -lpthread

clean:
	rm -f bin/client bin/server
