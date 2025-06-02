#ifndef LISTADOBLEVISUAL_HPP
#define LISTADOBLEVISUAL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

struct NodoVisual {
    std::string texto;
    sf::Color color;
};

inline std::vector<NodoVisual> listaVisual;

const int ANCHO = 120;
const int ALTO = 50;
const int POS_Y = 250;
const int ORIGEN_X = 60;

void dibujarAyudaLista(sf::RenderWindow& window, sf::Font& fuente) {
    float windowWidth = 800.f;
    float boxWidth = 260.f;
    float posX = windowWidth - boxWidth - 10.f;
    float posY = 10.f;


    sf::RectangleShape fondo(sf::Vector2f(boxWidth, 120));
    fondo.setPosition(sf::Vector2f(posX, posY));
    fondo.setFillColor(sf::Color(30, 30, 30, 200));
    fondo.setOutlineThickness(2);
    fondo.setOutlineColor(sf::Color::White);
    window.draw(fondo);

    sf::Text titulo(fuente, "Informacion de la Lista", 16);
    titulo.setFillColor(sf::Color::Yellow);
    titulo.setPosition(sf::Vector2f(posX + 10.f, posY + 5.f));
    window.draw(titulo);

    sf::Text explicacion1(fuente, "-->  : siguiente nodo", 14);
    explicacion1.setFillColor(sf::Color::Red);
    explicacion1.setPosition(sf::Vector2f(posX + 10.f, posY + 30.f));
    window.draw(explicacion1);

    sf::Text explicacion2(fuente, "<--  : nodo anterior", 14);
    explicacion2.setFillColor(sf::Color::Cyan);
    explicacion2.setPosition(sf::Vector2f(posX + 10.f, posY + 55.f));
    window.draw(explicacion2);

    sf::Text contadorLabel(fuente, "Total: " + std::to_string(listaVisual.size()), 14);
    contadorLabel.setFillColor(sf::Color::Green);
    contadorLabel.setPosition(sf::Vector2f(posX + 10.f, posY + 80.f));
    window.draw(contadorLabel);
}




void dibujarLista(sf::RenderWindow& window, sf::Font& fuente) {
    int espacio = ANCHO + 30;
    dibujarAyudaLista(window, fuente);

    for (size_t i = 0; i < listaVisual.size(); ++i) {
        float x = ORIGEN_X + i * espacio;


        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(sf::Vector2f(x, POS_Y));
        rect.setFillColor(listaVisual[i].color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);


        sf::Text texto(fuente, listaVisual[i].texto, 16);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(sf::Vector2f(x + 10.f, POS_Y + 10.f));
        window.draw(texto);


        if (i < listaVisual.size() - 1) {
            float xInicio = x + ANCHO;
            float xFinal = x + espacio;
            float yCentro = POS_Y + ALTO / 2;


            sf::VertexArray flechaAdelante(sf::PrimitiveType::Lines, 2);
            flechaAdelante[0].position = sf::Vector2f(xInicio, yCentro);
            flechaAdelante[1].position = sf::Vector2f(xFinal - 10, yCentro);
            flechaAdelante[0].color = flechaAdelante[1].color = sf::Color::Red;
            window.draw(flechaAdelante);


            sf::CircleShape punta(5, 3);
            punta.setRotation(sf::degrees(90));
            punta.setFillColor(sf::Color::Red);
            punta.setPosition(sf::Vector2f(xFinal - 1, yCentro - 5));
            window.draw(punta);


            sf::VertexArray flechaAtras(sf::PrimitiveType::Lines, 2);
            flechaAtras[0].position = sf::Vector2f(xFinal, yCentro + 10);
            flechaAtras[1].position = sf::Vector2f(xInicio + 10, yCentro + 10);
            flechaAtras[0].color = flechaAtras[1].color = sf::Color::Cyan;
            window.draw(flechaAtras);


            sf::CircleShape puntaAtras(5, 3);
            puntaAtras.setRotation(sf::degrees(270));
            puntaAtras.setFillColor(sf::Color::Cyan);
            puntaAtras.setPosition(sf::Vector2f(xInicio + 2, yCentro + 15));
            window.draw(puntaAtras);
        }


        sf::Text indice(fuente, std::to_string(i), 14);
        indice.setFillColor(sf::Color::White);
        indice.setPosition(sf::Vector2f(x + ANCHO / 2.f - 5.f, POS_Y + ALTO + 5.f));
        window.draw(indice);
    }


    if (!listaVisual.empty()) {
        int espacio = ANCHO + 30;


        float xHead = ORIGEN_X;
        sf::Text headLabel(fuente, "HEAD", 16);
        headLabel.setFillColor(sf::Color::Green);
        headLabel.setPosition(sf::Vector2f(xHead + 20.f, POS_Y - 30.f));
        window.draw(headLabel);


        float xTail = ORIGEN_X + (listaVisual.size() - 1) * espacio;
        sf::Text tailLabel(fuente, "TAIL", 16);
        tailLabel.setFillColor(sf::Color::Cyan);
        tailLabel.setPosition(sf::Vector2f(xTail + 20.f, POS_Y - 30.f));
        window.draw(tailLabel);
    }




}



void animarInsercion(sf::RenderWindow& window, sf::Font& fuente, const std::string& dato, size_t pos) {
    NodoVisual nuevoNodo;
    nuevoNodo.texto = dato;
    nuevoNodo.color = sf::Color(rand() % 255, rand() % 255, rand() % 255);


    int pasos = 20;
    float yInicio = -100;
    float yFinal = POS_Y;
    float deltaY = (yFinal - yInicio) / pasos;

    for (int i = 0; i <= pasos; ++i) {
        float yActual = yInicio + i * deltaY;

        window.clear();

        int espacio = ANCHO + 30;


        for (size_t j = 0; j < listaVisual.size(); ++j) {
            float x = ORIGEN_X + ((j >= pos) ? (j + 1) : j) * espacio;
            float y = POS_Y;

            sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
            rect.setPosition(sf::Vector2f(x, y));
            rect.setFillColor(listaVisual[j].color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto(fuente, listaVisual[j].texto, 16);
            texto.setFillColor(sf::Color::White);
            texto.setPosition(sf::Vector2f(x + 10.f, y + 10.f));
            window.draw(texto);
        }


        float xNuevo = ORIGEN_X + pos * espacio;

        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(sf::Vector2f(xNuevo, yActual));
        rect.setFillColor(nuevoNodo.color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::White);
        window.draw(rect);

        sf::Text texto(fuente, dato, 16);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(sf::Vector2f(xNuevo + 10.f, yActual + 10.f));
        window.draw(texto);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }


    listaVisual.insert(listaVisual.begin() + pos, nuevoNodo);
}



void eliminarVisual(sf::RenderWindow& window, sf::Font& fuente, const std::string& dato) {
    auto it = std::find_if(listaVisual.begin(), listaVisual.end(), [&](const NodoVisual& n) {
        return n.texto == dato;
    });

    if (it == listaVisual.end())
        return;

    size_t pos = std::distance(listaVisual.begin(), it);
    NodoVisual nodo = *it;


    float yInicio = POS_Y;
    float yFinal = POS_Y + 80;
    int pasos = 15;
    float deltaY = (yFinal - yInicio) / pasos;

    for (int i = 0; i <= pasos; ++i) {
        float yActual = yInicio + i * deltaY;

        window.clear();

        int espacio = ANCHO + 30;

        for (size_t j = 0; j < listaVisual.size(); ++j) {
            if (j == pos) continue;

            float x = ORIGEN_X + ((j < pos) ? j : (j - 1)) * espacio;

            sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
            rect.setPosition(sf::Vector2f(x, POS_Y));
            rect.setFillColor(listaVisual[j].color);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            window.draw(rect);

            sf::Text texto(fuente, listaVisual[j].texto, 16);
            texto.setFillColor(sf::Color::White);
            texto.setPosition(sf::Vector2f(x + 10.f, POS_Y + 10.f));
            window.draw(texto);
        }


        float xNodo = ORIGEN_X + pos * espacio;

        sf::RectangleShape rect(sf::Vector2f(ANCHO, ALTO));
        rect.setPosition(sf::Vector2f(xNodo, yActual));
        rect.setFillColor(nodo.color);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Red);
        window.draw(rect);

        sf::Text texto(fuente, nodo.texto, 16);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(sf::Vector2f(xNodo + 10.f, yActual + 10.f));
        window.draw(texto);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }


    listaVisual.erase(it);
}





#endif
