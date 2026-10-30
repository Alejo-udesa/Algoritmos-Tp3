#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <cstddef>

#include "funcion_hash.h"

#include <vector>

// TAD TablaHash<K, V>: tabla de hash con direccionamiento cerrado.
//
// Guarda pares <clave, valor> repartidos en buckets: el par de una clave esta
// en el bucket numero funcion_hash(clave) % capacidad().
//
// Requisitos sobre los tipos:
//   - K: se puede copiar, comparar con == y existe funcion_hash(K).
//   - V: se puede copiar.
//
// Invariante de representacion:
//   COMPLETAR: escriban aca el invariante de la representacion que elijan.     a revisar
//
// Complejidades: n es la cantidad de claves guardadas y c la capacidad.
// "Promedio" supone que la funcion de hash reparte las claves de manera
// uniforme y que calcularla (y comparar dos claves) cuesta O(1).
template <typename K, typename V>
class TablaHash {
  private:
    // COMPLETAR: la representacion la eligen ustedes (que guardan, y que hay
    // en cada bucket). Pueden agregar tambien funciones auxiliares privadas.
    // Lo que el Iterador necesite de aca tiene que estar declarado antes que el.

    struct Nodo {
        K clave;
        V valor;
        Nodo* siguiente;
        Nodo(const K& k, const V& v, Nodo* sig = nullptr)
            : clave(k), valor(v), siguiente(sig) {}
    };

    std::vector<Nodo*> _tabla;
    size_t _cantidad;
    size_t _capacidad;
    //void redimensionar(size_t nueva_capacidad); a revisar HABRIA Q AGREGAR ESTA FUNCION PARA CDO LOS BUCKETS SE LLENAN

  public:
    static const size_t FACTOR_DE_CARGA_MAXIMO = 2;

    // Pre:  capacidad_inicial >= 1.
    // Post: crea una tabla vacia, con capacidad_inicial buckets.
    // Costo: O(capacidad_inicial).
    TablaHash(size_t capacidad_inicial);

    // Post: libera toda la memoria pedida por la tabla.
    // Costo: O(n + c) en peor caso.
    ~TablaHash();

    // Copiar una tabla copiaria los punteros y no su contenido: lo prohibimos.
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;

    // Pre:  la clave NO esta en la tabla.
    // Post: la tabla tiene ademas el par <clave, valor>, y
    //       cantidad() <= FACTOR_DE_CARGA_MAXIMO * capacidad().
    // Costo: O(1) amortizado (en peor caso O(n), cuando toca redimensionar).
    void insertar(const K& clave, const V& valor);

    // Pre:  la clave esta en la tabla.
    // Post: la tabla ya no tiene la clave (ni su valor).
    // Costo: O(1) en promedio, O(n) en peor caso.
    void eliminar(const K& clave);

    // Pre:  -
    // Post: si la clave esta, devuelve un puntero a su valor (que se puede
    //       usar para leerlo o modificarlo); si no, devuelve nullptr.
    //       El puntero deja de ser valido al insertar o eliminar.
    // Costo: O(1) en promedio, O(n) en peor caso.
    V* buscar(const K& clave);

    // Post: devuelve la cantidad de claves guardadas. Costo: O(1).
    size_t cantidad();

    // Post: devuelve la cantidad de buckets. Costo: O(1).
    size_t capacidad();

    // Post: devuelve la cantidad de claves que comparten bucket con alguna
    //       clave que llego antes, es decir:
    //       cantidad() - (cantidad de buckets que no estan vacios).
    // Costo: O(c) en peor caso.
    size_t colisiones();

    // Iterador de la tabla: recorre todos los pares <clave, valor>, cada uno
    // exactamente una vez, en algun orden (ver TAD Iterador en el enunciado).
    // Deja de ser valido si se inserta o se elimina en la tabla.
    //
    // Invariante de representacion:
    //   COMPLETAR: escriban aca el invariante de la representacion que elijan.
    class Iterador {
      private:
        // COMPLETAR: la representacion la eligen ustedes. Desde aca se puede
        // usar la parte privada de la tabla.
        TablaHash* _origen;
        size_t _bucket;
        Nodo* _actual;

        void saltar_buckets_vacios() {
            while (_actual == nullptr && _bucket + 1 < _origen->_capacidad) {
                _bucket++;
                _actual = _origen->_tabla[_bucket];
            }
        }

        // Para que crear_iterador() pueda armar el iterador.
        friend class TablaHash;

      public:
        // Pre:  -
        // Post: indica si quedan pares por recorrer.
        // Costo: O(1).
        bool hay_mas() {
            // COMPLETAR
            if (_actual != nullptr){
                return true;
            }
            return false;
        }

        // Pre:  hay_mas().
        // Post: devuelve la clave del par actual, sin modificar el iterador.
        // Costo: O(1).
        K clave() {
            // COMPLETAR (reemplazar la linea de abajo)
            return _actual->clave;
        }

        // Pre:  hay_mas().
        // Post: devuelve el valor del par actual, sin modificar el iterador.
        // Costo: O(1).
        V valor() {
            // COMPLETAR (reemplazar la linea de abajo)
            return _actual->valor;
        }

        // Pre:  hay_mas().
        // Post: el iterador pasa al par siguiente (o al final, si no hay mas).
        // Costo: O(c) en peor caso. Recorrer la tabla entera (crear el
        //        iterador y avanzar hasta el final) cuesta O(n + c).
        void avanzar() {
            // COMPLETAR
            _actual = _actual->siguiente;
            this->saltar_buckets_vacios();
        }
    };

    // Pre:  -
    // Post: devuelve un iterador al primer par de la tabla (si la tabla esta
    //       vacia, el iterador ya esta al final).
    // Costo: O(c) en peor caso.
    Iterador crear_iterador();
};

// ---------------------------------------------------------------------------
// Implementacion. Al ser una clase template, va en el mismo .h.
// ---------------------------------------------------------------------------

template <typename K, typename V>
TablaHash<K, V>::TablaHash(size_t capacidad_inicial) {
    // COMPLETAR
    _capacidad = capacidad_inicial;
    _cantidad = 0;
    _tabla = std::vector<typename TablaHash<K, V>::Nodo*>(capacidad_inicial, nullptr);
}

// a revisar HABRIA QUE IMPLEMENTAR UNA FUNCION REDIMENSIONAR PARA CDO SE LLENAN LOS BUCKETS PERO NO SE XQ NO ESTA EN LA ESTRUCTURA

template <typename K, typename V>
TablaHash<K, V>::~TablaHash() {
    // COMPLETAR
    for(typename TablaHash<K, V>::Nodo* actual : _tabla) {
        while(actual!=nullptr) {
            typename TablaHash<K, V>::Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

}

template <typename K, typename V>
void TablaHash<K, V>::insertar(const K& clave, const V& valor) {
    // COMPLETAR
    //if (_cantidad +1 > FACTOR_DE_CARGA_MAXIMO * _capacidad){
    //this->redimensionar(_capacidad*2);
    //}
    size_t indice = funcion_hash(clave) % _capacidad;
    typename TablaHash<K, V>::Nodo* nuevo = new typename TablaHash<K, V>::Nodo(clave, valor, _tabla[indice]);
    _tabla[indice] = nuevo;
    _cantidad++;
}

template <typename K, typename V>
void TablaHash<K, V>::eliminar(const K& clave) {
    // COMPLETAR
    size_t indice = funcion_hash(clave) % _capacidad;
    typename TablaHash<K, V>::Nodo* actual = _tabla[indice];
    typename TablaHash<K, V>::Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (anterior == nullptr) {
                _tabla[indice] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            _cantidad--;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
        
    }
    return;
}

template <typename K, typename V>
V* TablaHash<K, V>::buscar(const K& clave) {
    // COMPLETAR
    size_t indice = funcion_hash(clave) % _capacidad;
    typename TablaHash<K, V>::Nodo* actual = _tabla[indice];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return &(actual->valor);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

template <typename K, typename V>
size_t TablaHash<K, V>::cantidad() {
    return _cantidad;
}

template <typename K, typename V>
size_t TablaHash<K, V>::capacidad() {
    // COMPLETAR
    return _capacidad;
}

template <typename K, typename V>
size_t TablaHash<K, V>::colisiones() 
{
    int buckets_con_elementos = 0;
    for (int i = 0; i<_capacidad; i++) {
        if (_tabla[i]!=nullptr) {
            buckets_con_elementos++;
        }
    }
    return cantidad() - buckets_con_elementos;
}

// El "typename" le avisa al compilador que TablaHash<K, V>::Iterador es un tipo.
template <typename K, typename V>
typename TablaHash<K, V>::Iterador TablaHash<K, V>::crear_iterador() {
    Iterador it;
    // COMPLETAR
    it._origen = this;
    it._bucket = 0;
    it._actual = _tabla[0];
    it.saltar_buckets_vacios();
    return it;
}

#endif
