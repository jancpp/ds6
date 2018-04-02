Lab06: main.o  OpenHash.o ClosedHashDH.o ClosedHashQP.o LinkedList.o Node.o
	g++ -g -std=c++11 -Wall main.o  OpenHash.o ClosedHashDH.o ClosedHashQP.o LinkedList.o Node.o -o Lab06

main.o: main.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

OpenHash.o: OpenHash.h OpenHash.cpp
	g++ -g -std=c++11 -Wall -c OpenHash.cpp

ClosedHashDH.o: ClosedHashDH.h ClosedHashDH.cpp
	g++ -g -std=c++11 -Wall -c ClosedHashDH.cpp

ClosedHashQP.o: ClosedHashQP.h ClosedHashQP.cpp
	g++ -g -std=c++11 -Wall -c ClosedHashQP.cpp

Node.o: Node.cpp Node.h
	g++ -g -std=c++11 -Wall -c Node.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -g -std=c++11 -Wall -c LinkedList.cpp

clean:
	rm *.o
