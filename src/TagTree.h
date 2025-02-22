// Created by Ashly Veliz on 20/02/25.
#ifndef TAG_TREE_H
#define TAG_TREE_H

#include <iostream>
#include <vector>
#include "DataProcessor.h"  // Para acceder a la estructura Pelicula

using namespace std;

class TagTree {
private:
    struct Nodo {
        string tag;
        vector<Pelicula> peliculas;
        Nodo* izquierda;
        Nodo* derecha;

        Nodo(const string& _tag) : tag(_tag), izquierda(nullptr), derecha(nullptr) {}
    };

    Nodo* raiz;

    Nodo* insertarNodo(Nodo* nodo, const string& tag, const Pelicula& pelicula);
    Nodo* buscarNodo(Nodo* nodo, const string& tag);
    void imprimirEnOrden(Nodo* nodo);
    void liberarMemoria(Nodo* nodo);

public:
    TagTree();
    ~TagTree();
    void insertar(const string& tag, const Pelicula& pelicula);
    vector<Pelicula> buscarPeliculasPorTag(const string& tag);
    void imprimirTags();
};

#endif // TAG_TREE_H
