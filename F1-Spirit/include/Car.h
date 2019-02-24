#ifndef CAR_H
#define CAR_H

#include "SFML/Graphics.hpp"

#define PI      3.141592
using namespace std;

class Car
{
    public:
        Car(float,string,int);
        void run();
        float getSpeed();
        float getRotation();
        float getAceleration();
        bool getMoving();
        sf::Sprite* getSprite();
        void setRotation(float);
        void setSpeed(float);
        void setMoving(bool);

        virtual ~Car();

    private:
        float speed = 0;
        float rotation; // 45 or -45
        float aceleration;
        bool moving = false;
        sf::Texture *texture;
        sf::Sprite *sprite;


};

#endif // CAR_H
