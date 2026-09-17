#include <cmath> // llround e isfinite para redondear montos a centavos.
#include <stdexcept> // out_of_range para rechazar montos que no se pueden representar.
#include <string> // Clase string para construir el resultado.

#include "numero_a_letras.hpp"

using namespace std;

// Arreglos de cadenas para convertir números a palabras
static const string unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
static const string especiales[] = {"diez", "once", "doce", "trece", "catorce", "quince", "dieciséis", "diecisiete", "dieciocho", "diecinueve"};
static const string veintes[] = {"veinte", "veintiuno", "veintidós", "veintitrés", "veinticuatro", "veinticinco", "veintiséis", "veintisiete", "veintiocho", "veintinueve"};
static const string decenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
static const string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};

// Escala larga del español: cada escala es un millón de veces la anterior.
struct Escala {
    unsigned long long valor;
    const char* singular;
    const char* plural;
};

static const Escala escalas[] = {
    {1000000000000000000ULL, "trillón", "trillones"},
    {1000000000000ULL, "billón", "billones"},
    {1000000ULL, "millón", "millones"},
};

// Montos a partir de este valor no conservan los centavos exactos en un double.
static const double MONTO_MAXIMO = 1e13;

// Agrega una palabra al resultado, separada por un solo espacio.
static void agregar(string& resultado, const string& palabra) {
    if (palabra.empty()) {
        return;
    }
    if (!resultado.empty()) {
        resultado += ' ';
    }
    resultado += palabra;
}

// Convierte un dígito del 1 al 9; con apocopar, el 1 se escribe "un".
static string convertirUnidad(int digito, bool apocopar) {
    return (digito == 1 && apocopar) ? "un" : unidades[digito];
}

// Convierte un número del 1 al 999.
static string convertirCentenas(int numero, bool apocopar) {
    if (numero == 100) {
        return "cien";
    }

    string resultado = centenas[numero / 100];
    int resto = numero % 100;

    if (resto >= 1 && resto <= 9) {
        agregar(resultado, convertirUnidad(resto, apocopar));
    } else if (resto >= 10 && resto <= 19) {
        agregar(resultado, especiales[resto - 10]);
    } else if (resto >= 20 && resto <= 29) {
        agregar(resultado, (resto == 21 && apocopar) ? "veintiún" : veintes[resto - 20]);
    } else if (resto >= 30) {
        agregar(resultado, decenas[resto / 10]);
        if (resto % 10 != 0) {
            agregar(resultado, "y");
            agregar(resultado, convertirUnidad(resto % 10, apocopar));
        }
    }
    return resultado;
}

// Convierte un número del 1 al 999 999.
static string convertirMiles(int numero, bool apocopar) {
    string resultado;
    int miles = numero / 1000;
    int resto = numero % 1000;

    // "mil", no "un mil"; y "veintiún mil", no "veintiuno mil"
    if (miles == 1) {
        resultado = "mil";
    } else if (miles > 1) {
        resultado = convertirCentenas(miles, true) + " mil";
    }

    if (resto > 0) {
        agregar(resultado, convertirCentenas(resto, apocopar));
    }
    return resultado;
}

string convertirNumero(long long numero, bool apocopar) {
    if (numero == 0) {
        return "cero";
    }

    string resultado;
    if (numero < 0) {
        resultado = "menos";
    }

    // Se usa el valor absoluto sin signo para que el mínimo de long long no desborde.
    unsigned long long restante = static_cast<unsigned long long>(numero);
    if (numero < 0) {
        restante = 0ULL - restante;
    }

    // Cada grupo de seis cifras se convierte por separado y recibe el nombre de su escala.
    for (const Escala& escala : escalas) {
        int grupo = static_cast<int>(restante / escala.valor);
        restante %= escala.valor;

        if (grupo == 1) {
            agregar(resultado, string("un ") + escala.singular);
        } else if (grupo > 1) {
            agregar(resultado, convertirMiles(grupo, true) + " " + escala.plural);
        }
    }

    if (restante > 0) {
        agregar(resultado, convertirMiles(static_cast<int>(restante), apocopar));
    }
    return resultado;
}

string convertirNumeroALetras(double monto) {
    if (!isfinite(monto) || monto < 0 || monto >= MONTO_MAXIMO) {
        throw out_of_range("El monto debe estar entre 0 y 9 999 999 999 999.99");
    }

    // Redondear una sola vez a centavos evita que 1.999 se convierta en "1 quetzal con 100 centavos".
    long long totalCentavos = llround(monto * 100);
    long long parteEntera = totalCentavos / 100;
    long long parteDecimal = totalCentavos % 100;

    string cantidadEnLetras = convertirNumero(parteEntera, true);

    // "un millón de quetzales", pero "un millón quinientos mil quetzales"
    if (parteEntera != 0 && parteEntera % 1000000 == 0) {
        cantidadEnLetras += " de";
    }
    cantidadEnLetras += (parteEntera == 1) ? " quetzal" : " quetzales";

    if (parteDecimal == 0) {
        cantidadEnLetras += (parteEntera == 1) ? " exacto" : " exactos";
    } else {
        cantidadEnLetras += " con " + convertirNumero(parteDecimal, true);
        cantidadEnLetras += (parteDecimal == 1) ? " centavo" : " centavos";
    }
    return cantidadEnLetras;
}
