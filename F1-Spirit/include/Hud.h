#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

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
};

#endif // HUD_H
