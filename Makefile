CC = gcc
CFLAGS = -Wall

monolithic:
	$(CC) $(CFLAGS) -c src/List.c -o build/list.o
	$(CC) $(CFLAGS) -c src/HashMap.c -o build/hashmap.o
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

	$(CC) build/main.o build/hashmap.o build/list.o -o build/program

run_monolithic:
	./build/program

static:
	$(CC) $(CFLAGS) -c src/List.c -o build/list.o
	$(CC) $(CFLAGS) -c src/HashMap.c -o build/hashmap.o
	ar r build/libhashmap.a build/list.o build/hashmap.o
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
	$(CC) build/main.o build/libhashmap.a -o build/program

	$(CC) build/main.o build/hashmap.o build/list.o -o build/program

run_static:
	./build/program


dynamic:
	$(CC) $(CFLAGS) -fPIC -c src/List.c -o build/list.o
	$(CC) $(CFLAGS) -fPIC -c src/HashMap.c -o build/hashmap.o
	$(CC) build/list.o build/hashmap.o -shared -o build/libhashmap.so
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
	$(CC) build/main.o -Lbuild -lhashmap -o build/program


run_dynamic:
	LD_LIBRARY_PATH="$ LD_LIBRARY_PATH:build/." ./build/program
