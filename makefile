run:
	echo "Compiling and running the program"
	gcc -o main src/main.c
	./main
clean:
	echo "Cleaning up"
	rm main