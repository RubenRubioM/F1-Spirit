/*
    NOTES:
    1) Car::getSprite() returns a sf::Sprite* and we storage in sf::Sprites*(carSprites) but on draw function we have to pass her the value (sf::Sprite)
    2) The events loops only executes when an event happens, this is why we have to put the movement system outside the loop

*/
#include "Game.h"

#include <iostream>
#include <math.h>

#define MAXSPEED    0.3


using namespace std;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();

    Car *player = new Car(0.003,"Assets/graphics/cars-f1.png",Model1);
    player->getSprite()->setPosition(400,400);


    //adding cars
    addCar(player);

    //GameLoop, infinity iterations
    gameLoop();
}


void Game::addCar(Car* car){
    cars[numCars] = car;
    numCars++;
}

void Game::draw(){
    window->clear();

    //Draw all the cars
    for(unsigned int i=0; i<numCars;i++){
        window->draw(*cars[i]->getSprite());

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
    Car *player = cars[0];
    while(window->pollEvent(*event)){

        switch(event->type){
            //KeyPressed
            case sf::Event::KeyPressed:
                switch(event->key.code){

                    case sf::Keyboard::Escape:

                        window->close();
                        break;

                    case sf::Keyboard::W: //Movement
                        //Set that the player is moving
                        player->setMoving(true);
                        break;

                    case sf::Keyboard::D:
                        player->setRotation(45);
                        break;

                    case sf::Keyboard::A:
                        player->setRotation(-45);
                        break;

                    default:
                        break;


                }//End KeyPressed event
                break;


            //Hit close button
            case sf::Event::Closed:

                window->close();
                break;

            //Key released
            case sf::Event::KeyReleased:
                switch(event->key.code){

                    case sf::Keyboard::D:
                        player->setRotation(0);
                        break;

                    case sf::Keyboard::A:
                        player->setRotation(0);
                        break;
                    case sf::Keyboard::W:
                        //Set that the player stop pressing the moving key
                        player->setMoving(false);
                        break;

                }//End KeyReleased event

        }//End switch event type


    }//End events loop


    if(player->getMoving()){
        if(player->getSpeed()<MAXSPEED){
            player->setSpeed(player->getSpeed()+player->getAceleration());

        }

    }else{
        if(player->getSpeed()>0){
            player->setSpeed(player->getSpeed()-player->getAceleration());

        }

    }
    player->run();
}


Game::~Game()
{
    //dtor
}
