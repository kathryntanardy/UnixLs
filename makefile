all:
	gcc -Wall -Werror UnixLs.c -o output

test:
	gcc -Wall -Werror infodemo.c -o test

clean: 
	rm output