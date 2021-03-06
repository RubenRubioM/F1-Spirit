#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "Car.h"
#include "Camera.h"
#include "Hud.h"
#include "GhostCar.h"
#include "EnemyCar.h"

#define NUMCARSMAX 51

using namespace std;


class Game
{
    public:
        Game(int x,int y, std::string title);
        void draw();
        void gameLoop();
        void eventsLoop();
        void addCar(Car*);
        virtual ~Game();

    protected:

    private:
        int numCars = 0;
        int numLap = 1;
        sf::Clock lapClock;
        sf::RenderWindow *window;
        sf::Event *event;
        sf::Time deltaTime;
        sf::Sprite* carSprites[NUMCARSMAX]; //Maximum 50 enemies and the player
        Car* cars[NUMCARSMAX];
        vector<EnemyCar*> enemyCars;
        Camera *playerCamera;
        GhostCar* ghostCar;
        sf::Sprite* roadSprite;
        sf::Texture* roadTexture;
        sf::Sprite* roadHeatSprite;
        sf::Texture* roadHeatTexture;

        sf::Texture* treesTexture;
        sf::Sprite* treesLeft;
        sf::Sprite* treesRight;

        sf::Texture* pitLaneTexture;
        sf::Sprite* pitLaneSprite;

        sf::View* minimap;
        sf::RectangleShape playerCircle;
        sf::RectangleShape ghostCircle;


        sf::Clock lapTimeClock;
        sf::Text* lapTimeText;
        sf::Font* font;

        sf::Clock pitLaneClock;
        sf::Clock pitLaneCD;

        Hud* hud;

        sf::Clock rotationClock;
        bool rotationKeyUp = false;
        bool raceFinished = false;

        enum carModels{
            Model1=0,Model2=1,Model3=2,Model4=3,Model5=4,Model6=6,Model7=7,Model8=8,Model9=9,Model10=10  //We skip model 5 because is the same as model 1
        };

};

#endif // GAME_H
