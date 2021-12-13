all:	ArrayBounds ParamCheck

ArrayBounds:	ArrayBounds.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE ArrayBounds.cpp -o ArrayBounds

ParamCheck:	ParamCheck.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE ParamCheck.cpp -o ParamCheck

clean:
	rm ArrayBounds ParamCheck *.class
