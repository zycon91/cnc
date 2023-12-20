CC?=gcc
CFLAGS=-Iinclude -I/usr/include/postgresql/ -I/usr/include/libbson-1.0 -I/usr/include/libmongoc-1.0 -Wall -g
LDFLAGS=-lcyaml -lpq -lmongoc-1.0 -lbson-1.0
DEPS=$(wildcard include/*.h)
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=%.o)

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cnc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o cnc

valgrind: cnc
	valgrind --leak-check=full ./cnc -f test.yaml

# CC?=gcc
# CFLAGS=-Iinclude -I/usr/include/postgresql/ -I/usr/include/libbson-1.0 -I~/Documents/mongoc-c-driver/build/src/libmongoc-1.0 -Wall -g
# LDFLAGS=-lcyaml -lpq -lmongoc-1.0 -lbson-1.0 -L~/Documents/mongoc-c-driver/libmongoc
# DEPS=$(wildcard include/*.h)
# SRC=$(wildcard src/*.c)
# OBJ=$(SRC:src/%.c=%.o)

# %.o: src/%.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# cnc: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# clean:
# 	rm -f *.o cnc

# valgrind: cnc
# 	valgrind --leak-check=full ./cnc -f test.yaml
