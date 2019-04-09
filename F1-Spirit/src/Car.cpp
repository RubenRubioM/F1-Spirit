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
    sprite->scale(0.5,0.5);
    sprite->setPosition(400,400);


}

void Car::run(float _deltaTime){


    if(getMoving()){
        if(getSpeed()<MAXSPEED){
            setSpeed(getSpeed()+getAceleration());
        }

    }else{
        if(getSpeed()>0){
            setSpeed(getSpeed()-getAceleration());

        }

    }

    float radians = (rotation*PI)/180.0;

    if(speed>0){
       sprite->move(speed*sin(radians)*_deltaTime,-speed*cos(radians)*_deltaTime);
    }else{
        sprite->move(0,0);
    }

}

void Car::reloadFuel(){
    fuelClock.restart();
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
sf::Clock Car::getSecondRotationClock(){return secondRotationClock;}
sf::Clock Car::getFuelClock(){return fuelClock;}

Car::~Car()
{

}
