// Versión comentada línea a línea: explica por qué se usan las variables y cada paso.
// Jader Suarez

#include <iostream>  // cout, cin, endl: salida/entrada estándar
#include <iomanip>   // setw, left, right, fixed, setprecision: formateo de salida
#include <string>    // std::string para almacenar nombres y líneas
#include <sstream>   // std::stringstream para validar entradas leyendo líneas
using namespace std; // Para evitar escribir std:: en cada uso (conveniencia en ejemplos pequeños)

// Valida entrada de un número no negativo (acepta decimales) leyendo líneas.
double validarDatoPositivo(const string& mensaje) {
    string linea;                    // almacena la línea completa leída desde cin
    while (true) {
        cout << mensaje;             // muestra el prompt al usuario
        if (!getline(cin, linea))    // lee una línea completa; protege contra EOF
            return 0.0;              // si hay EOF, devuelve 0.0 como fallback seguro
        stringstream ss(linea);      // convierte la línea en flujo para parsear
        double valor;                // variable donde intentamos almacenar el número
        char extra;                  // usado para detectar caracteres extra después del número
        // Si no podemos leer un double, o hay caracteres extra, o el valor es negativo -> error
        if (!(ss >> valor) || (ss >> extra) || valor < 0) {
            cout << "Error: ingrese un valor valido (no negativo)." << endl;
            continue;                // pide la entrada de nuevo
        }
        return valor;                // entrada válida -> devolver el valor parseado
    }
}

// Valida entero en rango [min, max] leyendo líneas.
int validarEnteroRango(const string& mensaje, int min, int max) {
    string linea;                    // línea completa leída del usuario
    while (true) {
        cout << mensaje;             // prompt
        if (!getline(cin, linea))    // protección contra EOF
            return min;              // si hay EOF, devolvemos min para evitar comportamiento indefinido
        stringstream ss(linea);      // parseo de la línea
        int valor;                   // entero leído
        char extra;                  // para detectar texto adicional inválido
        // Condiciones de fallo: no leer int, texto extra, o valor fuera de rango
        if (!(ss >> valor) || (ss >> extra) || valor < min || valor > max) {
            cout << "Error: valor invalido (" << min << "-" << max << ")." << endl;
            continue;                // repetir hasta entrada correcta
        }
        return valor;                // valor entero y dentro del rango
    }
}

// Calcula el total ganado: sum(distancia[i] * costo[i])
double calcularTotal(double distancia[], double costo[], int numViajes) {
    double total = 0.0;             // acumulador para el total ganado del conductor
    for (int i = 0; i < numViajes; i++) // iteramos solo hasta numViajes (no todo el arreglo)
        total += distancia[i] * costo[i]; // cada viaje contribuye: km * costo_por_km
    return total;                   // retornamos el total calculado
}

// Calcula el promedio de distancias (double)
double calcularPromedio(double distancia[], int numViajes) {
    double suma = 0.0;              // acumulador de distancias para calcular promedio
    for (int i = 0; i < numViajes; i++)
        suma += distancia[i];       // sumamos cada distancia registrada
    // Si no hay viajes (numViajes == 0) evitamos división por cero devolviendo 0.0
    return (numViajes > 0) ? (suma / numViajes) : 0.0;
}

int main() {
    // Pedir cantidad de conductores (1-10)
    // validamos con validarEnteroRango para asegurar que esté entre 1 y 10
    int cantidadConductores = validarEnteroRango(
        "Ingrese la cantidad de conductores (maximo 10): ", 1, 10);

    // Almacenamiento de datos
    string nombres[10];              // arreglo para almacenar hasta 10 nombres de conductores
    double totalGanado[10] = { 0.0 };     // total ganado por conductor (inicializado a 0.0)
    double promedioDistancia[10] = { 0.0 }; // promedio de distancia por conductor

    // Recorremos cada conductor para solicitar sus datos
    for (int i = 0; i < cantidadConductores; i++) {
        cout << "=== CONDUCTOR #" << i + 1 << " ===" << endl; // encabezado informativo
        cout << "Nombre: ";
        getline(cin, nombres[i]);    // leemos el nombre completo del conductor y lo guardamos en nombres[i]

        // Pedimos cuántos viajes realizó este conductor (1-10)
        int numViajes = validarEnteroRango(
            "Ingrese el numero de viajes realizados (maximo 10): ", 1, 10);

        double distancia[10] = { 0.0 }; // arreglo local para distancias de los viajes del conductor
        double costo[10] = { 0.0 };     // arreglo local para costo por km de cada viaje

        // Recolectamos distancia y costo por km para cada viaje
        for (int j = 0; j < numViajes; j++) {
            cout << endl;
            cout << "Viaje #" << j + 1 << endl;
            // validarDatoPositivo retorna double >= 0; asignamos a distancia[j]
            distancia[j] = validarDatoPositivo("  Distancia (km): ");
            // validarDatoPositivo retorna double >= 0; asignamos a costo[j]
            costo[j] = validarDatoPositivo("  Costo por km ($): ");
        }

        // Calculamos el total ganado y el promedio de distancia para este conductor
        totalGanado[i] = calcularTotal(distancia, costo, numViajes);
        promedioDistancia[i] = calcularPromedio(distancia, numViajes);
        cout << endl; // separación visual entre conductores
    }

    // Encontrar índice del mayor ingreso
    int indiceMayor = 0;             // inicializamos asumiendo que el primero es el mayor
    for (int i = 1; i < cantidadConductores; i++) {
        // comparamos totalGanado[i] con el actual mayor y actualizamos el índice si corresponde
        if (totalGanado[i] > totalGanado[indiceMayor]) indiceMayor = i;
    }

    // Mostrar resultados (encabezados de tabla)
    cout << "================ RESUMEN DE VIAJES ================" << endl;
    cout << "Conductor             Total Ganado ($)          Promedio Distancia (km)" << endl;

    // Imprimir una fila por cada conductor:
    // - usamos setw/left/right/fixed/setprecision para alinear y formatear números con 2 decimales
    for (int i = 0; i < cantidadConductores; i++) {
        cout << left << setw(22) << nombres[i]           // nombre alineado a la izquierda en 22 caracteres
            << right << setw(12) << fixed << setprecision(2) << totalGanado[i] // total con 2 decimales
            << setw(20) << fixed << setprecision(2) << promedioDistancia[i]    // promedio con 2 decimales
            << endl;
    }

    // Mensaje indicando cuál conductor obtuvo mayor ingreso
    cout << "==================================================" << endl;
    cout << "El conductor con mayor ingreso fue: " << nombres[indiceMayor]
        << " con $" << totalGanado[indiceMayor] << endl;

    cout << "==================================================" << endl;
    cout << " === Fin del programa === " << endl;
    return 0; // código de salida 0 (éxito)
}