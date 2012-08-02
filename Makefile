




CC=gcc `/usr/bin/apr-1-config --cppflags --cflags`

all: compile

compile:
	$(CC) -fPIC -c rpg_csv_to_list.c
	$(CC) -fPIC -c rpg_hash.c
	$(CC) -fPIC -c rpg_list.c
	$(CC) -fPIC -c rpg_stdin.c
	$(CC) -fPIC -c rpg_string_list.c
	$(CC) -fPIC -c rpg_time.c
	$(CC) -fPIC -c rpg_json_import.c
#	$(CC) -shared -o librpg.so rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o
	ar rcs librpg.a rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o rpg_time.o rpg_json_import.o

compile-tests: compile
	$(CC) -o test/test_rpg_hash test_rpg_hash.c rpg_string_list.o -lcunit -lapr-1
	$(CC) -o test/test_rpg_string_list test_rpg_string_list.c -lcunit -lapr-1

test-rpg_json_import: compile
	$(CC) -o test/test_rpg_json_import test_rpg_json_import.c -lcunit -lapr-1
	./test/test_rpg_json_import

test-rpg_csv_to_list: compile
	$(CC) -o test/test_rpg_csv_to_list test_rpg_csv_to_list.c rpg_string_list.o -lcunit -lapr-1
	./test/test_rpg_csv_to_list

test: compile-tests test-rpg_json_import test-rpg_csv_to_list
	./test/test_rpg_hash
	./test/test_rpg_string_list

install: compile
	cp *.h /usr/local/include
	cp *.a /usr/local/lib

clean:
	rm -f *.so *.o *.a test/*
