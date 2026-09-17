#include <climits>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "numero_a_letras.hpp"

using namespace std;

static int total = 0;
static int fallos = 0;

// Compara el resultado obtenido con el esperado y muestra la diferencia si no coinciden.
static void comprobar(const string& caso, const string& obtenido, const string& esperado) {
    total++;
    if (obtenido != esperado) {
        fallos++;
        cout << "FALLA " << caso << endl;
        cout << "  esperado: [" << esperado << "]" << endl;
        cout << "  obtenido: [" << obtenido << "]" << endl;
    }
}

struct CasoEntero {
    long long numero;
    const char* esperado;
};

struct CasoMonto {
    double monto;
    const char* esperado;
};

int main() {
    const CasoEntero enteros[] = {
        {0, "cero"},
        {1, "uno"},
        {9, "nueve"},
        {10, "diez"},
        {15, "quince"},
        {16, "dieciséis"},
        {20, "veinte"},
        {21, "veintiuno"},
        {22, "veintidós"},
        {23, "veintitrés"},
        {26, "veintiséis"},
        {29, "veintinueve"},
        {30, "treinta"},
        {31, "treinta y uno"},
        {45, "cuarenta y cinco"},
        {99, "noventa y nueve"},
        {100, "cien"},
        {101, "ciento uno"},
        {110, "ciento diez"},
        {121, "ciento veintiuno"},
        {200, "doscientos"},
        {555, "quinientos cincuenta y cinco"},
        {999, "novecientos noventa y nueve"},
        {1000, "mil"},
        {1001, "mil uno"},
        {1100, "mil cien"},
        {1999, "mil novecientos noventa y nueve"},
        {2000, "dos mil"},
        {10000, "diez mil"},
        {21000, "veintiún mil"},
        {31000, "treinta y un mil"},
        {100000, "cien mil"},
        {100500, "cien mil quinientos"},
        {101000, "ciento un mil"},
        {121000, "ciento veintiún mil"},
        {999999, "novecientos noventa y nueve mil novecientos noventa y nueve"},
        {1000000, "un millón"},
        {1000001, "un millón uno"},
        {1500000, "un millón quinientos mil"},
        {2000000, "dos millones"},
        {21000000, "veintiún millones"},
        {100000000, "cien millones"},
        {1000000000, "mil millones"},
        {2500000000, "dos mil quinientos millones"},
        {1000000000000, "un billón"},
        {2000000000000, "dos billones"},
        {1000000000000000000, "un trillón"},
        {-5, "menos cinco"},
        {-21, "menos veintiuno"},
        {LLONG_MAX, "nueve trillones doscientos veintitrés mil trescientos setenta y dos billones "
                    "treinta y seis mil ochocientos cincuenta y cuatro millones "
                    "setecientos setenta y cinco mil ochocientos siete"},
        {LLONG_MIN, "menos nueve trillones doscientos veintitrés mil trescientos setenta y dos billones "
                    "treinta y seis mil ochocientos cincuenta y cuatro millones "
                    "setecientos setenta y cinco mil ochocientos ocho"},
    };
    for (const CasoEntero& caso : enteros) {
        comprobar(to_string(caso.numero), convertirNumero(caso.numero), caso.esperado);
    }

    const CasoEntero apocopados[] = {
        {0, "cero"},
        {1, "un"},
        {11, "once"},
        {21, "veintiún"},
        {31, "treinta y un"},
        {101, "ciento un"},
        {1001, "mil un"},
        {21021, "veintiún mil veintiún"},
    };
    for (const CasoEntero& caso : apocopados) {
        comprobar(to_string(caso.numero) + " apocopado", convertirNumero(caso.numero, true), caso.esperado);
    }

    const CasoMonto montos[] = {
        {0.00, "cero quetzales exactos"},
        {0.01, "cero quetzales con un centavo"},
        {0.29, "cero quetzales con veintinueve centavos"},
        {0.50, "cero quetzales con cincuenta centavos"},
        {1.00, "un quetzal exacto"},
        {1.01, "un quetzal con un centavo"},
        {1.999, "dos quetzales exactos"},
        {2.00, "dos quetzales exactos"},
        {2.21, "dos quetzales con veintiún centavos"},
        {21.00, "veintiún quetzales exactos"},
        {31.31, "treinta y un quetzales con treinta y un centavos"},
        {100.00, "cien quetzales exactos"},
        {1999.99, "mil novecientos noventa y nueve quetzales con noventa y nueve centavos"},
        {4760.75, "cuatro mil setecientos sesenta quetzales con setenta y cinco centavos"},
        {1000000.00, "un millón de quetzales exactos"},
        {1500000.00, "un millón quinientos mil quetzales exactos"},
        {2000000.50, "dos millones de quetzales con cincuenta centavos"},
        {1000000000.00, "mil millones de quetzales exactos"},
        {9999999999999.99, "nueve billones novecientos noventa y nueve mil novecientos noventa y nueve millones "
                           "novecientos noventa y nueve mil novecientos noventa y nueve quetzales "
                           "con noventa y nueve centavos"},
    };
    for (const CasoMonto& caso : montos) {
        comprobar("Q " + to_string(caso.monto), convertirNumeroALetras(caso.monto), caso.esperado);
    }

    const double invalidos[] = {-0.01, 1e13, NAN, INFINITY};
    for (double monto : invalidos) {
        total++;
        try {
            convertirNumeroALetras(monto);
            fallos++;
            cout << "FALLA Q " << monto << " debía lanzar out_of_range" << endl;
        } catch (const out_of_range&) {
        }
    }

    cout << (total - fallos) << " de " << total << " pruebas pasaron" << endl;
    return fallos == 0 ? 0 : 1;
}
