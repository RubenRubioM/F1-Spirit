#include "Car.h"
#include <math.h>
using namespace std;

Car::Car(float _aceleration,string path, int carModel)
{
    speed = 0;
    aceleration = _aceleration;
    texture = new sf::Texture();

    texture->loadFromFile(path,sf::IntRect(32*carModel,0,32,32));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(16,16); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(1.5,1.5);
}

void Car::run(){
    float radians = (rotation*PI)/180.0;
    printf("%.6f\n",speed);

    if(speed>0){
       sprite->move(speed*sin(radians),-speed*cos(radians));
    }else{
        sprite->move(0,0);
    }

}

void Car::setRotation(float _rotation){
    rotation = _rotation;
    sprite->setRotation(rotation);
}

void Car::setSpeed(float _speed){
    speed = _speed;
}

void Car::setMoving(bool _moving){
    moving = _moving;
}

float Car::getSpeed(){return speed;}
float Car::getRotation(){return rotation;}
bool Car::getMoving(){return moving;}
float Car::getAceleration(){return aceleration;}
sf::Sprite* Car::getSprite(){return sprite;}

Car::~Car()
{

}
