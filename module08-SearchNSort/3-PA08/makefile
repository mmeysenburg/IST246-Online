all:	PA08 BSTests

BSTests:	BSTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN BSTests.cpp -o BSTests

PA08: 	PA08.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE PA08.cpp -o PA08

clean:
	rm PA08 BSTests
