/*
    NOTES:
    1) Car::getSprite() return a sf::Sprite* and we storage in sf::Sprites*(carSprites) but on draw function we have to pass her the value (sf::Sprite)

*/
#include "Game.h"
#include "Car.h"
#include <iostream>

#define NUMCARSMAX 51

using namespace std;

Game::Game(int x, int y, string title)
{
    window = new sf::RenderWindow(sf::VideoMode(x,y),title);


    Car *car = new Car(10,"Assets/graphics/car-rally-2-side.png");
    Car *car1 = new Car(10,"Assets/graphics/car-endurance-1-side.png");



    addCar(car->getSprite());
    addCar(car1->getSprite());

    car1->getSprite()->scale(2,2);
    car1->getSprite()->setPosition(400,400);


    event = new sf::Event();

    //GameLoop, infinity iterations
    gameLoop();
}


void Game::addCar(sf::Sprite* _sprite){
    carSprites[numCars] = _sprite;


    numCars++;
}

void Game::draw(){
    window->clear();

    //Draw all the cars
    for(unsigned int i=0; i<numCars;i++){
        window->draw(*carSprites[i]);

    }

    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    while(window->isOpen()){
        eventsLoop();


        draw();
    }
}

void Game::eventsLoop(){

    while(window->pollEvent(*event)){

        switch(event->type){
            //KeyPressed
            case sf::Event::KeyPressed:
                switch(event->key.code){

                    case sf::Keyboard::Escape:

                        window->close();
                        break;

                    case sf::Keyboard::W:


                        break;

                    default:
                        break;


                }//End switch keyPressed
                break;

            //Hit close button
            case sf::Event::Closed:

                window->close();
                break;

        }//End switch event type

    }
}


Game::~Game()
{
    //dtor
}
