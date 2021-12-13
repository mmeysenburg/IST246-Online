all:	PA03Tests PA03

PA03:	PA03.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE PA03.cpp -o PA03

PA03Tests:	PA03Tests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN PA03Tests.cpp -o PA03Tests

clean:
	rm PA03 PA03Tests
