all: naubf

naubf: naubf.hpp main.cpp
	g++ main.cpp -o naubf

clean: 
	rm -f naubf 
