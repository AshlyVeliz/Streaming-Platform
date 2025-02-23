//
// Created by Ashly Veliz on 23/02/25.
//

#ifndef STREAMING_PLATFORM_SEARCHTREE_H
#define STREAMING_PLATFORM_SEARCHTREE_H
#include <iostream>
#include <vector>
#include "DataProcessor.h"
#include "RelevanceCalculator.h"

using namespace std;

class SearchTree {
private:
    struct Nodo {
        Pelicula pelicula;
        Nodo* izquierda;
        Nodo* derecha;
        int altura;

        Nodo(const Pelicula& _pelicula)
                : pelicula(_pelicula), izquierda(nullptr), derecha(nullptr), altura(1) {}
    };

    Nodo* raiz;

    // 🔹 Funciones internas para manejar el árbol AVL
    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* y);
    Nodo* rotarIzquierda(Nodo* x);
    Nodo* insertarNodo(Nodo* nodo, const Pelicula& pelicula);
    void buscarCoincidencias(Nodo* nodo, const string& consulta, vector<pair<Pelicula, int>>& resultados);

public:
    SearchTree();
    ~SearchTree();
    void insertar(const Pelicula& pelicula);
    vector<Pelicula> buscar(const string& consulta, int pagina = 0, int peliculasPorPagina = 5);
    void destruirArbol(Nodo* nodo);
};

#endif //STREAMING_PLATFORM_SEARCHTREE_H
