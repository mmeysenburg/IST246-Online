all:	CoordinateTests MontePi

CoordinateTests:	CoordinateTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN CoordinateTests.cpp -o CoordinateTests

MontePi:	MontePi.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE MontePi.cpp -o MontePi

clean:
	rm CoordinateTests MontePi
