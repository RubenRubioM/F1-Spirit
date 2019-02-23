#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

class Game
{
    public:
        Game(int x,int y, std::string title);
        void draw();
        void gameLoop();
        void eventsLoop();
        void addCar(sf::Sprite*);
        virtual ~Game();

    protected:

    private:
        int numCars = 0;
        sf::RenderWindow *window;
        sf::Event *event;
        sf::Sprite* carSprites[51]; //Maximum 50 enemies and the player

};

#endif // GAME_H
