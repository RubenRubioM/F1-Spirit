#ifndef CAR_H
#define CAR_H

#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

#define PI      3.141592
#define MAXSPEED    0.3
using namespace std;

class Car
{
    public:
        Car(float,string,int);

        void run(float);
        void reloadFuel();
        void gameOver();
        void updatePenalty();
        int updateGear(); //Returns the gear
        int breakPiece(); //Returns the broken piece
        void repairCar();

        float getSpeed();
        float getRotation();
        float getAceleration();
        bool getMoving();
        sf::Sprite* getSprite();
        sf::Clock getSecondRotationClock();
        sf::Clock getFuelClock();
        void setRotation(float);
        void setSpeed(float);
        void setMoving(bool);
        void setAceleration(float);


        virtual ~Car();

    private:
        float speed = 0;
        float rotation; // 45 or -45
        float aceleration;
        float speedPenalty = 1; // Penalty to be applied to our car speed
        bool moving = false;
        bool pieceBroken[4] = {false,false,false,false};
        sf::Clock secondRotationClock;
        sf::Clock fuelClock;
        sf::Texture *texture;
        sf::Sprite *sprite;


};

#endif // CAR_H
