#include <iostream>
#include <string>

using namespace std;

// Clase Violín
class Violin {
private:
    // Atributos privados
    string marca;
    int año_fabricacion;
    int calidad_sonido;  // Escala de 1 a 10

public:
    // Constructor que inicializa los atributos
    Violin(string m, int año, int calidad) {
        marca = m;
        año_fabricacion = año;
        calidad_sonido = calidad;
    }

    // Método 1: Tocar el violín
    void tocar() {
        cout << "\n--- Tocando Violín ---" << endl;
        cout << "Marca: " << marca << endl;
        cout << "Año de fabricación: " << año_fabricacion << endl;
        cout << "Produciendo sonido hermoso con calidad: " << calidad_sonido << "/10" << endl;
        cout << "♪ Mi, mi, sol, sol, la, la, sol... ♪" << endl;
    }

    // Método 2: Afinar el violín
    void afinar() {
        cout << "\n--- Afinando Violín ---" << endl;
        cout << "Afinando las cuerdas del violín marca " << marca << "..." << endl;
        if (calidad_sonido < 10) {
            calidad_sonido++;
            cout << "¡Violín afinado exitosamente!" << endl;
            cout << "Nueva calidad de sonido: " << calidad_sonido << "/10" << endl;
        } else {
            cout << "El violín ya tiene la máxima calidad de sonido." << endl;
        }
    }

    // Método 3: Realizar mantenimiento
    void mantenimiento() {
        cout << "\n--- Realizando Mantenimiento ---" << endl;
        cout << "Limpiando y revisando violín marca " << marca << endl;
        cout << "Año de fabricación: " << año_fabricacion << endl;
        cout << "Aplicando barniz protector..." << endl;
        cout << "¡Mantenimiento completado!" << endl;
        cout << "El violín está listo para ser tocado." << endl;
    }

    // Método para mostrar información del violín
    void mostrarInfo() {
        cout << "\n=== INFORMACIÓN DEL VIOLÍN ===" << endl;
        cout << "Marca: " << marca << endl;
        cout << "Año de fabricación: " << año_fabricacion << endl;
        cout << "Calidad de sonido: " << calidad_sonido << "/10" << endl;
    }
};

// Función principal
int main() {
    cout << "===== SISTEMA DE GESTIÓN DE VIOLINES =====" << endl;

    // Creando dos instancias de la clase Violín
    Violin violin1("Stradivarius", 1920, 9);
    Violin violin2("Guarneri", 1995, 8);

    cout << "\n----------- VIOLÍN 1 -----------" << endl;
    violin1.mostrarInfo();
    violin1.tocar();
    violin1.afinar();
    violin1.mantenimiento();

    cout << "\n\n----------- VIOLÍN 2 -----------" << endl;
    violin2.mostrarInfo();
    violin2.tocar();
    violin2.afinar();
    violin2.mantenimiento();

    cout << "\n\n===== INFORMACIÓN FINAL =====" << endl;
    cout << "\nViolín 1 después de mantenimiento:" << endl;
    violin1.mostrarInfo();

    cout << "\nViolín 2 después de mantenimiento:" << endl;
    violin2.mostrarInfo();

    return 0;
}
