out: main.o fileReader.o
	g++ -o run main.o fileReader.o
main.o:main.cpp fileReader.h
	g++ -c main.cpp
fileReader.o:fileReader.cpp fileReader.h
	g++ -c fileReader.cpp
