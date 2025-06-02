#include "ColaVista.hpp"

ColaVista::ColaVista(sf::RenderWindow* window)
    : VistaBase(window), estadoActual(GESTION_COLA),
      tiempoAnimacion(0.0f), tipoAnimacionActual(SIN_ANIMACION_COLA),
      animacionEnCurso(false), elementoEnAnimacion(),
      mostrandoFront(false), tiempoMostrarFront(0.0f) {
    elementoEnAnimacion.activo = false;
}

void ColaVista::mostrarGestionCola(const ModeloCola& cola) {
    limpiarPantalla();

    sf::RectangleShape fondo(sf::Vector2f(1200, 800));
    fondo.setFillColor(sf::Color(25, 30, 45));
    fondo.setPosition(sf::Vector2f(0, 0));
    ventana->draw(fondo);

    sf::Text titulo(fuente, "COLA (FIFO) - SIMULACION REALISTA", 24);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(sf::Vector2f(350, 20));
    titulo.setStyle(sf::Text::Bold);

    dibujarPanelInfo(cola);
    dibujarPanelControles();
    dibujarCola(cola);

    if (animacionEnCurso && elementoEnAnimacion.activo) {
        dibujarElementoAnimado();
    }
    ventana->draw(titulo);
    mostrarPantalla();
}

void ColaVista::dibujarCola(const ModeloCola& cola) {
    NodoCola* actual = cola.obtenerFrente();
    int posicion = 0;
    int totalElementos = cola.size();

    while (actual != nullptr) {
        dibujarRectangulo(actual, posicion, totalElementos);
        actual = actual->siguiente;
        posicion++;
    }
}

void ColaVista::dibujarRectangulo(const NodoCola* nodo, int posicion, int totalElementos) {
    float rectX = BASE_X + posicion * (RECT_WIDTH + RECT_SPACING);
    float rectY = BASE_Y;

    sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
    rect.setFillColor(nodo->color);
    rect.setOutlineThickness(3);
    rect.setPosition(sf::Vector2f(rectX, rectY));

    if (posicion == 0) {
        if (mostrandoFront) {
            rect.setOutlineColor(sf::Color::Magenta);
            rect.setOutlineThickness(6);
        } else {
            rect.setOutlineColor(sf::Color::Yellow);
        }
    } else {
        rect.setOutlineColor(sf::Color::White);
    }

    sf::Text valorTexto(fuente, std::to_string(nodo->dato), 20);
    valorTexto.setFillColor(sf::Color::Black);
    valorTexto.setStyle(sf::Text::Bold);
    centrarTexto(valorTexto, rectX, rectY, RECT_WIDTH, RECT_HEIGHT);

    if (posicion == 0) {
        sf::Text frontIndicator(fuente, "<-- FRENTE", 16);
        frontIndicator.setFillColor(sf::Color::Red);
        frontIndicator.setStyle(sf::Text::Bold);
        frontIndicator.setPosition(sf::Vector2f(rectX, rectY - 30));
        ventana->draw(frontIndicator);
    }
    if (posicion == totalElementos - 1) {
        sf::Text finalIndicator(fuente, "<-- FINAL", 14);
        finalIndicator.setFillColor(sf::Color::Green);
        finalIndicator.setPosition(sf::Vector2f(rectX, rectY + RECT_HEIGHT + 10));
        ventana->draw(finalIndicator);
    }

    ventana->draw(rect);
    ventana->draw(valorTexto);
}

void ColaVista::dibujarElementoAnimado() {
    if (!elementoEnAnimacion.activo) return;

    sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
    rect.setFillColor(elementoEnAnimacion.color);
    rect.setOutlineThickness(4);
    rect.setOutlineColor(sf::Color::Yellow);

    rect.setPosition(elementoEnAnimacion.posicionActual);

    sf::Text valorTexto(fuente, std::to_string(elementoEnAnimacion.valor), 20);
    valorTexto.setFillColor(sf::Color::Black);
    valorTexto.setStyle(sf::Text::Bold);
    centrarTexto(valorTexto, elementoEnAnimacion.posicionActual.x,
                elementoEnAnimacion.posicionActual.y, RECT_WIDTH, RECT_HEIGHT);

    ventana->draw(rect);
    ventana->draw(valorTexto);
}

void ColaVista::dibujarPanelInfo(const ModeloCola& cola) {
    sf::RectangleShape panelInfo(sf::Vector2f(220, 180));
    panelInfo.setFillColor(sf::Color(35, 40, 55));
    panelInfo.setOutlineThickness(2);
    panelInfo.setOutlineColor(sf::Color(70, 130, 180));
    panelInfo.setPosition(sf::Vector2f(20, 60));

    sf::Text tituloInfo(fuente, "INFORMACION DE LA COLA", 14);
    tituloInfo.setFillColor(sf::Color::White);
    tituloInfo.setPosition(sf::Vector2f(30, 75));
    tituloInfo.setStyle(sf::Text::Bold);

    sf::Text elementos(fuente, "Elementos: " + std::to_string(cola.size()) + "/8", 12);
    elementos.setFillColor(sf::Color(100, 200, 255));
    elementos.setPosition(sf::Vector2f(30, 105));

    sf::Text frontInfo(fuente, "", 12);
    frontInfo.setFillColor(sf::Color(100, 255, 100));
    frontInfo.setPosition(sf::Vector2f(30, 130));
    if (!cola.empty()) {
        frontInfo.setString("FRENTE: " + std::to_string(cola.front()->dato));
    } else {
        frontInfo.setString("FRENTE: Vacia");
    }

    sf::Text estado(fuente, "", 12);
    estado.setPosition(sf::Vector2f(30, 155));
    if (cola.empty()) {
        estado.setString("Estado: VACIA");
        estado.setFillColor(sf::Color::Red);
    } else if (cola.full()) {
        estado.setString("Estado: LLENA");
        estado.setFillColor(sf::Color::Red);
    } else {
        estado.setString("Estado: NORMAL");
        estado.setFillColor(sf::Color::Green);
    }

    sf::RectangleShape barraFondo(sf::Vector2f(180, 12));
    barraFondo.setFillColor(sf::Color(40, 40, 40));
    barraFondo.setOutlineThickness(1);
    barraFondo.setOutlineColor(sf::Color::White);
    barraFondo.setPosition(sf::Vector2f(30, 185));

    float porcentaje = (float)cola.size() / 8.0f;
    sf::RectangleShape barraLleno(sf::Vector2f(180.0f * porcentaje, 12));
    sf::Color colorBarra = porcentaje < 0.7f ? sf::Color::Green :
                          porcentaje < 0.9f ? sf::Color::Yellow : sf::Color::Red;
    barraLleno.setFillColor(colorBarra);
    barraLleno.setPosition(sf::Vector2f(30, 185));

    ventana->draw(panelInfo);
    ventana->draw(tituloInfo);
    ventana->draw(elementos);
    ventana->draw(frontInfo);
    ventana->draw(estado);
    ventana->draw(barraFondo);
    ventana->draw(barraLleno);
}

void ColaVista::dibujarPanelControles() {
    sf::RectangleShape panelControles(sf::Vector2f(220, 200));
    panelControles.setFillColor(sf::Color(35, 40, 55));
    panelControles.setOutlineThickness(2);
    panelControles.setOutlineColor(sf::Color(255, 150, 100));
    panelControles.setPosition(sf::Vector2f(20, 260));

    sf::Text tituloControles(fuente, "CONTROLES", 14);
    tituloControles.setFillColor(sf::Color::White);
    tituloControles.setPosition(sf::Vector2f(30, 275));
    tituloControles.setStyle(sf::Text::Bold);

    sf::Text enqControl(fuente, "ENTER: Enqueue (Agregar)", 11);
    enqControl.setFillColor(sf::Color(100, 255, 100));
    enqControl.setPosition(sf::Vector2f(30, 305));

    sf::Text deqControl(fuente, "SPACE: Dequeue (Eliminar)", 11);
    deqControl.setFillColor(sf::Color(255, 100, 100));
    deqControl.setPosition(sf::Vector2f(30, 330));

    sf::Text frontControl(fuente, "F: Front (Ver frente)", 11);
    frontControl.setFillColor(sf::Color(100, 100, 255));
    frontControl.setPosition(sf::Vector2f(30, 355));

    sf::Text emptyControl(fuente, "E: Empty (Verificar vacio)", 11);
    emptyControl.setFillColor(sf::Color(255, 255, 100));
    emptyControl.setPosition(sf::Vector2f(30, 380));

    sf::Text mostrarControl(fuente, "M: Mostrar recursivo", 11);
    mostrarControl.setFillColor(sf::Color(255, 150, 255));
    mostrarControl.setPosition(sf::Vector2f(30, 405));

    sf::RectangleShape separador(sf::Vector2f(180, 1));
    separador.setFillColor(sf::Color(100, 100, 100));
    separador.setPosition(sf::Vector2f(30, 425));

    sf::Text volverControl(fuente, "ESC: Volver al menu", 11);
    volverControl.setFillColor(sf::Color(200, 200, 200));
    volverControl.setPosition(sf::Vector2f(30, 435));

    ventana->draw(panelControles);
    ventana->draw(tituloControles);
    ventana->draw(enqControl);
    ventana->draw(deqControl);
    ventana->draw(frontControl);
    ventana->draw(emptyControl);
    ventana->draw(mostrarControl);
    ventana->draw(separador);
    ventana->draw(volverControl);
}

void ColaVista::iniciarAnimacionEnqueue(int valor, sf::Color color, const ModeloCola& cola) {
    tipoAnimacionActual = ANIMACION_ENQUEUE;
    animacionEnCurso = true;
    tiempoAnimacion = 0.0f;

    elementoEnAnimacion.valor = valor;
    elementoEnAnimacion.color = color;
    elementoEnAnimacion.activo = true;
    elementoEnAnimacion.progreso = 0.0f;
    elementoEnAnimacion.posicionActual = sf::Vector2f(BASE_X - 150, BASE_Y);

    int totalElementos = cola.size();
    float destinoX = BASE_X + (totalElementos - 1) * (RECT_WIDTH + RECT_SPACING);
    elementoEnAnimacion.posicionDestino = sf::Vector2f(destinoX, BASE_Y);
}

void ColaVista::iniciarAnimacionDequeue(int valor, sf::Color color, const ModeloCola& cola) {
    tipoAnimacionActual = ANIMACION_DEQUEUE;
    animacionEnCurso = true;
    tiempoAnimacion = 0.0f;

    elementoEnAnimacion.valor = valor;
    elementoEnAnimacion.color = color;
    elementoEnAnimacion.activo = true;
    elementoEnAnimacion.progreso = 0.0f;

    elementoEnAnimacion.posicionActual = sf::Vector2f(BASE_X, BASE_Y);
    elementoEnAnimacion.posicionDestino = sf::Vector2f(BASE_X + 900, BASE_Y);
}

void ColaVista::actualizarAnimaciones(float deltaTime) {
    tiempoAnimacion += deltaTime;

    if (mostrandoFront) {
        tiempoMostrarFront += deltaTime;
        if (tiempoMostrarFront >= 2.0f) {
            desactivarVisualizacionFront();
        }
    }

    if (animacionEnCurso && elementoEnAnimacion.activo) {
        float velocidadActual = VELOCIDAD_ANIMACION;
        elementoEnAnimacion.progreso += deltaTime * velocidadActual;

        if (elementoEnAnimacion.progreso >= 1.0f) {
            elementoEnAnimacion.progreso = 1.0f;
            terminarAnimacion();
        }
        float t = elementoEnAnimacion.progreso < 0.5f
            ? 2.0f * elementoEnAnimacion.progreso * elementoEnAnimacion.progreso
            : -1.0f + (4.0f - 2.0f * elementoEnAnimacion.progreso) * elementoEnAnimacion.progreso;

        sf::Vector2f diferencia = elementoEnAnimacion.posicionDestino - elementoEnAnimacion.posicionActual;
        elementoEnAnimacion.posicionActual = elementoEnAnimacion.posicionActual + diferencia * t * deltaTime * 3.0f;
    }
}

bool ColaVista::hayAnimacionEnCurso() const {
    return animacionEnCurso;
}

void ColaVista::terminarAnimacion() {
    animacionEnCurso = false;
    elementoEnAnimacion.activo = false;
    tipoAnimacionActual = SIN_ANIMACION_COLA;
}

void ColaVista::activarVisualizacionFront() {
    mostrandoFront = true;
    tiempoMostrarFront = 0.0f;
}

void ColaVista::desactivarVisualizacionFront() {
    mostrandoFront = false;
}



