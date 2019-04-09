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
        void updateFuel(float); //This method will recieve the seconds since last fuel reload
        void updateGear(int);
        void updatePieceBroken(int);
        void repairPieces();

        int getFuelLast();

        virtual ~Hud();

    private:
        int fuelLast = 4;
        sf::View* hudView;
        sf::Texture* hudTexture;
        sf::Sprite* hud;
        sf::Font *font;
        sf::Text *velocityText;
        sf::Text *gearText;
        sf::Texture* fuelTexture;
        sf::Sprite* fuelSprite;
        sf::Texture *brokenBoxTexture;
        sf::Sprite *brokenBoxSprite;
        vector<sf::Sprite> brokenPieces;
        vector<sf::Sprite> fuelVector; //Vector where we storage all the fuel sprites

};

#endif // HUD_H
