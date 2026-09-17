CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2

numeros-a-letras: main.cpp numero_a_letras.cpp numero_a_letras.hpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp numero_a_letras.cpp

clean:
	rm -f numeros-a-letras

.PHONY: clean
