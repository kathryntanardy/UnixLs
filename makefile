all:
	gcc -Wall UnixLs.c -o UnixLs

test:
	gcc -Wall -Werror infodemo.c -o test

clean: 
	rm output