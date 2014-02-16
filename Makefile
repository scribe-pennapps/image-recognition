all:
		g++ `pkg-config --cflags --libs opencv` *.cc *.cpp -o main

clean:
		rm main
