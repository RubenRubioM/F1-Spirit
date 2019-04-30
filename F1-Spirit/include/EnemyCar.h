#ifndef ENEMYCAR_H
#define ENEMYCAR_H

#include "SFML/Graphics.hpp"
#include "GhostCar.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>




class EnemyCar
{
    public:
        EnemyCar(string path,int carModel, string ia);
        virtual ~EnemyCar();

        void updatePosition();
        void draw(sf::RenderWindow*);
        sf::Sprite* getSprite();

    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        std::ifstream fe;

        std::queue<Data> pathing;
};

#endif // ENEMYCAR_H
