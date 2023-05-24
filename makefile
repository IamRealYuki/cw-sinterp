.PHONY: all
all: sinterp.exe
sinterp.exe: src/main.o src/lexer.o src/executor.o src/clean.o
	gcc -Wall -Werror -g -O0 -o sinterp.exe src/main.o src/lexer.o src/executor.o src/clean.o
main.o: src/main.c
	gcc -Wall -Werror -g -O0 -c src/main.c
lexer.o: src/lexer.c
	gcc -Wall -Werror -g -O0 -c src/lexer.c
executor.o: src/executor.c
	gcc -Wall -Werror -g -O0 -c src/executor.c
clean.o: src/clean.c
	gcc -Wall -Werror -g -O0 -c src/clean.c