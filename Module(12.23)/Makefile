client: main.o clientModule.o
	g++ -o client main.o clientModule.o
main.o: main.cpp clientModule.h
	g++ -c main.cpp
clientModule.o: clientModule.cpp clientModule.h
	g++ -c clientModule.cpp
