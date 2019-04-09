/*
    NOTES:
    1) Car::getSprite() returns a sf::Sprite* and we storage in sf::Sprites*(carSprites) but on draw function we have to pass her the value (sf::Sprite)
    2) The events loops only executes when an event happens, this is why we have to put the movement system outside the loop
    3) I'll have to make a method that reset the fuelClock when the car reload the fuel

*/
#include "Game.h"

#include <iostream>
#include <math.h>




using namespace std;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();

    Car *player = new Car(0.0001,"Assets/graphics/cars-f1.png",Model1);
    playerCamera = new Camera();

    sf::Texture* bgTexture = new sf::Texture();
    bgTexture->loadFromFile("Assets/fb-og.jpg");
    bg = new sf::Sprite(*bgTexture);

    hud = new Hud();



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



    window->setView(*playerCamera->getCameraView());
    window->draw(*bg);

    //Draw all the cars
    for(unsigned int i=0; i<numCars;i++){
        window->draw(*cars[i]->getSprite());

    }
    hud->draw(window);
    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    sf::Clock deltaClock;
    while(window->isOpen()){
        deltaTime = deltaClock.restart();

        eventsLoop();

        //If the car has fuel, run
        if(hud->getFuelLast()!=0){
           cars[0]->run(deltaTime.asMilliseconds());
        }


        // ==== Update camera position ====
        playerCamera->moveCamera(cars[0]);

        // ==== Update HUD ====
        hud->updateVelocityText(cars[0]->getSpeed());
        hud->updateFuel(cars[0]->getFuelClock().getElapsedTime().asSeconds());

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

                    //TODO just for testing
                    case sf::Keyboard::R:
                        player->reloadFuel();
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



}


Game::~Game()
{
    //dtor
}
