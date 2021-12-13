all:	BSTTests LastWord

LastWord:	LastWord.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE LastWord.cpp -o LastWord

BSTTests:	BSTTests.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_IMPLEMENT_WITH_MAIN BSTTests.cpp -o BSTTests

clean:
	rm BSTTests LastWord
