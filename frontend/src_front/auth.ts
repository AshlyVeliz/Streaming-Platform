import { loadUserMovies } from "./userService";

// Verificar si hay sesión activa
function checkSession() {
    const user = localStorage.getItem("user");
    if (user) {
        document.getElementById("auth-container")!.style.display = "none";
        document.getElementById("app-container")!.style.display = "block";
        loadUserMovies();
    }
}

// Iniciar sesión
function login() {
    const username = (document.getElementById("username") as HTMLInputElement).value.trim();
    if (!username) {
        alert("Por favor, ingresa un usuario válido.");
        return;
    }

    localStorage.setItem("user", username);
    checkSession();
}

// Registrar usuario (Simulado)
function register() {
    alert("Registro exitoso. Ahora inicia sesión.");
}

// Cerrar sesión
function logout() {
    localStorage.removeItem("user");
    location.reload();
}

// Verificar sesión al cargar la página
checkSession();

// Hacer accesibles las funciones en el HTML
(window as any).login = login;
(window as any).register = register;
(window as any).logout = logout;
