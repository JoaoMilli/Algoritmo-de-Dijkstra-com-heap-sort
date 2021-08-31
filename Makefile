trab2:
	gcc -o trab2 *.c -lm
clean:
	rm -rf *.o
run:
	make trab2
	make clean