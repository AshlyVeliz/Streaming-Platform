#include "DataProcessor.h"

vector<Pelicula> DataProcessor::cargarPeliculasDesdeJSON(const string& rutaJSON) {
    vector<Pelicula> peliculas;
    ifstream jsonFile(rutaJSON);

    if (!jsonFile.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo JSON " << rutaJSON << endl;
        return peliculas;
    }

    json jsonPeliculas;
    jsonFile >> jsonPeliculas;
    jsonFile.close();

    for (const auto& item : jsonPeliculas["peliculas"]) {
        peliculas.emplace_back(
                item["titulo"].get<string>(),
                item["sinopsis"].get<string>(),
                item["tags"].get<vector<string>>()
        );
    }

    cout << "✔ Películas cargadas desde JSON en vector: " << peliculas.size() << endl;
    return peliculas;
}

vector<Pelicula> DataProcessor::cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON) {
    vector<Pelicula> peliculas;

    // Verificar si el JSON ya existe
    ifstream jsonFile(rutaJSON);
    if (jsonFile.good()) {
        cout << "✔ Archivo JSON ya existe. Cargando datos desde JSON.\n";
        return cargarPeliculasDesdeJSON(rutaJSON);
    }

    ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo " << rutaCSV << endl;
        return peliculas;
    }

    string linea;
    getline(archivo, linea);  // Omitir encabezados si los hay

    json jsonPeliculas;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, titulo, sinopsis, tagsStr;

        getline(ss, id, ',');
        getline(ss, titulo, ',');
        getline(ss, sinopsis, ',');
        getline(ss, tagsStr, ',');

        vector<string> tags;
        stringstream ssTags(tagsStr);
        string tag;
        while (getline(ssTags, tag, ' ')) {
            if (!tag.empty() && tag.front() == '"') tag.erase(0, 1);
            if (!tag.empty() && tag.back() == '"') tag.pop_back();
            tags.push_back(tag);
        }

        peliculas.emplace_back(titulo, sinopsis, tags);

        // Guardar en JSON con el ID real
        jsonPeliculas["peliculas"].push_back({
                                                     {"id", id},
                                                     {"titulo", titulo},
                                                     {"sinopsis", sinopsis},
                                                     {"tags", tags},
                                                     {"likes", 0},
                                                     {"ver_luego", json::array()}
                                             });
    }

    archivo.close();

    // Guardar el JSON corregido
    ofstream outFile(rutaJSON);
    outFile << jsonPeliculas.dump(4);
    outFile.close();

    cout << "✅ Archivo JSON creado exitosamente con IDs reales: " << rutaJSON << endl;
    return peliculas;
}

