//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_LISTAPILA_H
#define STREAMING_PLATFORM_LISTAPILA_H
#include <stack>
#include <iostream>
using namespace std;

template<typename T>
class ListaPila {
private:
    stack<T> pila;

public:
    void agregar(const T& elemento, const string& nombreLista);
    void mostrar(const string& nombreLista) const;
    void eliminar(const string& nombreLista);
};

template<typename T>
void ListaPila<T>::agregar(const T& elemento, const string& nombreLista) {
    pila.push(elemento);
    cout << "'" << elemento.titulo << "' se agrego a '" << nombreLista << "'.\n";
}

template<typename T>
void ListaPila<T>::mostrar(const string& nombreLista) const {
    if (pila.empty()) {
        cout << "No tienes elementos en '" << nombreLista << "'.\n";
        return;
    }

    stack<T> copia = pila;
    cout << "Elementos en '" << nombreLista << "':\n";
    while (!copia.empty()) {
        cout << "- " << copia.top().titulo << endl;
        copia.pop();
    }
}

template<typename T>
void ListaPila<T>::eliminar(const string& nombreLista) {
    if (pila.empty()) {
        cout << " No hay elementos para eliminar en '" << nombreLista << "'.\n";
        return;
    }
    cout << " Se elimino '" << pila.top().titulo << "' de '" << nombreLista << "'.\n";
    pila.pop();
}
#endif //STREAMING_PLATFORM_LISTAPILA_H
