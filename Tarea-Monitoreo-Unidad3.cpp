#include <iostream>
#include <vector>   // Para usar vectores en lugar de arreglos estáticos
#include <limits>   // Para limpiar el buffer de entrada
#include <cmath>    // Para usar la función abs() (valor absoluto)

using namespace std;

// PROTOTIPOS DE FUNCIONES
void ingresarDatos(vector<int> &prod, vector<float> &horas, vector<float> &energia, vector<float> &temp);
void analizarProduccion(vector<int> prod);
void analizarHoras(vector<float> horas);
void analizarEnergia(vector<float> energia);
void analizarTemperatura(vector<float> temp);

int main() {
    // Definimos la cantidad de días
    int numDias = 7;

    // 1. Declaración de los 4 arreglos usando vectores unidimensionales
    vector<int> produccion(numDias);
    vector<float> horasOperacion(numDias);
    vector<float> consumoEnergia(numDias);
    vector<float> temperaturaMaquinas(numDias);

    int opcion = 0;
    bool tieneDatos = false;

    // Menú interactivo con ciclo while
    while (opcion != 6) {
      
        cout << "   SISTEMA DE MONITOREO INDUSTRIAL" << endl;
        
        cout << "1. Registrar datos de la semana" << endl;
        cout << "2. Reporte de Produccion" << endl;
        cout << "3. Reporte de Horas" << endl;
        cout << "4. Reporte de Energia" << endl;
        cout << "5. Reporte de Temperatura (Personalizado)" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validación de datos existentes
        if (opcion >= 2 && opcion <= 5 && !tieneDatos) {
            cout << "\n[!] Alerta: Debe ingresar datos primero (Opcion 1)." << endl;
        } 
        else if (opcion == 1) {
            ingresarDatos(produccion, horasOperacion, consumoEnergia, temperaturaMaquinas);
            tieneDatos = true;
        } 
        else if (opcion == 2) {
            analizarProduccion(produccion);
        } 
        else if (opcion == 3) {
            analizarHoras(horasOperacion);
        } 
        else if (opcion == 4) {
            analizarEnergia(consumoEnergia);
        } 
        else if (opcion == 5) {
            analizarTemperatura(temperaturaMaquinas);
        } 
        else if (opcion != 6) {
            cout << "Opcion no valida." << endl;
        }
    }

    return 0;
}

//IMPLEMENTACIÓN DE FUNCIONES

void ingresarDatos(vector<int> &prod, vector<float> &horas, vector<float> &energia, vector<float> &temp) {
    int i = 0;
    while (i < prod.size()) {
        cout << "\n--- DATOS DEL DIA " << i + 1 << " ---" << endl;

        // Validación de Producción
        cout << "Unidades producidas: ";
        cin >> prod[i];
        while (prod[i] < 0) {
            cout << "Invalido. Ingrese un valor positivo: ";
            cin >> prod[i];
        }

        // Validación de Horas
        cout << "Horas operadas (Max 24): ";
        cin >> horas[i];
        while (horas[i] < 0 || horas[i] > 24) {
            cout << "Error. Rango permitido 0-24: ";
            cin >> horas[i];
        }

        // Validación de Energía
        cout << "Consumo energia (kWh): ";
        cin >> energia[i];
        while (energia[i] < 0) {
            cout << "Error. El consumo no puede ser negativo: ";
            cin >> energia[i];
        }

        // Validación de Temperatura
        cout << "Temperatura maquina (C): ";
        cin >> temp[i];
        while (temp[i] < 0 || temp[i] > 150) {
            cout << "Error. Ingrese temperatura valida (0-150): ";
            cin >> temp[i];
        }
        
        i++; // Avanzamos al siguiente día
    }
    cout << "\n[OK] Datos cargados con exito." << endl;
}

void analizarProduccion(vector<int> prod) {
    int total = 0;
    int mayor = prod[0], menor = prod[0];
    int dMayor = 1, dMenor = 1;

    int i = 0;
    while (i < prod.size()) {
        total += prod[i];
        if (prod[i] > mayor) { mayor = prod[i]; dMayor = i + 1; }
        if (prod[i] < menor) { menor = prod[i]; dMenor = i + 1; }
        i++;
    }

    cout << "\n>> REPORTE PRODUCCION" << endl;
    cout << "- Total producido: " << total << endl;
    cout << "- Promedio diario: " << (float)total / prod.size() << endl;
    cout << "- Mayor produccion: Dia " << dMayor << " (" << mayor << ")" << endl;
    cout << "- Menor produccion: Dia " << dMenor << " (" << menor << ")" << endl;
}

void analizarHoras(vector<float> horas) {
    float suma = 0;
    float menor = horas[0];
    int dMenor = 1;
    float limiteX = 12.0; // Valor propuesto para sobrecarga
    int sobrecarga = 0;

    int i = 0;
    while (i < horas.size()) {
        suma += horas[i];
        if (horas[i] < menor) { menor = horas[i]; dMenor = i + 1; }
        if (horas[i] > limiteX) { sobrecarga++; }
        i++;
    }

    cout << "\n>> REPORTE HORAS" << endl;
    cout << "- Promedio de horas: " << suma / horas.size() << " h" << endl;
    cout << "- Dia con menos trabajo: Dia " << dMenor << endl;
    cout << "- Dias con sobrecarga (>12h): " << sobrecarga << endl;
}

void analizarEnergia(vector<float> energia) {
    float total = 0;
    int i = 0;
    while (i < energia.size()) {
        total += energia[i];
        i++;
    }
    float promedio = total / energia.size();

    // Aqui busco el valor más cercano al promedio
    int diaCercano = 0;
    float difMinima = abs(energia[0] - promedio);

    i = 1;
    while (i < energia.size()) {
        if (abs(energia[i] - promedio) < difMinima) {
            difMinima = abs(energia[i] - promedio);
            diaCercano = i;
        }
        i++;
    }

    cout << "\n>> REPORTE ENERGIA" << endl;
    cout << "- Consumo Total: " << total << " kWh" << endl;
    cout << "- Consumo Promedio: " << promedio << " kWh" << endl;
    cout << "- Dia mas cercano al promedio: Dia " << diaCercano + 1 << " (" << energia[diaCercano] << " kWh)" << endl;
}

void analizarTemperatura(vector<float> temp) {
    float limite = 85.0; // Umbral de sobrecalentamiento
    int i = 0;
    bool problema = false;

    cout << "\n>> REPORTE PERSONALIZADO: TEMPERATURA" << endl;
    while (i < temp.size()) {
        if (temp[i] > limite) {
            cout << "[!] Alerta: Dia " << i+1 << " sobrepaso los " << limite << " grados." << endl;
            problema = true;
        }
        i++;
    }
    if (!problema) cout << "Estado de maquinas: NORMAL." << endl;
}