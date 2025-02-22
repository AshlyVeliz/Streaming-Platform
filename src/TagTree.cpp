// Created by Ashly Veliz on 20/02/25.
#include "TagTree.h"

// Constructor
TagTree::TagTree() : raiz(nullptr) {}

// Destructor: Liberar memoria del árbol
TagTree::~TagTree() {
    liberarMemoria(raiz);
}

// Función auxiliar para liberar memoria
void TagTree::liberarMemoria(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberarMemoria(nodo->izquierda);
    liberarMemoria(nodo->derecha);
    delete nodo;
}

// Insertar un tag en el árbol (ordenado alfabéticamente)
TagTree::Nodo* TagTree::insertarNodo(Nodo* nodo, const string& tag, const Pelicula& pelicula) {
    if (nodo == nullptr) {
        Nodo* nuevoNodo = new Nodo(tag);
        nuevoNodo->peliculas.push_back(pelicula);
        return nuevoNodo;
    }

    if (tag < nodo->tag) {
        nodo->izquierda = insertarNodo(nodo->izquierda, tag, pelicula);
    } else if (tag > nodo->tag) {
        nodo->derecha = insertarNodo(nodo->derecha, tag, pelicula);
    } else {
        nodo->peliculas.push_back(pelicula);
    }

    return nodo;
}

// Función pública para insertar una película en los tags correspondientes
void TagTree::insertar(const string& tag, const Pelicula& pelicula) {
    raiz = insertarNodo(raiz, tag, pelicula);
}

// Buscar un tag en el árbol
TagTree::Nodo* TagTree::buscarNodo(Nodo* nodo, const string& tag) {
    if (nodo == nullptr || nodo->tag == tag) {
        return nodo;
    }

    if (tag < nodo->tag) {
        return buscarNodo(nodo->izquierda, tag);
    }
    return buscarNodo(nodo->derecha, tag);
}

// Función pública para buscar películas por tag
vector<Pelicula> TagTree::buscarPeliculasPorTag(const string& tag) {
    Nodo* nodo = buscarNodo(raiz, tag);
    if (nodo) {
        return nodo->peliculas;
    }
    return {};  // Retorna un vector vacío si el tag no existe
}

// Función auxiliar para imprimir el árbol en orden (para pruebas)
void TagTree::imprimirEnOrden(Nodo* nodo) {
    if (nodo == nullptr) return;
    imprimirEnOrden(nodo->izquierda);
    cout << "#" << nodo->tag << " -> " << nodo->peliculas.size() << " películas" << endl;
    imprimirEnOrden(nodo->derecha);
}

// Función pública para imprimir todos los tags y cuántas películas tienen
void TagTree::imprimirTags() {
    imprimirEnOrden(raiz);
}
