#include "DataProcessor.h"

vector<Pelicula> DataProcessor::cargarPeliculasDesdeCSV(const string& rutaArchivo) {
    vector<Pelicula> peliculas;
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
        return peliculas;
    }

    string linea;

    // Omitimos la primera línea si contiene encabezados
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, titulo, sinopsis, tagsStr;

        // Leer los datos del CSV (ignoramos la primera columna ID)
        getline(ss, id, ',');         // ID (ignoramos)
        getline(ss, titulo, ',');     // Título
        getline(ss, sinopsis, ',');   // Sinopsis
        getline(ss, tagsStr, ',');    // Tags

        // Dividir los tags por el separador ";"
        vector<string> tags;
        stringstream ssTags(tagsStr);
        string tag;
        while (getline(ssTags, tag, ';')) {
            tags.push_back(tag);
        }

        // Crear película y agregarla al vector
        peliculas.emplace_back(titulo, sinopsis, tags);
    }

    archivo.close();
    return peliculas;
}
