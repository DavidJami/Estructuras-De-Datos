#ifndef PILADINAMICAPRO_HPP
#define PILADINAMICAPRO_HPP

#include <iostream>

template <typename T>
class PilaDinamica {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* cima;

public:
    PilaDinamica() : cima(nullptr) {}

    ~PilaDinamica() {
        while (!estaVacia()) pop();
    }

    bool estaVacia() const {
        return cima == nullptr;
    }

    void push(const T& valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cima;
        cima = nuevo;
    }

    void pop() {
        if (estaVacia()) return;
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
    }

    T top() const {
        if (estaVacia()) throw std::runtime_error("La pila está vacía.");
        return cima->dato;
    }

    int contarElementos() const {
        int contador = 0;
        Nodo* actual = cima;
        while (actual) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }
};

#endif
