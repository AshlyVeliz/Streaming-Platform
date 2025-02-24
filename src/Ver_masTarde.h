//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_VER_MASTARDE_H
#define STREAMING_PLATFORM_VER_MASTARDE_H
#include <stack>
#include "DataProcessor.h"  // Asegúrate de que Pelicula esté declarada aquí
using namespace std;

class Ver_masTarde {
private:
    stack<Pelicula> pila;
public:
    void agregar(const Pelicula& pelicula);
    void mostrar() const;
    void eliminar();
};


#endif //STREAMING_PLATFORM_VER_MASTARDE_H