#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

class BallObject : public GameObject{
    public:
        // ball state
        float Radius;
        bool Stuck;

        // constructor
        BallObject();
        BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

        // moves ball keeping it constrained within the window bounds (except bottom edge)
        glm::vec2 Move(float dt, unsigned int window_width);

        // resets the ball to original stae with the givne pos and velocity
        void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif