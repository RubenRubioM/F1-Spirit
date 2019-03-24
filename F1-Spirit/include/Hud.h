#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"


class Hud
{
    public:
        Hud();

        sf::View* getHudView();

        void draw(sf::RenderWindow*);
        virtual ~Hud();

    protected:

    private:
        sf::View* hudView;
        sf::Texture* hudTexture;
        sf::Sprite* hud;
};

#endif // HUD_H
