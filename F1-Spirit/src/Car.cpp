#include "Car.h"

using namespace std;

Car::Car(float _speed, string path)
{
    speed = _speed;
    texture = new sf::Texture();

    texture->loadFromFile(path);
    sprite = new sf::Sprite(*texture);
}



float Car::getSpeed(){return speed;}

sf::Sprite* Car::getSprite(){return sprite;}

Car::~Car()
{
    //dtor
}
