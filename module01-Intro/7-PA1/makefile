all:	ObjectCounterTests PowerBall

ObjectCounterTests:	ObjectCounterTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN ObjectCounterTests.cpp -o ObjectCounterTests

PowerBall:	PowerBall.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE PowerBall.cpp -o PowerBall

clean:
	rm ObjectCounterTests PowerBall
