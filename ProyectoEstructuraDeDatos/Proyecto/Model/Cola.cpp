#include "Cola.hpp"

ModeloCola::ModeloCola(int capacidad) : frente(nullptr), final(nullptr), tamanio(0), capacidadMaxima(capacidad) {}

ModeloCola::~ModeloCola() {
    while (!empty()) {
        NodoCola* temp = dequeue();
        delete temp;
    }
}

bool ModeloCola::enqueue(int valor, sf::Color color, sf::Vector2f posicion) {
    if (full()) {
        std::cout << "Error: Cola llena" << std::endl;
        return false;
    }
    NodoCola* nuevoNodo = new NodoCola(valor, color, posicion);
    if (empty()) {
        frente = final = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
        final = nuevoNodo;
    }
    tamanio++;
    std::cout << "ENQUEUE: Elemento " << valor << " añadido" << std::endl;
    return true;
}

NodoCola* ModeloCola::dequeue() {
    if (empty()) {
        std::cout << "Error: Cola vacía" << std::endl;
        return nullptr;
    }
    NodoCola* nodoEliminado = frente;
    frente = frente->siguiente;
    if (!frente) final = nullptr;
    tamanio--;
    std::cout << "DEQUEUE: Elemento " << nodoEliminado->dato << " eliminado" << std::endl;
    return nodoEliminado;
}

NodoCola* ModeloCola::front() const {
    return frente;
}

bool ModeloCola::empty() const {
    return frente == nullptr;
}

bool ModeloCola::full() const {
    return tamanio >= capacidadMaxima;
}

int ModeloCola::size() const {
    return tamanio;
}

NodoCola* ModeloCola::obtenerFrente() const {
    return frente;
}

void ModeloCola::mostrarRecursivo(NodoCola* nodo, int nivel) const {
    if (nodo == nullptr) return;
    std::cout << "Posición " << nivel << ": " << nodo->dato << std::endl;
    mostrarRecursivo(nodo->siguiente, nivel + 1);
}

