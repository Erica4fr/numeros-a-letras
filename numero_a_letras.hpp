#ifndef NUMERO_A_LETRAS_HPP
#define NUMERO_A_LETRAS_HPP

#include <string>

// Convierte un número entero en palabras: 1234 -> "mil doscientos treinta y cuatro".
// Acepta todo el rango de long long, incluidos los negativos ("menos ...").
// Con apocopar, el "uno" final se escribe "un" ("veintiuno" -> "veintiún"),
// como cuando la cifra va antes de un sustantivo: "veintiún quetzales".
std::string convertirNumero(long long numero, bool apocopar = false);

// Convierte un monto en quetzales a letras, como se escribe en un cheque:
// 1500.75 -> "mil quinientos quetzales con setenta y cinco centavos".
// Lanza std::out_of_range si el monto es negativo, no es finito o llega a diez billones.
std::string convertirNumeroALetras(double monto);

#endif
