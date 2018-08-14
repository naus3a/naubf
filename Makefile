all: naubf

naubf: naubf.hpp naubf.cpp main.cpp
	g++ main.cpp -o naubf

clean: 
	rm -f naubf 
