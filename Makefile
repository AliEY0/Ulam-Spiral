all:
	gcc main.c -o main `sdl2-config --cflags --libs` -lm
	./main
	rm main
