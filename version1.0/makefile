client:epollClientv1.o dht11.o
		g++ -o client epollClientv1.o dht11.o -lwiringPi -pthread
epollClientv1.o:epollClientv1.cpp dht11.h
		g++ -c epollClientv1.cpp -pthread
dht11.o:dht11.c dht11.h
		g++ -c dht11.c -lwiringPi 
clean:
		rm *.o
