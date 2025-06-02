#ifndef COLAVISTA_HPP
#define COLAVISTA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include <cmath>
#include "../Model/Cola.hpp"
#include "VistaBase.hpp"

enum EstadoMenuCola {
    GESTION_COLA
};

enum TipoAnimacionCola {
    SIN_ANIMACION_COLA,
    ANIMACION_ENQUEUE,
    ANIMACION_DEQUEUE
};

struct ElementoAnimadoCola {
    sf::Vector2f posicionActual;
    sf::Vector2f posicionDestino;
    sf::Color color;
    int valor;
    bool activo;
    float progreso;
};

class ColaVista : public VistaBase {
private:
    EstadoMenuCola estadoActual;

    // Parametros visuales
    const float RECT_WIDTH = 70.0f;
    const float RECT_HEIGHT = 70.0f;
    const float RECT_SPACING = 15.0f;
    const int BASE_X = 200;
    const int BASE_Y = 450;
    const float VELOCIDAD_ANIMACION = 2.0f;

    float tiempoAnimacion;
    TipoAnimacionCola tipoAnimacionActual;
    bool animacionEnCurso;
    ElementoAnimadoCola elementoEnAnimacion;
    bool mostrandoFront;
    float tiempoMostrarFront;

public:
    ColaVista(sf::RenderWindow* window);

    void mostrarGestionCola(const ModeloCola& cola);
    void dibujarCola(const ModeloCola& cola);
    void dibujarRectangulo(const NodoCola* nodo, int posicion, int totalElementos);
    void dibujarElementoAnimado();
    void dibujarPanelInfo(const ModeloCola& cola);
    void dibujarPanelControles();

    void iniciarAnimacionEnqueue(int valor, sf::Color color, const ModeloCola& cola);
    void iniciarAnimacionDequeue(int valor, sf::Color color, const ModeloCola& cola);
    void actualizarAnimaciones(float deltaTime);
    bool hayAnimacionEnCurso() const;
    void terminarAnimacion();

    void activarVisualizacionFront();
    void desactivarVisualizacionFront();

    void cambiarEstado(EstadoMenuCola nuevoEstado) { estadoActual = nuevoEstado; }
    EstadoMenuCola obtenerEstado() const { return estadoActual; }
};

#endif
