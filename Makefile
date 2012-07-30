




all: compile-tests compile

compile:
	gcc -fPIC -c rpg_csv_to_list.c
	gcc -fPIC -c rpg_hash.c
	gcc -fPIC -c rpg_list.c
	gcc -fPIC -c rpg_stdin.c
	gcc -fPIC -c rpg_string_list.c
	gcc -fPIC -c rpg_time.c
	gcc -fPIC -c rpg_json_import.c
#	gcc -shared -o librpg.so rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o
	ar rcs librpg.a rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o rpg_time.o rpg_json_import.o

compile-tests: compile
	gcc -o test/test_rpg_csv_to_list test_rpg_csv_to_list.c rpg_string_list.o -l cunit
	gcc -o test/test_rpg_hash test_rpg_hash.c rpg_string_list.o -l cunit
	gcc -o test/test_rpg_string_list test_rpg_string_list.c -l cunit

test-rpg_json_import: compile
	gcc -o test/test_rpg_json_import test_rpg_json_import.c -l cunit
	./test/test_rpg_json_import


test: compile-tests
	./test/test_rpg_hash
	./test/test_rpg_string_list
	./test/test-rpg_json_import

install: compile
	cp *.h /usr/local/include
	cp *.a /usr/local/lib

clean:
	rm -f *.so *.o *.a test/*
