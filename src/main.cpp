#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"

int main() {
    string rutaCSV = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.csv";
    string rutaJSON = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.json";

    // Cargar películas en un vector desde JSON o CSV
    vector<Pelicula> peliculas = DataProcessor::cargarPeliculasDesdeCSV(rutaCSV, rutaJSON);

    if (peliculas.empty()) {
        cout << "❌ No se cargaron películas. Revisa el archivo CSV o JSON." << endl;
        return 1;
    }

    TagTree tagTree;

    // Insertar las películas en el árbol de tags
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
    }

    // Mostrar los tags almacenados (opcional)
    cout << "\n📌 Tags en el árbol de búsqueda: " << endl;
    tagTree.imprimirTags();

    // 🔍 Búsqueda por tag
    while (true) {
        string tagBuscado;
        cout << "\n🔍 Ingrese un tag para buscar películas (o 'salir' para terminar): ";
        cin >> tagBuscado;

        if (tagBuscado == "salir") break;

        vector<Pelicula> resultados = tagTree.buscarPeliculasPorTag(tagBuscado);

        if (resultados.empty()) {
            cout << "❌ No se encontraron películas con el tag #" << tagBuscado << endl;
        } else {
            cout << "\n🎥 Películas con el tag #" << tagBuscado << ":" << endl;
            for (size_t i = 0; i < min(resultados.size(), size_t(5)); ++i) {
                cout << "\n🎬 Título: " << resultados[i].titulo << endl;
                cout << "📖 Sinopsis: " << resultados[i].sinopsis << endl;
            }
        }
    }

    return 0;
}
