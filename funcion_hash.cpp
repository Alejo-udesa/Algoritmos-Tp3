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

/*a revisar, faltan proponer dos funciones de hash, una mala y otra que masomenos funcione, SECCION 3.5 (No hay una única respuesta, así que hay que probar. El programa explorar_hash.cpp carga en una
TablaHash los jugadores del archivo de datos del grupo y muestra la cantidad de claves, la capacidad final y
las colisiones.
1. Proponer al menos tres funciones de hash distintas para strings (alguna deliberadamente mala, por
ejemplo una que sólo mire el largo o la primera letra).
2. Para cada una, medir las colisiones sobre el archivo del grupo, con al menos dos capacidades iniciales
distintas.
3. Volcar los resultados en una tabla y explicar en pocas líneas qué función eligieron y por qué. ¿Qué tienen
en común las claves que colisionan con las funciones malas? ¿Cambia algo si la capacidad es potencia de
2?
Como referencia: si la función repartiera las claves de manera perfectamente uniforme, con n claves y c buckets
se esperan aproximadamente n −c(1 −(1 −1/c)n) colisiones.))*/
