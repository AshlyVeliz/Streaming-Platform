import { Stack } from "./stack";

// Pila para "Ver más tarde"
const watchLaterStack = new Stack<string>();

// Obtener usuario actual
function getCurrentUser(): string | null {
    return localStorage.getItem("user");
}

// Obtener películas que le gustan al usuario
export function getLikedMovies(): { title: string, tags: string[] }[] {
    return [
        { title: "Interstellar", tags: ["Sci-Fi", "Drama"] },
        { title: "The Dark Knight", tags: ["Action", "Crime"] },
        { title: "Inception", tags: ["Sci-Fi", "Thriller"] },
        { title: "The Godfather", tags: ["Crime", "Drama"] },
        { title: "Pulp Fiction", tags: ["Crime", "Thriller"] }
    ];
}

// Cargar las películas del usuario
export function loadUserMovies() {
    const user = getCurrentUser();
    if (!user) return;

    const likedMoviesContainer = document.getElementById("liked-movies")!;
    likedMoviesContainer.innerHTML = "";

    getLikedMovies().slice(0, 5).forEach(movie => {
        const movieElement = document.createElement("div");
        movieElement.classList.add("movie-card");
        movieElement.innerHTML = `
            <div class="movie-title">${movie.title}</div>
            <div class="movie-tags">Tags: ${movie.tags.join(", ")}</div>
            <button class="movie-button" onclick="addToWatchLater('${movie.title}')">Ver más tarde</button>
        `;
        likedMoviesContainer.appendChild(movieElement);
    });

    loadWatchLaterMovies();
}

// Agregar película a "Ver más tarde"
export function addToWatchLater(movieTitle: string) {
    watchLaterStack.push(movieTitle);
    loadWatchLaterMovies();
}

// Cargar lista de "Ver más tarde"
export function loadWatchLaterMovies() {
    const watchLaterContainer = document.getElementById("watch-later")!;
    watchLaterContainer.innerHTML = "";

    watchLaterStack.getAll().forEach(movieTitle => {
        const movieElement = document.createElement("div");
        movieElement.classList.add("movie-card");
        movieElement.innerHTML = `
            <div class="movie-title">${movieTitle}</div>
            <button class="movie-button" onclick="removeFromWatchLater()">Eliminar</button>
        `;
        watchLaterContainer.appendChild(movieElement);
    });
}

// Eliminar última película agregada (LIFO)
export function removeFromWatchLater() {
    watchLaterStack.pop();
    loadWatchLaterMovies();
}

// Hacer accesibles las funciones en el HTML
(window as any).addToWatchLater = addToWatchLater;
(window as any).removeFromWatchLater = removeFromWatchLater;
