#ifndef GHOSTCAR_H
#define GHOSTCAR_H


#include "SFML/Graphics.hpp"
#include "Car.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <queue>

struct Data{
    float x;
    float y;
    int angle;
};

class GhostCar
{
    public:
        GhostCar(string path, int carModel);
        virtual ~GhostCar();

        void updatePoint(Car*);
        void updatePosition();
        void draw(sf::RenderWindow*);
        void startGhost();

        sf::Sprite* getSprite();

    private:
        sf::Texture* texture;
        sf::Sprite* sprite;

        std::queue<Data> actualPoints;
        std::queue<Data> lastPoints;
};

#endif // GHOSTCAR_H
