CC = gcc
CFLAGS = -Wall

MONOLITHIC_PATH = build/monolithic

monolithic:
	$(CC) $(CFLAGS) -c src/List.c -o $(MONOLITHIC_PATH)/list.o
	$(CC) $(CFLAGS) -c src/HashMap.c -o $(MONOLITHIC_PATH)/hashmap.o
	$(CC) $(CFLAGS) -c src/main.c -o $(MONOLITHIC_PATH)/main.o

	$(CC) $(MONOLITHIC_PATH)/main.o $(MONOLITHIC_PATH)/hashmap.o $(MONOLITHIC_PATH)/list.o -o $(MONOLITHIC_PATH)/program

run_monolithic:
	./$(MONOLITHIC_PATH)/program

STATIC_PATH = build/static

static:
	$(CC) $(CFLAGS) -c src/List.c -o $(STATIC_PATH)/list.o
	$(CC) $(CFLAGS) -c src/HashMap.c -o $(STATIC_PATH)/hashmap.o
	ar r $(STATIC_PATH)/libhashmap.a $(STATIC_PATH)/list.o $(STATIC_PATH)/hashmap.o
	$(CC) $(CFLAGS) -c src/main.c -o $(STATIC_PATH)/main.o
	$(CC) $(STATIC_PATH)/main.o $(STATIC_PATH)/libhashmap.a -o $(STATIC_PATH)/program

	$(CC) $(STATIC_PATH)/main.o $(STATIC_PATH)/hashmap.o $(STATIC_PATH)/list.o -o $(STATIC_PATH)/program

run_static:
	./$(STATIC_PATH)/program


DYNAMIC_PATH = build/dynamic

dynamic:
	$(CC) $(CFLAGS) -fPIC -c src/List.c -o $(DYNAMIC_PATH)/list.o
	$(CC) $(CFLAGS) -fPIC -c src/HashMap.c -o $(DYNAMIC_PATH)/hashmap.o
	$(CC) $(DYNAMIC_PATH)/list.o $(DYNAMIC_PATH)/hashmap.o -shared -o $(DYNAMIC_PATH)/libhashmap.so
	$(CC) $(CFLAGS) -c src/main.c -o $(DYNAMIC_PATH)/main.o
	$(CC) $(DYNAMIC_PATH)/main.o -L$(DYNAMIC_PATH) -lhashmap -o $(DYNAMIC_PATH)/program


run_dynamic:
	LD_LIBRARY_PATH="$ LD_LIBRARY_PATH:$(DYNAMIC_PATH)/." ./$(DYNAMIC_PATH)/program
