all: server test

server: server.o
	gcc -o server server.o

test: test.o
	gcc -o test test.o
