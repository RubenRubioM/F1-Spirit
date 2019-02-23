#ifndef CAR_H
#define CAR_H

#include "SFML/Graphics.hpp"
using namespace std;

class Car
{
    public:
        Car(float,string);
        float getSpeed();
        sf::Sprite* getSprite();
        virtual ~Car();

    protected:

    private:
        float speed;
        sf::Texture *texture;
        sf::Sprite *sprite;


};

#endif // CAR_H
