#include "EnemyCar.h"

EnemyCar::EnemyCar(string path, int carModel, string ia)
{
    texture = new sf::Texture();

    texture->loadFromFile(path,sf::IntRect(32*carModel,0,32,32));
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(16,16); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0

    //Read the IA
    fe.open(ia);
    std::string value;
    std::string delimiter = "-";
    std::string token;
    size_t pos = 0;
    float x,y;
    int cont = 0, angle;

    while(!fe.eof()){
        fe >> value;

        while((pos = value.find(delimiter)) != std::string::npos){
            token = value.substr(0,pos);

            value.erase(0,pos+delimiter.length());
            if(cont==0){
                //X value
                x = ::atof(token.c_str());
            }else if(cont==1){
                y = ::atof(token.c_str());
            }else if(cont==2){
                angle = ::atoi(token.c_str());
            }
            cont++;

        }
        //cout << token << endl;

        Data d;
        d.x = x;
        d.y = y;
        d.angle = angle;
        pathing.push(d);
        cont = 0;

    }

}

void EnemyCar::updatePosition(){

    if(!pathing.empty()){
        float x = pathing.front().x;
        float y = pathing.front().y;
        int angle = pathing.front().angle;

        sprite->setPosition(x,y);
        sprite->setRotation(angle);
        pathing.pop();
    }

}

void EnemyCar::draw(sf::RenderWindow* _window){
    _window->draw(*sprite);
}


sf::Sprite* EnemyCar::getSprite(){return sprite;}

EnemyCar::~EnemyCar()
{
    //dtor
}
