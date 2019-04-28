#include "GhostCar.h"

GhostCar::GhostCar(string path, int carModel)
{
    texture = new sf::Texture();

    texture->loadFromFile(path,sf::IntRect(32*carModel,0,32,32));
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(16,16); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->setColor(sf::Color(255,255,255,100));

}

void GhostCar::updatePoint(Car* _player){
    Data d;
    d.x = _player->getSprite()->getPosition().x;
    d.y = _player->getSprite()->getPosition().y;
    d.angle = _player->getRotation();

    actualPoints.push(d);
}

void GhostCar::updatePosition(){

    if(!lastPoints.empty()){
        float x = lastPoints.front().x;
        float y = lastPoints.front().y;
        int angle = lastPoints.front().angle;

        sprite->setPosition(x,y);
        sprite->setRotation(angle);
        lastPoints.pop();
    }

}

//Called when the lap is over to save the last points and empty the queue to store the new ones
void GhostCar::startGhost(){
    lastPoints = actualPoints;

    //Empty the queue to store the new points
    while(!actualPoints.empty()){
        actualPoints.pop();
    }
}

void GhostCar::draw(sf::RenderWindow* _window){
    _window->draw(*sprite);
}


sf::Sprite* GhostCar::getSprite(){return sprite;}

GhostCar::~GhostCar()
{
    //dtor
}
