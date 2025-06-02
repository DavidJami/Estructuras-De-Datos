#ifndef LISTADOBLE_HPP
#define LISTADOBLE_HPP

#include <iostream>
using namespace std;

template <typename T>
class ListaDoble {
private:
    struct Nodo {
        T dato;
        Nodo* anterior;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), anterior(nullptr), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    Nodo* cola;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDoble() {
        Nodo* actual = cabeza;
        while (actual) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& dato) {
        Nodo* nuevo = new Nodo(dato);
        if (!cabeza) {
            cabeza = cola = nuevo;
            return;
        }
        Nodo* actual = cabeza;
        while (actual && actual->dato < dato)
            actual = actual->siguiente;

        if (actual == cabeza) {
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        } else if (!actual) {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        } else {
            Nodo* anterior = actual->anterior;
            anterior->siguiente = nuevo;
            nuevo->anterior = anterior;
            nuevo->siguiente = actual;
            actual->anterior = nuevo;
        }
    }

    bool eliminar(const T& dato) {
        Nodo* actual = cabeza;
        while (actual && actual->dato != dato)
            actual = actual->siguiente;

        if (!actual) return false;

        if (actual == cabeza && actual == cola)
            cabeza = cola = nullptr;
        else if (actual == cabeza) {
            cabeza = cabeza->siguiente;
            cabeza->anterior = nullptr;
        } else if (actual == cola) {
            cola = cola->anterior;
            cola->siguiente = nullptr;
        } else {
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
        }

        delete actual;
        return true;
    }

    Nodo* getCabeza() const { return cabeza; }

    void mostrarRecursivo() const {
        mostrarDesde(cabeza);
        cout << endl;
    }


    void mostrarDesde(Nodo* nodo) const {
        if (!nodo) return;
        cout << nodo->dato << " ";
        mostrarDesde(nodo->siguiente);
    }
};

#endif

