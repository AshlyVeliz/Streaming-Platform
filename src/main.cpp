#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"
#include "SearchTree.h"

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
    SearchTree searchTree;

    // Insertar las películas en los árboles
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
        searchTree.insertar(pelicula);
    }

    // 🔍 Búsqueda por título con paginación
    while (true) {
        string consulta;
        cout << "\n🔍 Ingrese una palabra o frase para buscar (o 'salir'): ";
        getline(cin, consulta);

        if (consulta == "salir") break;

        int pagina = 0;
        int peliculasPorPagina = 5;

        while (true) {
            vector<Pelicula> resultados = searchTree.buscar(consulta, pagina, peliculasPorPagina);

            if (resultados.empty()) {
                cout << "❌ No se encontraron coincidencias.\n";
                break;
            }

            cout << "\n🎥 Página " << (pagina + 1) << ":\n";
            for (const auto& pelicula : resultados) {
                cout << "🎬 " << pelicula.titulo << " | 📖 " << pelicula.sinopsis << endl;
            }

            cout << "\n📌 Escriba 'más' para ver más o 'salir' para terminar: ";
            string opcion;
            cin >> opcion;
            if (opcion == "mas") {
                pagina++;
            } else {
                break;
            }
        }
    }

    return 0;
}
