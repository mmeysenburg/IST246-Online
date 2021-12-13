all:	IteratorSLLTests PA04

IteratorSLLTests:	IteratorSLLTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN IteratorSLLTests.cpp -o IteratorSLLTests

PA04:	PA04.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE PA04.cpp -o PA04

clean:
	rm IteratorSLLTests PA04
