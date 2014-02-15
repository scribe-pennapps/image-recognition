all:
		g++ `pkg-config --cflags --libs opencv` *.cc -o main

clean:
		rm main
