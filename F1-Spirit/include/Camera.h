#ifndef CAMERA_H
#define CAMERA_H

#include "Car.h"

class Camera
{
    public:
        Camera();

        void moveCamera(Car*);
        sf::View* getCameraView();
        virtual ~Camera();

    protected:

    private:

        sf::View *cameraView;
        float cameraXSize = 200;
        float cameraYSize = 150;
};

#endif // CAMERA_H
