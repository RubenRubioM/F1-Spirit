#ifndef CAR_H
#define CAR_H

#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Hud.h"

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
        void colision();

        float getSpeed();
        float getRotation();
        float getAceleration();
        bool getColisionando();
        bool getMoving();
        bool getPitLane();
        bool getGodMode();
        sf::Sprite* getSprite();
        sf::Clock getSecondRotationClock();
        sf::Clock getFuelClock();
        void setRotation(float);
        void setSpeed(float);
        void setMoving(bool);
        void setAceleration(float);
        void setColisionando(bool);
        void setPitLane(bool);
        void switchGodMode();


        virtual ~Car();

    private:
        float speed = 0;
        float rotation; // 45 or -45
        float aceleration;
        float speedPenalty = 1; // Penalty to be applied to our car speed
        int frame = 0;
        bool moving = false;
        bool pieceBroken[4] = {false,false,false,false};
        bool carCrashed = false;
        bool colisionando = false;
        bool pitLane = false;
        bool godMode = false;
        sf::Clock secondRotationClock;
        sf::Clock fuelClock;
        sf::Clock animationClock;
        sf::Texture *texture;
        sf::Sprite *sprite;
        Hud* hud;


};

#endif // CAR_H
