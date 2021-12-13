all:	UserAuth

UserAuth.o:	UserAuth.cpp
	g++ -std=c++11 -Wall -c -I ../../doctest -DDOCTEST_CONFIG_DISABLE UserAuth.cpp -o UserAuth.o
	
User.o:	User.cpp
	g++ -std=c++11 -Wall -c User.cpp -o User.o
	
UserAuth:	UserAuth.o User.o
	g++ -std=c++11 -Wall UserAuth.o User.o -o UserAuth

clean:
	rm UserAuth *.o
