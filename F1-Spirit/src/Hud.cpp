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
    velocityText->setPosition(565,430);
    velocityText->setColor(sf::Color::White);
    velocityText->setCharacterSize(30);

    // ==== Initialize fuel sprite ====
    fuelTexture = new sf::Texture();
    fuelTexture->loadFromFile("Assets/graphics/hud/fuel.png");
    fuelSprite = new sf::Sprite(*fuelTexture);
    fuelSprite->scale(2,1);
    fuelSprite->setColor(sf::Color(255, 0, 0));

    //We want 5 *fuelSprite
    for(int i=0; i<=4 ; i++){
       fuelVector.push_back(*fuelSprite);
       if(i==0){
          fuelVector.at(i).setPosition(500,493);
       }else{
          fuelVector.at(i).setPosition(fuelVector.at(0).getPosition().x+30*i, fuelVector.at(0).getPosition().y);
       }

    }


}

void Hud::updateVelocityText(float _velocity){

    //We do this because the pointing float precision and sometimes is 0.307 instead of 0.3 :(
    if(_velocity<0) _velocity = 0;

    if(_velocity>=0.3) _velocity = 0.3;

    //We change the color of the sf::Text *velocityText
    if(_velocity >= 0.1f && _velocity <0.2f){
        velocityText->setColor(sf::Color(76, 230, 0));
    }else if(_velocity >= 0.2f && _velocity <= 0.275f){

        velocityText->setColor(sf::Color(255, 166, 77));
    }else if(_velocity > 0.275f){
        velocityText->setColor(sf::Color(255, 26, 26));
    }else if(_velocity <0.1f){
        velocityText->setColor(sf::Color::White);
    }

    _velocity *= 1000;
    string velocityString = to_string((int)_velocity);

    velocityText->setString(velocityString);
}

// TODO: adjust to the final numbers
void Hud::updateFuel(float _time){
    if(_time <= 10.f){
        fuelLast = 4;
    }else if( _time >10.f && _time <=20.f){
        fuelLast = 3;
    }else if( _time >20.f && _time <=30.f){
        fuelLast = 2;
    }else if( _time >30.f && _time <=40.f){
        fuelLast = 1;
    }else{
        fuelLast = 0;
    }
}

void Hud::draw(sf::RenderWindow* _window){
    _window->setView(*hudView);
    // ==== We draw first the image ====
    _window->draw(*hud);

    // ==== We draw now the texts and rectangles ====
    _window->draw(*velocityText);

    for(int i=0; i<=fuelLast;i++){
        _window->draw(fuelVector.at(i));
    }


}

int Hud::getFuelLast(){return fuelLast;}

Hud::~Hud()
{
    //dtor
}
