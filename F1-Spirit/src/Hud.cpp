#include "Hud.h"

Hud *Hud::unicaInstancia = 0;

Hud::Hud()
{
    sf::Texture* hudTexture = new sf::Texture();
    hudTexture->loadFromFile("Assets/graphics/hud/info f1 spirit.png");
    hud = new sf::Sprite(*hudTexture);

    hud->setOrigin(hud->getTexture()->getSize().x/2.f,hud->getTexture()->getSize().y/2.f);
    hud->setPosition(550,449);
    hud->setScale(1,0.75);

    hudView = new sf::View(sf::FloatRect(400,300,300,300));
    hudView->setViewport(sf::FloatRect(0.5,0.02,0.5,0.95));

    // ===== Initialize velocity text =====
    font = new sf::Font();
    font->loadFromFile("Assets/Fonts/Formula1-Regular.ttf");
    velocityText = new sf::Text();
    velocityText->setFont(*font);
    velocityText->setOrigin(velocityText->getGlobalBounds().width / 2.f, velocityText->getGlobalBounds().height /2.f);
    velocityText->setPosition(520,420);
    velocityText->setColor(sf::Color::White);
    velocityText->setCharacterSize(30);

    // ==== Initialize gear text ====
    gearText = new sf::Text("1",*font);
    gearText->setOrigin(gearText->getGlobalBounds().width / 2.f, gearText->getGlobalBounds().height /2.f);
    gearText->setPosition(625,466);
    gearText->setStyle(sf::Text::Bold);
    gearText->setColor(sf::Color::White);
    gearText->setCharacterSize(20);


    // ==== Initialize lap text ====
    lapText = new sf::Text("Laps left: 5",*font);
    lapText->setOrigin(lapText->getGlobalBounds().width / 2.f, lapText->getGlobalBounds().height /2.f);
    lapText->setPosition(522,417);
    lapText->setStyle(sf::Text::Bold);
    lapText->setColor(sf::Color::White);
    lapText->setCharacterSize(10);

    // ==== Initialize lapTime text ====
    lapTimeText = new sf::Text("0000",*font);
    lapTimeText->setOrigin(lapTimeText->getGlobalBounds().width / 2.f, lapTimeText->getGlobalBounds().height /2.f);
    lapTimeText->setPosition(480,435);
    lapTimeText->setStyle(sf::Text::Bold);
    lapTimeText->setColor(sf::Color::Green);
    lapTimeText->setCharacterSize(12);

    // ==== Initialize GodMode text ====
    godModeText = new sf::Text("",*font);
    godModeText->setOrigin(godModeText->getGlobalBounds().width / 2.f, godModeText->getGlobalBounds().height /2.f);
    godModeText->setPosition(512,397);
    godModeText->setStyle(sf::Text::Bold);
    godModeText->setColor(sf::Color::Red);
    godModeText->setOutlineThickness(3);
    godModeText->setOutlineColor(sf::Color::Yellow);
    godModeText->setCharacterSize(10);

    // ==== Initialize fuel sprites ====
    fuelTexture = new sf::Texture();
    fuelTexture->loadFromFile("Assets/graphics/hud/fuel.png");
    fuelSprite = new sf::Sprite(*fuelTexture);
    fuelSprite->scale(2,1);
    fuelSprite->setColor(sf::Color(255, 0, 0));

    //We want 5 *fuelSprite
    for(int i=0; i<5 ; i++){
       fuelVector.push_back(*fuelSprite);
       if(i==0){
          fuelVector.at(i).setPosition(500,493);
       }else{
          fuelVector.at(i).setPosition(fuelVector.at(0).getPosition().x+30*i, fuelVector.at(0).getPosition().y);
       }

    }


    // ==== Initialize broken sprites ====
    brokenBoxTexture = new sf::Texture();
    brokenBoxTexture->loadFromFile("Assets/graphics/hud/BreakBox.png");
    brokenBoxSprite = new sf::Sprite(*brokenBoxTexture);
    brokenBoxSprite->scale(0,0);


    //We want 4 *fuelSprite
    for(int i=0; i<4 ; i++){
       brokenPieces.push_back(*brokenBoxSprite);
       if(i==0){
          brokenPieces.at(i).setPosition(630,530);
       }else{
          brokenPieces.at(i).setPosition(brokenPieces.at(0).getPosition().x, brokenPieces.at(0).getPosition().y+13.5*i);

       }

    }


}

void Hud::updateVelocityText(float _velocity){

    //We do this because the pointing float precision and sometimes is 0.307 instead of 0.3 :(
    if(_velocity<0) _velocity = 0;

    if(_velocity>=0.3) _velocity = 0.3;

    //We change the color of the sf::Text *velocityText
    if(_velocity >= 0.1f && _velocity <0.2f){
        velocityText->setColor(sf::Color(76, 230, 0));
    }else if(_velocity >= 0.2f && _velocity <= 0.275f){
        velocityText->setStyle(sf::Text::Regular);
        velocityText->setColor(sf::Color(255, 166, 77));
    }else if(_velocity > 0.275f){
        velocityText->setStyle(sf::Text::Bold);
        velocityText->setColor(sf::Color(255, 26, 26));
    }else if(_velocity <0.1f){
        velocityText->setColor(sf::Color::White);
    }

    _velocity *= 1000;
    string velocityString = to_string((int)_velocity);

    velocityText->setString(velocityString);
}

// TODO: adjust to the final numbers
void Hud::updateFuel(float _time){


    if(_time <= 7.f){
        fuelLast = 5;
    }else if( _time >7.f && _time <=14.f){
        fuelLast = 4;
    }else if( _time >14.f && _time <=21.f){
        fuelLast = 3;
    }else if( _time >21.f && _time <=28.f){
        fuelLast = 2;
    }else if(_time >28.f && _time <=35.f){
        fuelLast = 1;
    }else{
        fuelLast = 0;
    }
}

void Hud::updateGear(int _gear){
    gearText->setString(to_string(_gear));

    // ==== Colors :) =====
    if(_gear<4){
        gearText->setColor(sf::Color::White);
    }else if(_gear >=4 && _gear<6){
        gearText->setColor(sf::Color(255, 166, 77));
    }else{
        gearText->setColor(sf::Color(255, 26, 26));
    }
}

void Hud::updatePieceBroken(int _piece){
    brokenPieces.at(_piece).setScale(0.9,0.3);
}

void Hud::repairPieces(){
    for(int i=0; i<brokenPieces.size(); i++){
        brokenPieces.at(i).setScale(0,0);
    }
}

void Hud::updateLap(int _lap){
    string lapString = "Laps left: " + to_string(6-_lap);

    lapText->setString(lapString);
}

void Hud::updateGodMode(bool _godMode){
    if(_godMode){
        godModeText->setString("GOD MODE");
    }else{
        godModeText->setString("");
    }
}

void Hud::updateLapClock(float _time){
    // 1 minute -> 6000
    // 1 minute 30 sec 20ms -> 9020
    //cout << fixed << setprecision(2) << _time << endl;
    lapTimeText->setColor(sf::Color::Green);

    string lapTimeString  = to_string(_time);
    lapTimeText->setString(lapTimeString);
}

void Hud::draw(sf::RenderWindow* _window){
    _window->setView(*hudView);
    // ==== We draw first the image ====
    _window->draw(*hud);

    // ==== We draw now the texts and rectangles ====
    _window->draw(*velocityText);
    _window->draw(*gearText);
    _window->draw(*lapText);
    _window->draw(*lapTimeText);
    _window->draw(*godModeText);

    for(int i=0; i<fuelLast;i++){
        _window->draw(fuelVector.at(i));
    }

    for(int i=0; i<brokenPieces.size();i++){
        _window->draw(brokenPieces.at(i));
    }


}

int Hud::getFuelLast(){return fuelLast;}
sf::Text* Hud::getLapTimeText(){return lapTimeText;}

Hud::~Hud()
{
    //dtor
}
