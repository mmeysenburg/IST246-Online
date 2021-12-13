all: SpellCheck BadSpellCheck

BadSpellCheck:	BadSpellCheck.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE BadSpellCheck.cpp -o BadSpellCheck

SpellCheck:	SpellCheck.cpp
	g++ -std=c++11 -Wall -O3 -I ../../doctest -DDOCTEST_CONFIG_DISABLE SpellCheck.cpp -o SpellCheck

clean:
	rm BadSpellCheck SpellCheck
