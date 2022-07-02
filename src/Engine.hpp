#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

struct Point
{
    float x,y;
};

class Engine
{
    public:
        Engine();
        ~Engine();

        void run();
        void update(sf::Time deltaTime);
        void processEvents();
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
        void render();

        void addPoint(const float x, const float y);
        void Casteljau();
        void DeBoor(const int deg);

    public: // Normalement prive
        bool MouseL=false, MouseR=false, Echap=false, MouseRPressed = false, MouseLPressed = false;
        bool Left=false, Right=false, Up=false, Space=false, Down=false;
        bool SpacePressed=false, UpPressed=false, DownPressed=false, LeftPressed=false, RightPressed=false;
        sf::RenderWindow m_window;
        sf::Time TimePerFrame;

        sf::VertexArray Points; // Vertex à imprimer
        sf::VertexArray Lines;
        int nbPoint;

        Point findCt(float t, std::vector<Point> vec);
};


#endif // ENGINE_HPP_INCLUDED
