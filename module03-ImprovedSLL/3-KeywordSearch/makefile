KeywordSearch:	KeywordSearch.o Movie.o
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE KeywordSearch.o Movie.o -o KeywordSearch

KeywordSearch.o:	KeywordSearch.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE -c KeywordSearch.cpp -o KeywordSearch.o

Movie.o:	Movie.cpp
	g++ -std=c++11 -Wall -I ../../doctest -DDOCTEST_CONFIG_DISABLE -c Movie.cpp -o Movie.o

clean:
	rm KeywordSearch.o Movie.o KeywordSearch
