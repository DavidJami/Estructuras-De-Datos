#include "Pila.hpp"

using namespace std;
ModeloPila::ModeloPila(int capacidad) : tope(nullptr), tamanio(0), capacidadMaxima(capacidad) {
}

ModeloPila::~ModeloPila() {
    while (!empty()) {
        NodoPila* temp = pop();
        delete temp;
    }
}

bool ModeloPila::push(int valor, sf::Color color, sf::Vector2f posicion) {
    if (full()) {
        cout << "Error: Pila llena" << endl;
        return false;
    }

    NodoPila* nuevoNodo = new NodoPila(valor, color, posicion);
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
    tamanio++;

    cout << "PUSH: Elemento " << valor << " añadido" << endl;
    return true;
}

NodoPila* ModeloPila::pop() {
    if (empty()) {
        cout << "Error: Pila vacía" << endl;
        return nullptr;
    }

    NodoPila* nodoEliminado = tope;
    tope = tope->siguiente;
    tamanio--;

    cout << "POP: Elemento " << nodoEliminado->dato << " eliminado" << endl;
    return nodoEliminado;
}

NodoPila* ModeloPila::top() const {
    return tope;
}

bool ModeloPila::empty() const {
    return tope == nullptr;
}

bool ModeloPila::full() const {
    return tamanio >= capacidadMaxima;
}

int ModeloPila::size() const {
    return tamanio;
}

NodoPila* ModeloPila::obtenerTope() const {
    return tope;
}

// Sobrecarga de operadores
ModeloPila& ModeloPila::operator+=(int valor) {
    // Generar color aleatorio simple
    int r = 100 + (valor * 17) % 155;
    int g = 100 + (valor * 23) % 155;
    int b = 100 + (valor * 31) % 155;
    sf::Color colorAleatorio(r, g, b);
    sf::Vector2f posicionDefault(450, 600);

    push(valor, colorAleatorio, posicionDefault);
    return *this;
}

ModeloPila& ModeloPila::operator--() {
    NodoPila* eliminado = pop();
    if (eliminado) {
        delete eliminado;
    }
    return *this;
}

// Funcion recursiva para mostrar elementos
void ModeloPila::mostrarRecursivo(NodoPila* nodo, int nivel) const {
    if (nodo == nullptr) {
        return;
    }

    cout << "Nivel " << nivel << ": " << nodo->dato << endl;
    mostrarRecursivo(nodo->siguiente, nivel + 1);
}
