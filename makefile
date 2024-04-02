all:
	gcc -Wall -Werror UnixLs.c -o output

clean: 
	rm output