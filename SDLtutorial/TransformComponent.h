#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL.h>
#include "EntityManager.h"
#include "Constants.h"
#include "Game.h"

class TransformComponent : public Component {
public:
    vf2d position;
    vf2d velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
        position = vf2d(posX, posY);
        velocity = vf2d(velX, velY);
        width = w;
        height = h;
        scale = s;
    }

    void Initialize() override {

    }

    void Update(float deltaTime) override {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }
};

#endif