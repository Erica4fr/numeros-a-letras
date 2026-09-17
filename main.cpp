#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "numero_a_letras.hpp"

using namespace std;

// Imprime cada valor recibido como argumento junto con su representación en letras.
// Por defecto los valores son montos en quetzales; con -n son números enteros.
int main(int argc, char* argv[]) {
    bool soloNumeros = argc > 1 && string(argv[1]) == "-n";
    int primero = soloNumeros ? 2 : 1;

    if (argc <= primero) {
        cerr << "Uso: " << argv[0] << " MONTO..." << endl;
        cerr << "     " << argv[0] << " -n ENTERO..." << endl;
        return 1;
    }

    int estado = 0;
    for (int i = primero; i < argc; i++) {
        string texto = argv[i];
        size_t leidos = 0;
        try {
            if (soloNumeros) {
                long long numero = stoll(texto, &leidos);
                if (leidos != texto.size()) {
                    throw invalid_argument(texto);
                }
                cout << numero << " = " << convertirNumero(numero) << endl;
            } else {
                double monto = stod(texto, &leidos);
                if (leidos != texto.size()) {
                    throw invalid_argument(texto);
                }
                string enLetras = convertirNumeroALetras(monto);
                cout << fixed << setprecision(2) << "Q " << monto << " = " << enLetras << endl;
            }
        } catch (const invalid_argument&) {
            cerr << "No es un número válido: " << texto << endl;
            estado = 1;
        } catch (const out_of_range&) {
            cerr << "Fuera de rango: " << texto << endl;
            estado = 1;
        }
    }
    return estado;
}
