#include <iostream>
#include <iomanip>
#include <string>

#include "numero_a_letras.hpp"

using namespace std;

// Imprime cada monto recibido como argumento junto con su representación en letras.
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " MONTO..." << endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        double monto = stod(argv[i]);
        cout << fixed << setprecision(2) << "Q " << monto << " = " << convertirNumeroALetras(monto) << endl;
    }
    return 0;
}
