#include "Game.h"
using namespace std;

Game::Game(int x, int y, string title)
{
    window = new sf::RenderWindow(sf::VideoMode(x,y),title);

    texture1 = new sf::Texture();


    texture1->loadFromFile("racing-pack/PNG/Cars/car_black_1.png");
    sprite1 = new sf::Sprite(*texture1);

    //How to change the center point on a sprite
    sprite1->setOrigin((sprite1->getTexture()->getSize().x)/2.f,(sprite1->getTexture()->getSize().y)/2.f);
    sprite1->setPosition(300.f,300.f);
    sprite1->setRotation(90);
    sprite1->setScale(0.5,0.5);

    event = new sf::Event();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();
    window->draw(*sprite1);
    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    while(window->isOpen()){
        eventsLoop();
        sprite1->rotate(1);

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

                    case sf::Keyboard::A:
                        sprite1->move(sprite1->getPosition().x+10, sprite1->getPosition().y+10);


                }//End switch keyPressed

            //Hit close button
            case sf::Event::Closed:
                window->close();

        }//End switch event type

    }
}


Game::~Game()
{
    //dtor
}
