#ifndef NUMERO_A_LETRAS_HPP
#define NUMERO_A_LETRAS_HPP

#include <string>

// Toma un número entero y lo convierte en su representación en palabras.
std::string convertirNumero(long long numero, bool esMil = false, bool esMillon = false);

// Convierte un monto en quetzales a letras, como se escribe en un cheque.
std::string convertirNumeroALetras(double numero);

#endif
