build:
	gcc -m32 -std=c99 tema3.c Functii.c Functii.h -o tema3
run:
	./tema3
clean:
	rm -rf tema3