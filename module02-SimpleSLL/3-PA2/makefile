all:	SimpleSLLTests RandomPoet

SimpleSLLTests:	SimpleSLLTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN SimpleSLLTests.cpp -o SimpleSLLTests

RandomPoet:	RandomPoet.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE RandomPoet.cpp -o RandomPoet

clean:
	rm SimpleSLLTests RandomPoet
