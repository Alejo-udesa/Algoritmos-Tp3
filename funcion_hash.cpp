#include "funcion_hash.h"

size_t funcion_hash(const std::string& clave) {
    // COMPLETAR
    int k = 3821;
    for (int i = 0; i < clave.size(); i++) {
        k = ((k << 5) + k) + clave[i];
    }
    return k;
}

size_t funcion_hash(int clave) {
    int k = 3821;
    for (int i = 0; i < clave; i++) {
        double cifra_temp = clave;
        for (int j = 1; j <= i; j++) {cifra_temp *= 0.1;} 
        int cifra = (int)cifra_temp  ;       // a revisar el uso del casteo, capaz conviene static_cast
        k = ((k << 5) + k) + clave;
    }
    return k;
}
