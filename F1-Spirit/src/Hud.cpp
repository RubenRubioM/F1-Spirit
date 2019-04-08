#include "Hud.h"

Hud::Hud()
{
    sf::Texture* hudTexture = new sf::Texture();
    hudTexture->loadFromFile("Assets/graphics/hud/info f1 spirit.png");
    hud = new sf::Sprite(*hudTexture);

    hud->setOrigin(hud->getTexture()->getSize().x/2.f,hud->getTexture()->getSize().y/2.f);
    hud->setPosition(550,449);
    hud->setScale(1,0.75);

    hudView = new sf::View(sf::FloatRect(400,300,300,300));
    hudView->setViewport(sf::FloatRect(0.5,0.02,0.5,0.95));

    // ===== Initialize velocity text =====
    sf::Font *font = new sf::Font();
    font->loadFromFile("Assets/Fonts/Formula1-Regular.ttf");
    velocityText = new sf::Text("Hello",*font);
    velocityText->setOrigin(velocityText->getGlobalBounds().width / 2.f, velocityText->getGlobalBounds().height /2.f);
    velocityText->setPosition(570,430);
    velocityText->setColor(sf::Color::White);
    velocityText->setCharacterSize(30);

}

void Hud::updateVelocityText(float _velocity){

    //We do this because the pointing float precision
    if(_velocity<0) _velocity = 0;

    if(_velocity>3) _velocity = 3;

    if(_velocity>=1.f){
        //velocityText->setColor(sf::Color::)
    }

    _velocity *= 1000;
    string velocityString = to_string((int)_velocity);

    velocityText->setString(velocityString);
}

void Hud::draw(sf::RenderWindow* _window){
    _window->setView(*hudView);
    // ==== We draw first the image ====
    _window->draw(*hud);

    // ==== We draw now the texts and rectangles ====
    _window->draw(*velocityText);


}

Hud::~Hud()
{
    //dtor
}
