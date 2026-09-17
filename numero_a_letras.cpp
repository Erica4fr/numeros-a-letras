#include <string> // Proporciona funcionalidad para trabajar con cadenas de caracteres, como la clase string y varias funciones relacionadas con manipulación de cadenas.
#include <cmath> // Proporciona funciones matemáticas comunes, como funciones trigonométricas, logarítmicas y exponenciales.

#include "numero_a_letras.hpp"

using namespace std;

// Arreglos de cadenas para convertir números a palabras
string unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
string especiales[] = {"diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete", "dieciocho", "diecinueve"};
string decenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};

// Toma un número entero y lo convierte en su representación en palabras. "Acepta números de hasta billones"
string convertirNumero(long long numero, bool esMil, bool esMillon) {
    string resultado;

    // Convertir millones
    if (numero >= 1000000) {
        if (numero / 1000000 == 1) {
            resultado += "un millon ";
        } else {
            resultado += convertirNumero(numero / 1000000, false, true) + " millones ";
        }
        numero %= 1000000;
    }
    
    // Convertir miles
    if (numero >= 1000) {
        if (numero == 100000) {
            resultado += "cien mil ";
        } else {
            resultado += convertirNumero(numero / 1000, true) + " mil ";
        }
        numero %= 1000;
    }

    // Convertir centenas
    if (numero >= 100) {
        resultado += centenas[numero / 100] + " ";
        numero %= 100;
    }

    // Convertir números del 10 al 19
    if (numero >= 10 && numero <= 19) {
        resultado += especiales[numero - 10] + " ";
    }

    // Convertir decenas
    else if (numero >= 20) {
        resultado += decenas[numero / 10] + " ";
        numero %= 10;
    }

    // Convertir unidades
    if (numero >= 1 && numero <= 9) {
        resultado += unidades[numero] + " ";
    }

    // Eliminar espacio adicional despues de "mil" o "millon" si no es seguido por otro numero
    if ((esMil || esMillon) && numero == 0)
        resultado.pop_back();

    return resultado;
}

// Funcion para convertir un numero en letras (solo admite numeros hasta billones)
string convertirNumeroALetras(double numero) {


    long long parteEntera = static_cast<long long>(numero);
    long long parteDecimal = static_cast<long long>(round((numero - parteEntera) * 100)); // Convertir a entero sin aproximar


    string cantidadEnLetras;

    // Convertir la parte entera
    if (parteEntera == 0) {
        cantidadEnLetras = "cero";
    } else {
        cantidadEnLetras += convertirNumero(parteEntera);
        if (parteEntera == 1 && parteEntera < 1000000)
            cantidadEnLetras += " quetzal ";
    else if (parteEntera > 1 && parteEntera < 1000000)
    cantidadEnLetras += " quetzales ";
    }

    // Convertir la parte decimal
    if (parteDecimal > 0) {
    if (parteDecimal == 1)
        cantidadEnLetras += "con un centavo";
    else
        cantidadEnLetras += "con " + convertirNumero(parteDecimal) + " centavos";
    }
    else {
        cantidadEnLetras += "exactos";
    }
    return cantidadEnLetras;
}
