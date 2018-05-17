proj1: main.o aq.o
	g++ -std=c++11 -g -Wall main.o aq.o -o proj1
main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp
aq.o: aq.h aq.cpp
	g++ -std=c++11 -g -Wall -c aq.cpp

	
clean: 
	rm *.o proj1
	echo clean done 
