all:
	g++ -I/usr/include/python3.12/ -I/usr/include/SDL2/ src/main.cpp -L/usr/lib/python3.12/config-3.12-x86_64-linux-gnu -lpython3.12 -lSDL2 -o bin/main.o