# Números a letras

Convierte números enteros y montos en quetzales a su representación en palabras, en español.

```
$ ./numeros-a-letras 4760.75
Q 4760.75 = cuatro mil setecientos sesenta quetzales con setenta y cinco centavos
```

## Historia

Esta función fue el primer reto de programación al que me enfrenté en la carrera. La escribí en 2023 para el proyecto final de Programación 1 en la UMG: una planilla de trabajadores en C++ que calculaba sueldos e imprimía cheques con el monto en letras. De todo ese proyecto, convertir un número en palabras fue lo más difícil y lo que más valoro, así que este repositorio se queda solo con esa parte.

- [Código original de 2023](https://github.com/Erica4fr/numeros-a-letras/blob/7b54d75c8c9808dc76f505241acbc99d0e6005ec/Planilla_de_trabajadores.cpp#L257-L342), dentro de la planilla completa.
- [Correcciones posteriores](https://github.com/Erica4fr/numeros-a-letras/compare/299151d7013446567dbe16cb586c4ebf4cfe77d1...cbb7eb85e396ac45489615de867d08b2c6cf66a0), comparadas con la función tal como la escribí.

La idea de la versión original se mantiene: dividir el número en grupos y reutilizar la misma función para cada uno. Lo que se corrigió:

| Entrada | Versión de 2023 | Versión actual |
|---|---|---|
| 21 | veinte uno | veintiuno |
| 31 | treinta uno | treinta y uno |
| 100 | ciento | cien |
| 1000 | uno mil | mil |
| 21 000 | veinte uno mil | veintiún mil |
| 100 500 | ciento mil quinientos | cien mil quinientos |
| 1 000 000 000 000 | un millon millones | un billón |
| Q 1.00 | uno quetzal exactos | un quetzal exacto |
| Q 1.999 | uno quetzal con ciento centavos | dos quetzales exactos |
| Q 1 500 000.00 | un millon quinientos mil exactos | un millón quinientos mil quetzales exactos |

## Uso

Requiere un compilador de C++17 y `make`.

```
make
./numeros-a-letras 4760.75 21 1000000
./numeros-a-letras -n 1234 21000 1000000000000
```

```
Q 4760.75 = cuatro mil setecientos sesenta quetzales con setenta y cinco centavos
Q 21.00 = veintiún quetzales exactos
Q 1000000.00 = un millón de quetzales exactos
1234 = mil doscientos treinta y cuatro
21000 = veintiún mil
1000000000000 = un billón
```

Sin opciones, cada argumento es un monto en quetzales. Con `-n`, cada argumento es un número entero.

## Como biblioteca

Copia `numero_a_letras.hpp` y `numero_a_letras.cpp` a tu proyecto:

```cpp
#include "numero_a_letras.hpp"

convertirNumero(1234);           // "mil doscientos treinta y cuatro"
convertirNumero(21, true);       // "veintiún"
convertirNumeroALetras(2000000); // "dos millones de quetzales exactos"
```

- `convertirNumero(long long numero, bool apocopar = false)` acepta todo el rango de `long long`, incluidos los negativos. Con `apocopar`, el "uno" final se escribe "un", como cuando la cifra va antes de un sustantivo: "veintiún quetzales".
- `convertirNumeroALetras(double monto)` redondea a centavos y acepta montos desde 0 hasta 9 999 999 999 999.99. Fuera de ese rango, o si el monto no es finito, lanza `std::out_of_range`; a partir de diez billones un `double` ya no conserva los centavos exactos.

## Reglas que aplica

- Del 16 al 29 se escribe en una palabra, con tilde cuando corresponde: dieciséis, veintidós, veintitrés.
- Del 31 en adelante, las decenas y las unidades se unen con "y": treinta y uno.
- 100 exacto es "cien"; de 101 a 199, "ciento".
- Antes de "mil", de una escala o de "quetzales", "uno" se acorta a "un": veintiún mil, ciento un millones.
- Escala larga del español: millón (10⁶), billón (10¹²) y trillón (10¹⁸).
- Los millones exactos llevan "de": un millón de quetzales.

## Pruebas

```
make test
```

Las pruebas cubren enteros desde cero hasta los extremos de `long long`, la apócope, montos con y sin centavos, el redondeo y los montos fuera de rango.
