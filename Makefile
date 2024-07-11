all:
	g++ -I/usr/include/python3.12/ src/main.cpp -L/usr/lib/python3.12/config-3.12-x86_64-linux-gnu -lpython3.12 -o bin/main.o