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
        getline(ss, id, ',');         // ID (ignorar)
        getline(ss, titulo, ',');     // Título
        getline(ss, sinopsis, ',');   // Sinopsis
        getline(ss, tagsStr, ',');    // Tags (pero aún están juntos)

        // 🔹 Separar los tags por espacio y limpiar comillas dobles
        vector<string> tags;
        stringstream ssTags(tagsStr);
        string tag;
        while (ssTags >> tag) {  // Separa por espacio
            // Eliminar comillas dobles si las tiene
            if (!tag.empty() && tag.front() == '"') tag.erase(0, 1);
            if (!tag.empty() && tag.back() == '"') tag.pop_back();

            tags.push_back(tag);
        }

        // Crear película y agregarla al vector
        peliculas.emplace_back(titulo, sinopsis, tags);
    }

    archivo.close();
    return peliculas;
}
