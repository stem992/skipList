CFLAGS = -g -O0 -Wall -Wextra -Wpedantic -I include -I Resources/

mkdir:
	mkdir -p bin
	mkdir -p build

test: bin/skip_list_test
	cd bin && ./skip_list_test

main : bin/skip_list_main
	cd bin && ./skip_list_main ../txt/dictionary.txt ../txt/correctme.txt 


bin/skip_list_test : build/skip_list_test.o build/skip_list.o build/unity.o
	$(CC) $^ -o $@

bin/skip_list_main : build/skip_list_main.o build/skip_list.o
	$(CC) $^ -o $@


build/skip_list_test.o: test/skip_list_test.c Resources/unity.h
	$(CC) $(CFLAGS) -c test/skip_list_test.c -o build/skip_list_test.o

build/skip_list_main.o: app/skip_list_main.c
	$(CC) $(CFLAGS) -c app/skip_list_main.c -o build/skip_list_main.o

build/skip_list.o: src/skip_list.c include/skip_list.h
	$(CC) $(CFLAGS) -c src/skip_list.c -o build/skip_list.o
	
build/unity.o : Resources/unity.c Resources/unity.h
	$(CC) $(CFLAGS) -c Resources/unity.c -o build/unity.o


clean:
	$(RM) build/*
	$(RM) bin/*
	