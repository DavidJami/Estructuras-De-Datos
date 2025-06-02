#include "ColaControlador.hpp"

ColaControlador::ColaControlador(sf::RenderWindow* window) : ventana(window), semilla(1), salir(false) {
    cola = new ModeloCola(8);
    vista = new ColaVista(window);
    if (!vista->cargarFuente()) {
        std::cout << "Error al cargar fuentes" << std::endl;
    }
}

ColaControlador::~ColaControlador() {
    delete cola;
    delete vista;
}

void ColaControlador::ejecutar() {
    salir = false;
    std::cout << "Iniciando gestion de cola..." << std::endl;

    while (ventana->isOpen() && !salir) {
        float deltaTime = reloj.restart().asSeconds();
        vista->actualizarAnimaciones(deltaTime);

        while (const std::optional evento = ventana->pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana->close();
            }
            manejarEventosCola(*evento);
        }
        vista->mostrarGestionCola(*cola);
    }

    std::cout << "Saliendo de gestion de cola..." << std::endl;
}

void ColaControlador::manejarEventosCola(const sf::Event& evento) {
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
            case sf::Keyboard::Key::F:
                mostrarFrente();
                break;
            case sf::Keyboard::Key::E:
                verificarVacia();
                break;
            case sf::Keyboard::Key::M:
                mostrarColaCompleta();
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

void ColaControlador::agregarElementoConAnimacion() {
    if (!cola->full()) {
        int valor = generarNumeroAleatorio();
        sf::Color color = generarColorAleatorio();
        sf::Vector2f posicion(450, 600);
        cola->enqueue(valor, color, posicion);
        vista->iniciarAnimacionEnqueue(valor, color, *cola);
        std::cout << "ENQUEUE animado: Elemento " << valor << " ingresando a la cola..." << std::endl;
    } else {
        std::cout << "No se puede agregar: Cola llena" << std::endl;
    }
}

void ColaControlador::eliminarElementoConAnimacion() {
    if (!cola->empty()) {
        NodoCola* elementoAEliminar = cola->front();
        int valor = elementoAEliminar->dato;
        sf::Color color = elementoAEliminar->color;
        vista->iniciarAnimacionDequeue(valor, color, *cola);
        NodoCola* eliminado = cola->dequeue();
        delete eliminado;
        std::cout << "DEQUEUE animado: Elemento " << valor << " saliendo de la cola..." << std::endl;
    } else {
        std::cout << "No se puede eliminar: Cola vacia" << std::endl;
    }
}

void ColaControlador::mostrarFrente() {
    if (!cola->empty()) {
        vista->activarVisualizacionFront();
        std::cout << "=== OPERACION FRONT ===" << std::endl;
        std::cout << "Consultando elemento del frente SIN quitarlo" << std::endl;
        std::cout << "Valor en el FRENTE: " << cola->front()->dato << std::endl;
        std::cout << "El elemento permanece en la cola" << std::endl;
        std::cout << "Elementos en cola: " << cola->size() << " (sin cambios)" << std::endl;
        std::cout << "===================" << std::endl;
    } else {
        std::cout << "=== OPERACION FRONT ===" << std::endl;
        std::cout << "ERROR: La cola esta vacia" << std::endl;
        std::cout << "No hay elemento que consultar" << std::endl;
        std::cout << "===================" << std::endl;
    }
}

void ColaControlador::verificarVacia() {
    if (cola->empty()) {
        std::cout << "EMPTY: La cola esta VACIA (true)" << std::endl;
    } else {
        std::cout << "EMPTY: La cola NO esta vacia (false)" << std::endl;
    }
}

void ColaControlador::mostrarColaCompleta() {
    std::cout << std::endl << "=== CONTENIDO COMPLETO DE LA COLA ===" << std::endl;
    if (cola->empty()) {
        std::cout << "La cola esta vacia" << std::endl;
    } else {
        std::cout << "Mostrando recursivamente:" << std::endl;
        cola->mostrarRecursivo(cola->obtenerFrente());
    }
    std::cout << "====================================" << std::endl;
}

int ColaControlador::generarNumeroAleatorio() {
    semilla = (semilla * 1103515245 + 12345) & 0x7fffffff;
    return (semilla % 99) + 1;
}

sf::Color ColaControlador::generarColorAleatorio() {
    int r = 100 + (generarNumeroAleatorio() * 17) % 155;
    int g = 100 + (generarNumeroAleatorio() * 23) % 155;
    int b = 100 + (generarNumeroAleatorio() * 31) % 155;
    return sf::Color(r, g, b);
}
