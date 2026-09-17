CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2

numeros-a-letras: main.cpp numero_a_letras.cpp numero_a_letras.hpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp numero_a_letras.cpp

pruebas: pruebas.cpp numero_a_letras.cpp numero_a_letras.hpp
	$(CXX) $(CXXFLAGS) -o $@ pruebas.cpp numero_a_letras.cpp

test: pruebas
	./pruebas

clean:
	rm -f numeros-a-letras pruebas

.PHONY: test clean
