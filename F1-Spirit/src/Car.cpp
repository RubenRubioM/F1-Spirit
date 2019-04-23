#include "Car.h"
#include <math.h>
using namespace std;

Car::Car(float _aceleration,string path, int carModel)
{
    speed = 0;
    aceleration = _aceleration;
    texture = new sf::Texture();

    texture->loadFromFile(path,sf::IntRect(32*carModel,0,32,32));
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(16,16); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(0.5,0.5);
    sprite->setPosition(220,2300);

    hud = Hud::getInstance();



}

void Car::run(float _deltaTime){


    if(getMoving()){
        if(getSpeed()<MAXSPEED){
            setSpeed(getSpeed()+getAceleration()*speedPenalty);
        }

    }else{
        if(getSpeed()>0){
            setSpeed(getSpeed()-getAceleration()*speedPenalty);
        }
    }

    float radians = (rotation*PI)/180.0;

    if(speed>0){
       sprite->move(speed*sin(radians)*_deltaTime,-speed*cos(radians)*_deltaTime);
    }else{
        sprite->move(0,0);
    }

}

void Car::colision(){

    if(!colisionando){
        animationClock.restart();
        colisionando = true;
    }


    if(animationClock.getElapsedTime().asSeconds()>0.2 && frame<6){
        sf::Texture* textureAnimation = new sf::Texture();
        textureAnimation->loadFromFile("Assets/graphics/cars-f1.png",sf::IntRect(0,32*frame,32,32));
        sprite->setTexture(*textureAnimation);
        frame++;
        animationClock.restart();
    }else if(frame==6){
        sf::Texture* textureAnimation = new sf::Texture();
        textureAnimation->loadFromFile("Assets/graphics/cars-f1.png",sf::IntRect(0,0,32,32));
        sprite->setTexture(*textureAnimation);
        colisionando = false;
        frame = 0;
        hud->updatePieceBroken(breakPiece());
        sprite->setPosition(300,sprite->getPosition().y);
        speed = 0;
    }


}


int Car::updateGear(){


    if(speed <= 0.035f){
        aceleration = 0.0003;
        return 1;
    }else if(speed > 0.035f && speed <= 0.1f){
        aceleration = 0.00020;
        return 2;
    }else if(speed > 0.1f && speed <= 0.15f){
        aceleration = 0.00014;
        return 3;
    }else if(speed > 0.15f && speed <= 0.2f){
        aceleration = 0.00010;
        return 4;
    }else if(speed > 0.2f && speed <= 0.275f){
        aceleration = 0.00005;
        return 5;
    }else{
        aceleration = 0.00003;
        return 6;
    }
}

void Car::reloadFuel(){
    fuelClock.restart();
}

int Car::breakPiece(){
    bool broken = false;
    srand(time(NULL));

    int piece = 0;
    if(!carCrashed){
        while(!broken){
            piece = rand()%4;
            if(pieceBroken[piece]==false){
               pieceBroken[piece] = true;
               broken = true;
            }

        }

        updatePenalty();
    }

    return piece;
}

void Car::repairCar(){

    for(int i=0; i<4; i++){
        pieceBroken[i] = false;
    }

    updatePenalty();
}

void Car::updatePenalty(){

    int piecesBroken = 0;

    for(int i=0;i<4;i++){
        if(pieceBroken[i]){
            piecesBroken++;
        }
    }
    if(piecesBroken==4){
        carCrashed=true;
    }
    speedPenalty = 1 - (0.22*piecesBroken);

}


void Car::gameOver(){
    cout << "Game over..." << endl;
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

void Car::setAceleration(float _aceleration){
    aceleration = _aceleration;
}

void Car::setColisionando(bool _colisionando){
    colisionando = _colisionando;
}

void Car::setPitLane(bool _pitLane){
    pitLane = _pitLane;
}

void Car::switchGodMode(){
    if(godMode){
        godMode = false;
    }else{
        godMode = true;
    }
    hud->updateGodMode(godMode);
}

float Car::getSpeed(){return speed;}
float Car::getRotation(){return rotation;}
bool Car::getMoving(){return moving;}
bool Car::getColisionando(){return colisionando;}
float Car::getAceleration(){return aceleration;}
sf::Sprite* Car::getSprite(){return sprite;}
sf::Clock Car::getSecondRotationClock(){return secondRotationClock;}
sf::Clock Car::getFuelClock(){return fuelClock;}
bool Car::getPitLane(){return pitLane;}
bool Car::getGodMode(){return godMode;}


Car::~Car()
{

}
