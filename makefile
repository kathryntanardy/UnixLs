all:
	gcc -Wall -Werror UnixLs.c -o UnixLs

test:
	gcc -Wall -Werror infodemo.c -o test

clean: 
	rm UnixLs test