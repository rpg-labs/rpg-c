




all: compile-tests compile

compile:
	gcc -fPIC -c rpg_csv_to_list.c
	gcc -fPIC -c rpg_hash.c
	gcc -fPIC -c rpg_list.c
	gcc -fPIC -c rpg_stdin.c
	gcc -fPIC -c rpg_string_list.c
#	gcc -shared -o librpg.so rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o
	ar rcs librpg.a rpg_csv_to_list.o rpg_hash.o rpg_list.o rpg_stdin.o rpg_string_list.o

compile-tests: compile
	gcc -o test/test_rpg_csv_to_list test_rpg_csv_to_list.c rpg_string_list.o -l cunit
	gcc -o test/test_rpg_hash test_rpg_hash.c rpg_string_list.o -l cunit
	gcc -o test/test_rpg_string_list test_rpg_string_list.c -l cunit

test: compile-tests
	./test/test_rpg_hash
	./test/test_rpg_string_list

install: compile
	cp *.h /usr/local/include
	cp *.a /usr/local/lib

clean:
	rm -f *.so *.o *.a test/*
