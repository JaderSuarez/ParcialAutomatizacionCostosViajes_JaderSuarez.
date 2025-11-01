// 2parcial.cpp 
// Jader Suarez

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// Valida entrada de un número no negativo (acepta decimales) leyendo líneas.
double validarDatoPositivo(const string& mensaje) {
    string linea;
    while (true) {
        cout << mensaje;
        if (!getline(cin, linea)) return 0.0; // protección ante EOF
        stringstream ss(linea);
        double valor;
        char extra;
        if (!(ss >> valor) || (ss >> extra) || valor < 0) {
            cout << "Error: ingrese un valor valido (no negativo)." << endl;
            continue;
        }
        return valor;
    }
}

// Valida entero en rango [min, max] leyendo líneas.
int validarEnteroRango(const string& mensaje, int min, int max) {
    string linea;
    while (true) {
        cout << mensaje;
        if (!getline(cin, linea)) return min; // protección ante EOF
        stringstream ss(linea);
        int valor;
        char extra;
        if (!(ss >> valor) || (ss >> extra) || valor < min || valor > max) {
            cout << "Error: valor invalido (" << min << "-" << max << ")." << endl;
            continue;
        }
        return valor;
    }
}

// Calcula el total ganado: sum(distancia[i] * costo[i])
double calcularTotal(double distancia[], double costo[], int numViajes) {
    double total = 0.0;
    for (int i = 0; i < numViajes; i++) total += distancia[i] * costo[i];
    return total;
}

// Calcula el promedio de distancias (double)
double calcularPromedio(double distancia[], int numViajes) {
    double suma = 0.0;
    for (int i = 0; i < numViajes; i++) suma += distancia[i];
    return (numViajes > 0) ? (suma / numViajes) : 0.0;
}

int main() {
    // Pedir cantidad de conductores (1-10)
    int cantidadConductores = validarEnteroRango("Ingrese la cantidad de conductores (maximo 10): ", 1, 10);

    // Almacenamiento de datos
    string nombres[10];
    double totalGanado[10] = { 0.0 };
    double promedioDistancia[10] = { 0.0 };

    for (int i = 0; i < cantidadConductores; i++) {
        cout << "=== CONDUCTOR #" << i + 1 << " ===" << endl;
        cout << "Nombre: ";
        getline(cin, nombres[i]);

        int numViajes = validarEnteroRango("Ingrese el numero de viajes realizados (maximo 10): ", 1, 10);

        double distancia[10] = { 0.0 };
        double costo[10] = { 0.0 };

        for (int j = 0; j < numViajes; j++) {
            cout << endl;
            cout << "Viaje #" << j + 1 << endl;
            distancia[j] = validarDatoPositivo("  Distancia (km): ");
            costo[j] = validarDatoPositivo("  Costo por km ($): ");
        }

        totalGanado[i] = calcularTotal(distancia, costo, numViajes);
        promedioDistancia[i] = calcularPromedio(distancia, numViajes);
        cout << endl;
    }

    // Encontrar índice del mayor ingreso
    int indiceMayor = 0;
    for (int i = 1; i < cantidadConductores; i++) {
        if (totalGanado[i] > totalGanado[indiceMayor]) indiceMayor = i;
    }

    // Mostrar resultados
    cout << "================ RESUMEN DE VIAJES ================" << endl;
    cout << "Conductor             Total Ganado ($)          Promedio Distancia (km)" << endl;

    // Imprimir una fila por cada conductor 
    for (int i = 0; i < cantidadConductores; i++) {
        cout << left << setw(22) << nombres[i]
             << right << setw(12) << fixed << setprecision(2) << totalGanado[i]
             << setw(20) << fixed << setprecision(2) << promedioDistancia[i]
             << endl;
    }

    cout << "==================================================" << endl;

    cout << "El conductor con mayor ingreso fue: " << nombres[indiceMayor]
        << " con $" << totalGanado[indiceMayor] << endl;

    cout << "==================================================" << endl;
    cout << " === Fin del programa === " << endl;
    return 0;
}
