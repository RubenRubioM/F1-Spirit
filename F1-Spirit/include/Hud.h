#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <vector>

using namespace std;


class Hud
{
    public:
        Hud();

        sf::View* getHudView();

        void draw(sf::RenderWindow*);
        void updateVelocityText(float);
        virtual ~Hud();

    private:
        sf::View* hudView;
        sf::Texture* hudTexture;
        sf::Sprite* hud;
        sf::Text *velocityText;
        sf::Texture* fuelTexture;
        sf::Sprite* fuelSprite;
        vector<sf::Sprite> fuelVector; //Vectore where we storage all the fuel sprites

};

#endif // HUD_H
