.PHONY: all
all: sinterp.exe
sinterp.exe: main.o lexer.o executor.o clean.o
	gcc -Wall -Werror -g -O0 -o sinterp.exe src/main.o src/lexer.o src/executor.o src/clean.o
main.o: src/main.c
	gcc -I src -Wall -Werror -g -O0 -c src/main.c -o src/$@
lexer.o: src/lexer.c
	gcc -I src -Wall -Werror -g -O0 -c src/lexer.c -o src/$@
executor.o: src/executor.c
	gcc -I src -Wall -Werror -g -O0 -c src/executor.c -o src/$@
clean.o: src/clean.c
	gcc -I src -Wall -Werror -g -O0 -c src/clean.c -o src/$@