all:	BFSDemo DijkstraDemo GraphTests

GraphTests:	GraphTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN GraphTests.cpp -o GraphTests

BFSDemo:	BFSDemo.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE BFSDemo.cpp -o BFSDemo

DijkstraDemo: 	DijkstraDemo.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE DijkstraDemo.cpp -o DijkstraDemo

clean:
	rm BFSDemo DijkstraDemo GraphTests
