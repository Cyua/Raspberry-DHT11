run:main.o dht11.o
		g++ -o run main.o dht11.o -lwiringPi
main.o:main.cpp dht11.h
		g++ -c main.cpp
dht11.o:dht11.c dht11.h
		g++ -c dht11.c -lwiringPi 
