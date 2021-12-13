all:	PA05 DLLTests

PA05:	PA05.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE PA05.cpp -o PA05

DLLTests:	DLLTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN DLLTests.cpp -o DLLTests

clean:
	rm PA05 DLLTests
