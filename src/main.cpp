#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"
#include "SearchTree.h"
#include "Ver_masTarde.h"
#include "MeGusta.h"

using namespace std;

int main() {
    string rutaCSV = "C:\\Streaming-Platform\\data\\movies.csv";
    string rutaJSON = "C:\\Streaming-Platform\\data\\movies.json";

    // Cargar peliculas en un vector desde JSON o CSV
    vector<Pelicula> peliculas = DataProcessor::cargarPeliculasDesdeCSV(rutaCSV, rutaJSON);

    if (peliculas.empty()) {
        cout << "No se cargaron peliculas. Revisa el archivo CSV o JSON." << endl;
        return 1;
    }

    TagTree tagTree;
    SearchTree searchTree;
    Ver_masTarde verMasTarde;
    MeGusta meGusta;

    // Insertar las peliculas en los arboles
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
        searchTree.insertar(pelicula);
    }

    // Búsqueda por titulo con paginacion y opciones
    while (true) {
        string consulta;
        cout << "\n Ingrese una palabra o frase para buscar (o 'salir'): ";
        getline(cin, consulta);

        if (consulta == "salir") break;

        int pagina = 0;
        int peliculasPorPagina = 5;

        while (true) {
            vector<Pelicula> resultados = searchTree.buscar(consulta, pagina, peliculasPorPagina);

            if (resultados.empty()) {
                cout << "No se encontraron coincidencias.\n";
                break;
            }

            cout << "\n Pagina " << (pagina + 1) << ":\n";
            for (size_t i = 0; i < resultados.size(); ++i) {
                cout << i + 1 << ". 🎬 " << resultados[i].titulo << " | 📖 " << resultados[i].sinopsis << endl;
            }

            cout << "\nOpciones:\n"
                 << "'mas' -> Ver mas resultados\n"
                 << "'agregar' -> Agregar a 'Ver mas tarde'\n"
                 << "'like' -> Agregar a 'Me gusta'\n"
                 << "'ver' -> Ver listas\n"
                 << "'eliminar' -> Quitar la ultima añadida\n"
                 << "'salir' -> Terminar\n"
                 << "selecciona una opcion: ";

            string opcion;
            cin >> opcion;
            cin.ignore();  // Limpiar buffer

            if (opcion == "mas") {
                pagina++;
            } else if (opcion == "agregar") {
                cout << "Ingrese el numero de la pelicula para agregar a 'Ver mas tarde': ";
                int num; cin >> num;
                if (num >= 1 && num <= (int)resultados.size()) {
                    verMasTarde.agregar(resultados[num - 1]);
                } else {
                    cout << "Numero invalido.\n";
                }
            } else if (opcion == "like") {
                cout << "Ingrese el numero de la pelicula para agregar a 'Me gusta': ";
                int num; cin >> num;
                if (num >= 1 && num <= (int)resultados.size()) {
                    meGusta.agregar(resultados[num - 1]);
                } else {
                    cout << "Numero invalido.\n";
                }
            } else if (opcion == "ver") {
                cout << "\nLista 'Ver mas tarde':\n";
                verMasTarde.mostrar();
                cout << "\nLista 'Me gusta':\n";
                meGusta.mostrar();
            } else if (opcion == "eliminar") {
                cout << "¿De que lista deseas eliminar? ('ver' para 'Ver mas tarde', 'like' para 'Me gusta'): ";
                string lista;
                cin >> lista;
                if (lista == "ver") {
                    verMasTarde.eliminar();
                } else if (lista == "like") {
                    meGusta.eliminar();
                } else {
                    cout << "Opcion invalida.\n";
                }
            } else if (opcion == "salir") {
                break;
            } else {
                cout << "Opcion invalida.\n";
            }
        }
    }

    return 0;
}
