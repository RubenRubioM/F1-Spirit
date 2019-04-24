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

    // ==== MAP ====
    roadTexture = new sf::Texture();
    roadTexture->loadFromFile("Assets/Mapa/f1spiritMap.png");
    roadSprite = new sf::Sprite(*roadTexture);
    roadSprite->scale(0.4,0.4);
    roadSprite->setPosition(-100,-400);

    treesTexture = new sf::Texture();
    treesTexture->loadFromFile("Assets/Mapa/Arboles.png");
    treesLeft = new sf::Sprite(*treesTexture);
    treesLeft->scale(0.4,0.4);
    treesLeft->setPosition(0,0);

    treesRight = new sf::Sprite(*treesTexture);
    treesRight->scale(0.4,0.4);
    treesRight->setPosition(670,0);

    pitLaneTexture = new sf::Texture();
    pitLaneTexture->loadFromFile("Assets/PitLane.png");
    pitLaneSprite = new sf::Sprite(*pitLaneTexture);
    pitLaneSprite->setOrigin(pitLaneTexture->getSize().x,pitLaneTexture->getSize().y);
    pitLaneSprite->setScale(0.4,0.4);
    pitLaneSprite->setPosition(220,2200);

    // ==== MINIMAP ====
    minimap = new sf::View(sf::FloatRect(0,-170,2300,2500));
    minimap->setViewport(sf::FloatRect(0.553f,0.04f,1.f,0.27f));

    playerCircle.setRadius(25);
    playerCircle.setOrigin(playerCircle.getRadius(),playerCircle.getRadius());
    playerCircle.setFillColor(sf::Color::Blue);
    playerCircle.setOutlineThickness(10);
    playerCircle.setOutlineColor(sf::Color::Red);

    // ==== TEXT ====
    font = new sf::Font();
    font->loadFromFile("Assets/Fonts/Formula1-Regular.ttf");
    lapTimeText = new sf::Text();
    lapTimeText->setFont(*font);
    lapTimeText->setOrigin(lapTimeText->getGlobalBounds().width / 2.f, lapTimeText->getGlobalBounds().height /2.f);
    lapTimeText->setPosition(220,2000);
    lapTimeText->setColor(sf::Color::White);
    lapTimeText->setCharacterSize(30);

    hud = Hud::getInstance();

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

    for(int j=0; j<2; j++){
        if(j==0){
            //We draw the map
            window->setView(*playerCamera->getCameraView());

            window->draw(*roadSprite);
            window->draw(*treesLeft);
            window->draw(*treesRight);
            window->draw(*pitLaneSprite);


            //Draw all the cars
            for(unsigned int i=0; i<numCars;i++){
                window->draw(*cars[i]->getSprite());

            }
            hud->draw(window);
        }else{
            //We draw the minimap
            window->setView(*minimap);

            window->draw(*roadSprite);
            window->draw(*treesLeft);
            window->draw(*treesRight);

            //Draw all the cars
            for(unsigned int i=0; i<numCars;i++){
                window->draw(*cars[i]->getSprite());

            }
            window->draw(playerCircle);
        }
    }





    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    sf::Clock deltaClock;

    Car *player = cars[0];

    lapClock.restart();
    while(window->isOpen()){
        deltaTime = deltaClock.restart();

        eventsLoop();



        //Colision
        if(player->getGodMode()==false){
            if(treesLeft->getGlobalBounds().intersects(player->getSprite()->getGlobalBounds()) || treesRight->getGlobalBounds().intersects(player->getSprite()->getGlobalBounds())){
                player->setColisionando(true);
            }
        }


        if(player->getColisionando()){
            player->colision();
        }

        //Colision with pitlane
        if(numLap!=1 && player->getSpeed()<0.25f && !player->getPitLane() && pitLaneCD.getElapsedTime().asSeconds()>5.f){
            if(pitLaneSprite->getGlobalBounds().intersects(player->getSprite()->getGlobalBounds())){
                cout << "PitLane" << endl;
                player->setPitLane(true);
                pitLaneClock.restart();
                playerCamera->getCameraView()->zoom(0.5);
            }
        }



        //We check if the car is at the end of the lap
        if(player->getSprite()->getPosition().y < -300){
            player->getSprite()->setPosition(player->getSprite()->getPosition().x+10,2300);
            cout << to_string(lapClock.getElapsedTime().asSeconds()) << endl;
            numLap++;
            lapTimeText->setString(to_string(lapClock.getElapsedTime().asSeconds()));
            lapTimeClock.restart();
            lapClock.restart();
            hud->updateLap(numLap);
        }


        // ==== CAR ====
        if(hud->getFuelLast()==0){
            player->setMoving(false);
        }

        if(!player->getPitLane()){
            player->run(deltaTime.asSeconds()*1000);
        }else{
            //Enters pitLane

            player->repairCar();
            hud->repairPieces();
            player->reloadFuel();
            if(pitLaneClock.getElapsedTime().asSeconds()>5.f){
                player->setPitLane(false);
                pitLaneCD.restart();
                player->setSpeed(0);
                playerCamera->getCameraView()->zoom(2);
                cout << "Ya puedes retomar la carrera" << endl;
            }
        }

        playerCircle.setPosition(player->getSprite()->getPosition());

        // ==== Update camera position ====
        playerCamera->moveCamera(cars[0]);

        // ==== Update HUD ====
        hud->updateVelocityText(cars[0]->getSpeed());

        if(player->getGodMode()==false){
          hud->updateFuel(cars[0]->getFuelClock().getElapsedTime().asSeconds());
        }

        hud->updateGear(cars[0]->updateGear());

        if(lapTimeClock.getElapsedTime().asSeconds()>5.f || numLap==1){
           hud->updateLapClock(lapClock.getElapsedTime().asSeconds());

        }else{
            hud->getLapTimeText()->setColor(sf::Color::Yellow);
        }

        if(numLap==6){
            raceFinished = true;
            player->setMoving(false);
        }

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
                        break;

                    case sf::Keyboard::G:
                        player->switchGodMode();

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
