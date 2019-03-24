#include "Hud.h"

Hud::Hud()
{
    sf::Texture* hudTexture = new sf::Texture();
    hudTexture->loadFromFile("Assets/graphics/hud/info f1 spirit.png");
    hud = new sf::Sprite(*hudTexture);

    hud->setOrigin(hud->getTexture()->getSize().x/2,hud->getTexture()->getSize().y/2);
    hud->setPosition(550,449);
    hud->setScale(1,0.75);

    hudView = new sf::View(sf::FloatRect(400,300,300,300));
    hudView->setViewport(sf::FloatRect(0.5,0.02,0.5,0.95));
}

void Hud::draw(sf::RenderWindow* _window){
    _window->setView(*hudView);
    _window->draw(*hud);
}

Hud::~Hud()
{
    //dtor
}
