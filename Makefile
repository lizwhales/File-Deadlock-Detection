CC=gcc
CFLAGS=-Wall -03

detect:
	$(CC) $(CFLAGS) -o detect detect.c

clean:
	rm -f *.o *.plist detect

format:
	clang-format --style=GNU -i *.c

analyze:
	clang --analyze detect.c -o detect
	rm detect

syntax:
	clang -fsyntax-only detect.c