#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

class Game
{
    public:
        Game(int x,int y, std::string title);
        void draw();
        void gameLoop();
        void eventsLoop();
        virtual ~Game();

    protected:

    private:
        sf::RenderWindow *window;
        sf::Texture *texture1;
        sf::Sprite *sprite1;
        sf::Event *event;
};

#endif // GAME_H
