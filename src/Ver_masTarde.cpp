#include "Ver_masTarde.h"
#include<iostream>
using namespace std;
void Ver_masTarde::agregar(const Pelicula& pelicula) {
    pila.push(pelicula);
    cout << "✅ '" << pelicula.titulo << "' se agregó a 'Ver más tarde'.\n";
}

void Ver_masTarde::mostrar() const {
    if (pila.empty()) {
        cout << "No tienes películas en 'Ver más tarde'.\n";
        return;
    }
    stack<Pelicula> copia = pila;
    while (!copia.empty()) {
        cout << "- " << copia.top().titulo << endl;
        copia.pop();
    }
}

void Ver_masTarde::eliminar() {
    if (pila.empty()) {
        cout << "No hay películas para eliminar.\n";
        return;
    }
    cout << " Se eliminó '" << pila.top().titulo << "' de 'Ver más tarde'.\n";
    pila.pop();
}