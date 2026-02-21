// @author Salgado González Edgar
//@class main. Clase que implementará y ejecutará nuestro código.
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Vector2.h"

void dibujarCurva(Vector2 p0, Vector2 p1, Vector2 p2, sf::RenderWindow* window);
int main()
{
    //Inicialización de la ventana para desplegar mi dibujo.
    sf::RenderWindow window(sf::VideoMode({400, 400}), "My window");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Se coloca la ventana en negro.
        window.clear(sf::Color::Black);
        // Se comienzan a dar las "estructuras" de las curvas de Bézier.
        Vector2 p0{70.f,154.f};
        Vector2 p1{170.f, -40.f};
        Vector2 p2{319.f, 135.f};
        dibujarCurva(p0, p1, p2, &window);
        p1.set(28.f, 349.f);
        p2.set(211.f, 340.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(211.f, 340.f);
        p1.set(381.f, 286.f);
        p2.set(319.f, 135.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(81.f, 220.f);
        p1.set(93.f, 213.f);
        p2.set(103.f, 209.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(93.f, 213.f);
        p1.set(98.f, 241.f);
        p2.set(114.f, 254.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(114.f, 254.f);
        p1.set(127.f, 251.f);
        p2.set(141.f, 256.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(141.f, 256.f);
        p1.set(160.f, 276.f);
        p2.set(175.f, 283.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(175.f, 283.f);
        p1.set(200.f, 300.f);
        p2.set(223.f, 283.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(223.f, 283.f);
        p1.set(236.f, 281.f);
        p2.set(248.f, 282.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(248.f, 282.f);
        p1.set(293.f, 244.f);
        p2.set(297.f, 176.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(289.f, 172.f);
        p1.set(299.f, 175.f);
        p2.set(310.f, 180.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(272.f, 257.f);
        p1.set(303.f, 291.f);
        p2.set(310.f, 267.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(310.f, 267.f);
        p1.set(308.f, 236.f);
        p2.set(284.f, 235.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(278.f, 245.f);
        p1.set(288.f, 250.f);
        p2.set(295.f, 260.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(117.f, 163.f);
        p1.set(127.f, 139.f);
        p2.set(144.f, 127.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(120.f, 134.f);
        p1.set(126.f, 152.f);
        p2.set(148.f, 164.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(228.f, 151.f);
        p1.set(234.f, 128.f);
        p2.set(248.f, 115.f);
        dibujarCurva(p0, p1, p2, &window);
        p0.set(222.f, 117.f);
        p1.set(236.f, 136.f);
        p2.set(258.f, 146.f);
        dibujarCurva(p0, p1, p2, &window);
        window.display();
    }
}
/*
@func. puntoCurva cálcula los puntos dentro de una curva de bézier conociendo
@param p0, p1, p2. Punto inicial, punto de "control" y punto final respectivamente de las curvas de Bézier
@param t. De 0 a 1, calcula un punto exacto dentro de la curva.
@return Vector2. Un punto dentro de la curva de Bézier.
*/
Vector2 puntoCurva(Vector2 p0, Vector2 p1, Vector2 p2, float t){
  Vector2 l0 = p0.lerp(p1, t);
  Vector2 l1 =p1.lerp(p2, t);
  return l0.lerp(l1, t);
}
/*
@func. dibujarCurva dibuja la curva de Bézier en pantalla.
@param p0, p1, p2. Punto inicial, punto de "control" y punto final respectivamente de las curvas de Bézier
@param window. La ventana que se usa para deplegar la imagen.
*/
void dibujarCurva(Vector2 p0, Vector2 p1, Vector2 p2, sf::RenderWindow* window){
    // En un vector (que funciona similar a una lista), guarda las posiciones de los puntos.
    std::vector<sf::Vector2f> posiciones;
    // Recopila la posición de 1000 puntos dentro de la curva de Bézier dada.
    for (float i = 0; i <= 1.0f; i += 0.001f)
    {
        Vector2 seguimiento = puntoCurva(p0, p1, p2, i);
        posiciones.push_back(sf::Vector2f(seguimiento.getX(), seguimiento.getY()));
    }
    // Le damos un tamaño de dibujado a cada uno de los puntos, además de darle color "come as you are"
    sf::RectangleShape puntoVisual({4.f, 4.f});
    puntoVisual.setFillColor(sf::Color::Yellow);
    // Se dibujan cada uno de los puntos simplemente cambiando la posición de la figura.
    for (const sf::Vector2f& pos : posiciones)
    {
        puntoVisual.setPosition(pos);
        window->draw(puntoVisual);
    }

}
