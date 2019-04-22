/*
    NOTES:
    1) Car::getSprite() returns a sf::Sprite* and we storage in sf::Sprites*(carSprites) but on draw function we have to pass her the value (sf::Sprite)
    2) The events loops only executes when an event happens, this is why we have to put the movement system outside the loop
    3) I'll have to make a method that reset the fuelClock when the car reload the fuel
    4) To not show the box for broken pieces I just scale(0,0)

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

    roadTexture = new sf::Texture();
    roadTexture->loadFromFile("Assets/Mapa/f1spiritMap.png");
    roadSprite = new sf::Sprite(*roadTexture);
    roadSprite->scale(0.4,0.4);
    //roadSprite->setPosition(player->getSprite()->getPosition().x-300,player->getSprite()->getPosition().y-2000);
    roadSprite->setPosition(-100,-400);

    /*
    roadSprite2 = new sf::Sprite(*roadTexture);
    roadSprite2->scale(0.4,0.4);
    roadSprite2->setPosition(-110,-2640);


    roadSprite3 = new sf::Sprite(*roadTexture);
    roadSprite3->scale(0.4,0.4);
    roadSprite3->setPosition(-115,-(2640*2)+400);
    */


    grassTexture = new sf::Texture();
    grassTexture->loadFromFile("Assets/Mapa/f1spiritMapCesped.png");
    grassSprite = new sf::Sprite(*grassTexture);
    grassSprite->scale(0.4,0.4);
    //grassSprite->setPosition(player->getSprite()->getPosition().x-300,player->getSprite()->getPosition().y-2000);
    grassSprite->setPosition(-100,-400);


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

    window->draw(*grassSprite);
    window->draw(*roadSprite);
    //window->draw(*roadSprite2);
    //window->draw(*roadSprite3);

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

    Car *player = cars[0];
    while(window->isOpen()){
        deltaTime = deltaClock.restart();

        eventsLoop();

        //We check if the car is at the end of the lap
        if(player->getSprite()->getPosition().y < -300){
            player->getSprite()->setPosition(player->getSprite()->getPosition().x+10,2300);
        }


        // ==== CAR ====
        if(hud->getFuelLast()==0){
            player->setMoving(false);
        }

        player->run(deltaTime.asSeconds()*1000);

        // ==== Update camera position ====
        playerCamera->moveCamera(cars[0]);

        // ==== Update HUD ====
        hud->updateVelocityText(cars[0]->getSpeed());
        hud->updateFuel(cars[0]->getFuelClock().getElapsedTime().asSeconds());
        hud->updateGear(cars[0]->updateGear());
        //==============================================

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

                    case sf::Keyboard::Space: //Movement
                        //Set that the player is moving
                        if(hud->getFuelLast()!=0){
                           player->setMoving(true);
                        }

                        break;

                    case sf::Keyboard::Right:
                        if(rotationKeyUp){
                            rotationKeyUp = false;
                            rotationClock.restart();
                        }

                        if(rotationClock.getElapsedTime().asSeconds()>0.5){
                            player->setRotation(60);
                        }else{
                            player->setRotation(30);
                        }


                        break;

                    case sf::Keyboard::Left:
                        if(rotationKeyUp){
                            rotationKeyUp = false;
                            rotationClock.restart();
                        }

                        if(rotationClock.getElapsedTime().asSeconds()>0.5){
                            player->setRotation(-60);
                        }else{
                            player->setRotation(-30);
                        }
                        break;

                    //TODO just for testing
                    case sf::Keyboard::R:
                        player->reloadFuel();
                        break;

                    //TODO just for testing
                    case sf::Keyboard::Q:
                        hud->updatePieceBroken(player->breakPiece());
                        break;

                    //TODO just for testing
                    case sf::Keyboard::T:
                        player->repairCar();
                        hud->repairPieces();

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

                    case sf::Keyboard::Right:
                        rotationKeyUp = true;
                        rotationClock.restart();
                        break;

                    case sf::Keyboard::Left:
                        rotationKeyUp = true;
                        rotationClock.restart();
                        break;
                    case sf::Keyboard::Space:
                        //Set that the player stop pressing the moving key
                        player->setMoving(false);
                        break;

                }//End KeyReleased event

        }//End switch event type


    }//End events loop

    //Decreasing rotation
    if(rotationKeyUp && rotationClock.getElapsedTime().asSeconds()<0.2){
        if(player->getRotation()==60){
            player->setRotation(30);
        }else if(player->getRotation()==-60){
            player->setRotation(-30);
        }
    }else if(rotationKeyUp && rotationClock.getElapsedTime().asSeconds()>=0.2){
        player->setRotation(0);
    }

}


Game::~Game()
{
    //dtor
}
