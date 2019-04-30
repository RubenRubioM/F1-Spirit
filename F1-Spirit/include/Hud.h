#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <iomanip>

using namespace std;


class Hud
{
    public:
        static Hud *getInstance(){
            if(unicaInstancia == 0){
                unicaInstancia = new Hud();
            }
            return unicaInstancia;
        }

        sf::View* getHudView();

        void draw(sf::RenderWindow*);
        void updateVelocityText(float);
        void updateFuel(float); //This method will recieve the seconds since last fuel reload
        void updateGear(int);
        void updatePieceBroken(int);
        void repairPieces();
        void updateLap(int);
        void updateLapClock(float);
        void updateGodMode(bool);

        int getFuelLast();
        sf::Text* getLapTimeText();

        virtual ~Hud();

    private:
        Hud();
        static Hud *unicaInstancia;
        int fuelLast = 4;
        int fuelTickTime = 15;
        sf::View* hudView;
        sf::Texture* hudTexture;
        sf::Sprite* hud;
        sf::Font *font;
        sf::Text *velocityText;
        sf::Text *gearText;
        sf::Text *lapText;
        sf::Text *lapTimeText;
        sf::Text *godModeText;
        sf::Texture* fuelTexture;
        sf::Sprite* fuelSprite;
        sf::Texture *brokenBoxTexture;
        sf::Sprite *brokenBoxSprite;
        vector<sf::Sprite> brokenPieces;
        vector<sf::Sprite> fuelVector; //Vector where we storage all the fuel sprites

};

#endif // HUD_H
