#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Pelicula {
    string titulo;
    string sinopsis;
    vector<string> tags;

    Pelicula(const string& _titulo, const string& _sinopsis, const vector<string>& _tags)
            : titulo(_titulo), sinopsis(_sinopsis), tags(_tags) {}
};

class DataProcessor {
public:
    static vector<Pelicula> cargarPeliculasDesdeCSV(const string& rutaArchivo);
};

#endif // DATA_PROCESSOR_H
