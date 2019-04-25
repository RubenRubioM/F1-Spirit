#include "Camera.h"

Camera::Camera()
{
    cameraView = new sf::View(sf::FloatRect(0,0,cameraXSize,cameraYSize));
    cameraView->setViewport(sf::FloatRect(0.02,0.02,0.48,0.94));
    cameraView->zoom(2);
}

void Camera::moveCamera(Car* _player){
    cameraView->setCenter(_player->getSprite()->getPosition().x,_player->getSprite()->getPosition().y);
}

sf::View* Camera::getCameraView(){return cameraView;}
Camera::~Camera()
{
    //dtor
}
