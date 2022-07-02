#include "Engine.hpp"

#define k 4

Engine::Engine(): m_window(sf::VideoMode(700,700), "Application SFML"),
    Points(sf::Points, 5000),
    Lines(sf::Lines, 5000),
    nbPoint(0)
{
    TimePerFrame = sf::seconds(1.f/120.f);
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
                
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;

            default:
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { 
        this-> MouseL = isPressed;
        if(!isPressed) { this->MouseLPressed=false; }
    }
    if(mouse == sf::Mouse::Right) {
        this-> MouseR = isPressed;
        if(!isPressed) { this->MouseRPressed=false; }
    }
}

void Engine::update(sf::Time deltaTime)
{
    //////////////////////////////////////////////////////////////
    ////////////// Reponse aux inputs ////////////////////////////
    //////////////////////////////////////////////////////////////

    if(Echap) { m_window.close(); }
    if(MouseL && !MouseLPressed) { 
        addPoint(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
        MouseLPressed = true;
    }
    if(MouseR && !MouseRPressed) {}
    if(Left && !LeftPressed) { }
    if(Right && !RightPressed) { }
    if(Up && !UpPressed) {  }
    if(Down) {  }
    if(Space) { }

    //////////////////////////////////////////////////
    ////////////// Update ////////////////////////////
    //////////////////////////////////////////////////
}

void Engine::addPoint(const float x, const float y)
{
        nbPoint++;
        Points[nbPoint-1].position = sf::Vector2f(x,y);
        Points[nbPoint-1].color = sf::Color(255,255,255);

        Casteljau();
}

void Engine::Casteljau(void)
{
    std::vector<Point> lNoeuds1;

    lNoeuds1.clear();
    for(int j=0; j<nbPoint; j++)
    {
        Point p;
        p.x = Points[j].position.x;
        p.y = Points[j].position.y;
        lNoeuds1.push_back(p);
    }

    std::vector<Point> Ct;
    Ct.clear();
    for(float t=0; t<=1; t+=0.005) {
        Ct.push_back(findCt(t,lNoeuds1));
    }

    for(int i=0; i < 1/0.005; i++)
    {
        Lines[i*2].position = sf::Vector2f(Ct[i].x, Ct[i].y);
        Lines[i*2+1].position = sf::Vector2f(Ct[i+1].x, Ct[i+1].y);
        Lines[i*2].color = sf::Color::Yellow;
        Lines[i*2+1].color = sf::Color::Red;
    }
}

void Engine::DeBoor(const int deg)
{
    
}

Point Engine::findCt(float t, std::vector<Point> vec)
{
    for(int i=1; i<nbPoint; i++) {
        for(int j=0; j < nbPoint-i; j++) {
            vec[j].x = (1.0-t) * vec[j].x + t * vec[j+1].x;
            vec[j].y = (1.0-t) * vec[j].y + t * vec[j+1].y;
        }
    }

    return vec[0];
}

void Engine::render(void)
{
    m_window.clear();
    m_window.draw(Points);
    m_window.draw(Lines);
    m_window.display();
}

Engine::~Engine()
{}