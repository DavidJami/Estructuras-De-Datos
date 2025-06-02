#include "PilaControlador.hpp"

PilaControlador::PilaControlador(sf::RenderWindow* window) : ventana(window), semilla(1), salir(false) {
    pila = new ModeloPila(8);
    vista = new PilaVista(window);

    if (!vista->cargarFuente()) {
        std::cout << "Error al cargar fuentes" << std::endl;
    }
}

PilaControlador::~PilaControlador() {
    delete pila;
    delete vista;
}

void PilaControlador::ejecutar() {
    salir = false;
    std::cout << "Iniciando gestion de pila..." << std::endl;

    while (ventana->isOpen() && !salir) {
        float deltaTime = reloj.restart().asSeconds();
        vista->actualizarAnimaciones(deltaTime);

        while (const std::optional evento = ventana->pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana->close();
            }
            manejarEventosPila(*evento);
        }
        vista->mostrarGestionPila(*pila);
    }

    std::cout << "Saliendo de gestion de pila..." << std::endl;
}


void PilaControlador::manejarEventosPila(const sf::Event& evento) {
    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>()) {
        if (vista->hayAnimacionEnCurso()) {
            std::cout << "Espera a que termine la animacion actual..." << std::endl;
            return;
        }

        switch (keyPressed->code) {
            case sf::Keyboard::Key::Enter:
                agregarElementoConAnimacion();
                break;
            case sf::Keyboard::Key::Space:
                eliminarElementoConAnimacion();
                break;
            case sf::Keyboard::Key::T:
                mostrarTope();
                break;
            case sf::Keyboard::Key::E:
                verificarVacia();
                break;
            case sf::Keyboard::Key::M:
                mostrarPilaCompleta();
                break;
            case sf::Keyboard::Key::Escape:
                salir = true;
                std::cout << "Regresando al menu principal" << std::endl;
                break;
            default:
                break;
        }
    }
}

void PilaControlador::agregarElementoConAnimacion() {
    if (!pila->full()) {
        int valor = generarNumeroAleatorio();
        sf::Color color = generarColorAleatorio();
        sf::Vector2f posicion(450, 600);
        pila->push(valor, color, posicion);
        vista->iniciarAnimacionPush(valor, color, *pila);
        std::cout << "PUSH animado: Pelota " << valor << " cayendo en el tubo..." << std::endl;
    } else {
        std::cout << "No se puede agregar: Tubo lleno" << std::endl;
    }
}

void PilaControlador::eliminarElementoConAnimacion() {
    if (!pila->empty()) {
        NodoPila* elementoAEliminar = pila->top();
        int valor = elementoAEliminar->dato;
        sf::Color color = elementoAEliminar->color;
        vista->iniciarAnimacionPop(valor, color, *pila);
        NodoPila* eliminado = pila->pop();
        delete eliminado;
        std::cout << "POP animado: Pelota " << valor << " saliendo del tubo..." << std::endl;
    } else {
        std::cout << "No se puede eliminar: Tubo vacio" << std::endl;
    }
}

void PilaControlador::agregarElemento() {
    if (!pila->full()) {
        int valor = generarNumeroAleatorio();
        sf::Color color = generarColorAleatorio();
        sf::Vector2f posicion(450, 600);
        pila->push(valor, color, posicion);
    } else {
        std::cout << "No se puede agregar: Pila llena" << std::endl;
    }
}

void PilaControlador::eliminarElemento() {
    NodoPila* eliminado = pila->pop();
    if (eliminado) {
        delete eliminado;
    }
}

void PilaControlador::mostrarTope() {
    if (!pila->empty()) {
        vista->activarVisualizacionTop();
        std::cout << "=== OPERACION TOP ===" << std::endl;
        std::cout << "Consultando elemento del tope SIN quitarlo" << std::endl;
        std::cout << "Valor en el TOP: " << pila->top()->dato << std::endl;
        std::cout << "El elemento permanece en la pila" << std::endl;
        std::cout << "Elementos en pila: " << pila->size() << " (sin cambios)" << std::endl;
        std::cout << "===================" << std::endl;
    } else {
        std::cout << "=== OPERACION TOP ===" << std::endl;
        std::cout << "ERROR: La pila esta vacia" << std::endl;
        std::cout << "No hay elemento que consultar" << std::endl;
        std::cout << "===================" << std::endl;
    }
}

void PilaControlador::verificarVacia() {
    if (pila->empty()) {
        std::cout << "EMPTY: La pila esta VACIA (true)" << std::endl;
    } else {
        std::cout << "EMPTY: La pila NO esta vacia (false)" << std::endl;
    }
}

void PilaControlador::mostrarPilaCompleta() {
    std::cout << std::endl << "=== CONTENIDO COMPLETO DE LA PILA ===" << std::endl;
    if (pila->empty()) {
        std::cout << "La pila esta vacia" << std::endl;
    } else {
        std::cout << "Mostrando recursivamente:" << std::endl;
        pila->mostrarRecursivo(pila->obtenerTope());
    }
    std::cout << "====================================" << std::endl;
}

int PilaControlador::generarNumeroAleatorio() {
    semilla = (semilla * 1103515245 + 12345) & 0x7fffffff;
    return (semilla % 99) + 1;
}

sf::Color PilaControlador::generarColorAleatorio() {
    int r = 100 + (generarNumeroAleatorio() * 17) % 155;
    int g = 100 + (generarNumeroAleatorio() * 23) % 155;
    int b = 100 + (generarNumeroAleatorio() * 31) % 155;
    return sf::Color(r, g, b);
}
