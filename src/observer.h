//
// Created by Darlene on 25/02/2025.
//

#ifndef STREAMING_PLATFORM_OBSERVER_H
#define STREAMING_PLATFORM_OBSERVER_H
#include "DataProcessor.h"

class Observer {
public:
    virtual void actualizar(const Pelicula& pelicula) = 0;
    virtual ~Observer() = default;
};
#endif //STREAMING_PLATFORM_OBSERVER_H
