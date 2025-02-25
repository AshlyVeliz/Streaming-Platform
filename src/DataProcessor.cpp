#include <queue>
#include <condition_variable>
#include "DataProcessor.h"

using namespace std;

// Pool de hilos para paralelizar la carga
class ThreadPool {
public:
    ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (thread &worker : workers) worker.join();
    }

    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queueMutex);
            tasks.push(move(task));
        }
        condition.notify_one();
    }

private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queueMutex;
    condition_variable condition;
    bool stop = false;
};

// Cargar películas desde JSON
vector<Pelicula> DataProcessor::cargarPeliculasDesdeJSON(const string& rutaJSON) {
    vector<Pelicula> peliculas;
    ifstream jsonFile(rutaJSON);

    if (!jsonFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo JSON " << rutaJSON << endl;
        return peliculas;
    }

    json jsonPeliculas;
    jsonFile >> jsonPeliculas;
    jsonFile.close();

    for (const auto& item : jsonPeliculas) {
        peliculas.emplace_back(
                item["titulo"].get<string>(),
                item["sinopsis"].get<string>(),
                item["tags"].get<vector<string>>(),
                item.value("likes", 0),
                item.value("ver_luego", false)
        );
    }

    cout << "✔ Películas cargadas desde JSON: " << peliculas.size() << endl;
    return peliculas;
}

// Procesar línea del CSV en paralelo
void DataProcessor::procesarLinea(const string& linea, vector<Pelicula>& peliculas, mutex& m) {
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

    Pelicula pelicula(titulo, sinopsis, tags, 0, false);

    lock_guard<mutex> lock(m);
    peliculas.push_back(pelicula);
}

// Guardar películas en JSON
void DataProcessor::guardarJSON(const vector<Pelicula>& peliculas, const string& rutaJSON) {
    json jsonPeliculas;
    for (const auto& pelicula : peliculas) {
        jsonPeliculas.push_back({
                                        {"titulo", pelicula.titulo},
                                        {"sinopsis", pelicula.sinopsis},
                                        {"tags", pelicula.tags},
                                        {"likes", pelicula.likes},
                                        {"ver_luego", pelicula.ver_luego}
                                });
    }

    ofstream outFile(rutaJSON);
    if (outFile.is_open()) {
        outFile << jsonPeliculas.dump(4);
        outFile.close();
        cout << "✔ Archivo JSON creado con éxito: " << rutaJSON << endl;
    } else {
        cerr << "Error: No se pudo guardar el archivo JSON." << endl;
    }
}

// Cargar películas desde CSV con paralelización y ordenamiento
vector<Pelicula> DataProcessor::cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON) {
    vector<Pelicula> peliculas;

    // Si JSON ya existe, cargar desde JSON en lugar de CSV
    ifstream jsonFile(rutaJSON);
    if (jsonFile.good()) {
        cout << "✔ Archivo JSON encontrado. Cargando datos desde JSON.\n";
        return cargarPeliculasDesdeJSON(rutaJSON);
    }

    ifstream archivoCSV(rutaCSV);
    if (!archivoCSV.is_open()) {
        cerr << "x Error: No se pudo abrir el archivo CSV " << rutaCSV << endl;
        return peliculas;
    }

    string linea;
    getline(archivoCSV, linea);

    // Crear pool de hilos según los núcleos de la CPU
    ThreadPool pool(thread::hardware_concurrency());
    mutex m;

    while (getline(archivoCSV, linea)) {
        pool.enqueue([=, &peliculas, &m] {
            procesarLinea(linea, peliculas, m);
        });
    }

    archivoCSV.close();

    // Ordenar películas antes de insertarlas en el AVL Tree
    sort(peliculas.begin(), peliculas.end(), [](const Pelicula& a, const Pelicula& b) {
        return a.titulo < b.titulo;
    });

    // Guardar JSON en un hilo separado
    thread jsonThread(guardarJSON, ref(peliculas), rutaJSON);
    jsonThread.join();

    return peliculas;
}
