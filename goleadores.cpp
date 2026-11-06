#include "goleadores.h"

#include <iostream>
#include <vector>

namespace {
    struct Par {
        std::string nombre;
        int goles;
    };

    bool viene_antes(const Par& a, const Par& b) {
        if (a.goles != b.goles) {
            return a.goles > b.goles;
        }
        return a.nombre < b.nombre;
    }

    void juntar_pares(Diccionario<std::string, int>& dic,
                      std::vector<Par>& pares) {
        Diccionario<std::string, int>::Iterador it = dic.crear_iterador();
        while (it.hay_mas()) {
            Par p;
            p.nombre = it.clave();
            p.goles = it.valor();
            pares.push_back(p);
            it.avanzar();
        }
    }

    void ordenar_por_nombre(std::vector<Par>& pares) {
        for (size_t i = 1; i < pares.size(); i++) {
            Par actual = pares[i];
            size_t j = i;
            while (j > 0 && pares[j - 1].nombre > actual.nombre) {
                pares[j] = pares[j - 1];
                j--;
            }
            pares[j] = actual;
        }
    }

    void ordenar_por_goles(std::vector<Par>& pares) {
        for (size_t i = 1; i < pares.size(); i++) {
            Par actual = pares[i];
            size_t j = i;
            while (j > 0 && viene_antes(actual, pares[j - 1])) {
                pares[j] = pares[j - 1];
                j--;
            }
            pares[j] = actual;
        }
    }
}

Goleadores::Goleadores() {
    // COMPLETAR (si hace falta)
}

void Goleadores::anotar_gol(const std::string& jugador) {
    // COMPLETAR
    int goles_previos = 0;
    if (goles_por_jugador.pertenece(jugador)) {
        goles_previos = goles_por_jugador.obtener(jugador);
    }
    int goles_nuevos = goles_previos + 1;

    int goles_del_maximo = 0;
    if (maximo != "") {
        goles_del_maximo = goles_por_jugador.obtener(maximo);
    }

    goles_por_jugador.insertar(jugador, goles_nuevos);  // cubre ambos casos

    if (maximo == "" || goles_nuevos > goles_del_maximo) {
        maximo = jugador;
    }
}

int Goleadores::goles(const std::string& jugador) {
    // COMPLETAR
    if (goles_por_jugador.pertenece(jugador)) {
        return goles_por_jugador.obtener(jugador);
    }
    return 0;
}

size_t Goleadores::cantidad_de_jugadores() {
    // COMPLETAR
    return goles_por_jugador.cantidad();
}

std::string Goleadores::maximo_goleador() {
    // COMPLETAR
    return goles_por_jugador(maximo);
}

void Goleadores::imprimir_por_nombre() {
    // OPTATIVO
    std::vector<Par> pares;
    juntar_pares(goles_por_jugador, pares);
    ordenar_por_nombre(pares);

    for (size_t i = 0; i < pares.size(); i++) {
        std::cout << pares[i].nombre << ": " << pares[i].goles << std::endl;
    }
}

void Goleadores::imprimir_por_goles() {
    // OPTATIVO
    std::vector<Par> pares;
    juntar_pares(goles_por_jugador, pares);
    ordenar_por_goles(pares);

    for (size_t i = 0; i < pares.size(); i++) {
        std::cout << pares[i].nombre << ": " << pares[i].goles << std::endl;
    }
}
