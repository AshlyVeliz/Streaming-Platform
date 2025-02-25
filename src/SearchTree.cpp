//
// Created by Ashly Veliz on 23/02/25.
//

#include "SearchTree.h"
#include <cmath>
#include <algorithm>

SearchTree::SearchTree() : raiz(nullptr) {}

SearchTree::~SearchTree() {
    destruirArbol(raiz);
}

//Función para liberar memoria del árbol
void SearchTree::destruirArbol(Nodo* nodo) {
    if (nodo) {
        destruirArbol(nodo->izquierda);
        destruirArbol(nodo->derecha);
        delete nodo;
    }
}

//Obtener altura del nodo
int SearchTree::obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

//Obtener balance del nodo
int SearchTree::obtenerBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
}

//Rotación Derecha
SearchTree::Nodo* SearchTree::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    return x;
}

//Rotación Izquierda
SearchTree::Nodo* SearchTree::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    return y;
}

//Insertar un nodo en el AVL Tree
SearchTree::Nodo* SearchTree::insertarNodo(Nodo* nodo, const Pelicula& pelicula) {
    if (nodo == nullptr) return new Nodo(pelicula);

    if (pelicula.titulo < nodo->pelicula.titulo) {
        nodo->izquierda = insertarNodo(nodo->izquierda, pelicula);
    } else if (pelicula.titulo > nodo->pelicula.titulo) {
        nodo->derecha = insertarNodo(nodo->derecha, pelicula);
    } else {
        return nodo;
    }

    //Actualizar altura
    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    //Obtener balance
    int balance = obtenerBalance(nodo);

    //Aplicar rotaciones si es necesario
    if (balance > 1 && pelicula.titulo < nodo->izquierda->pelicula.titulo)
        return rotarDerecha(nodo);

    if (balance < -1 && pelicula.titulo > nodo->derecha->pelicula.titulo)
        return rotarIzquierda(nodo);

    if (balance > 1 && pelicula.titulo > nodo->izquierda->pelicula.titulo) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && pelicula.titulo < nodo->derecha->pelicula.titulo) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

//Método público para insertar película
void SearchTree::insertar(const Pelicula& pelicula) {
    raiz = insertarNodo(raiz, pelicula);
}

//Buscar coincidencias en título y sinopsis
void SearchTree::buscarCoincidencias(Nodo* nodo, const string& consulta, vector<pair<Pelicula, int>>& resultados) {
    if (!nodo) return;

    //Calcular relevancia con RelevanceCalculator
    int puntuacion = RelevanceCalculator::calcularRelevancia(nodo->pelicula, consulta);
    if (puntuacion > 0) {
        resultados.emplace_back(nodo->pelicula, puntuacion);
    }

    //Buscar en subárbol izquierdo y derecho
    buscarCoincidencias(nodo->izquierda, consulta, resultados);
    buscarCoincidencias(nodo->derecha, consulta, resultados);
}

//Método público para buscar películas con paginación
                                    vector<Pelicula> SearchTree::buscar(const string& consulta, int pagina, int peliculasPorPagina) {
    vector<pair<Pelicula, int>> resultados;
    buscarCoincidencias(raiz, consulta, resultados);

    //Ordenar por relevancia (mayor puntuación primero)
    sort(resultados.begin(), resultados.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    //Paginación
    int inicio = pagina * peliculasPorPagina;
    int fin = min(inicio + peliculasPorPagina, (int)resultados.size());

    vector<Pelicula> peliculasPaginadas;
    for (int i = inicio; i < fin; i++) {
        peliculasPaginadas.push_back(resultados[i].first);
    }

    return peliculasPaginadas;
}
