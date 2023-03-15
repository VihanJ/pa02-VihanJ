CXX_FLAGS = -Wall

runMovies: main.cpp
	g++ ${CXX_FLAGS} main.cpp -o runMovies