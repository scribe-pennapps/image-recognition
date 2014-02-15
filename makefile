all:
	g++ `pkg-config --cflags --libs opencv` *.cpp -o main

clean:
	rm main