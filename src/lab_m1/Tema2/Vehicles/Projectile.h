#pragma once
#include <iostream>

#include "components/simple_scene.h"

namespace m1
{
    class Projectile : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 size = glm::vec3(0.2, 0.2, 0.2);
        glm::vec3 forward;
        float speed = 10.f;
        float angle = 0;
        float time = 0;
        bool alive = true;

    public:
        explicit Projectile(const float x, const float y, const float z, glm::vec3 forward, float angle)
        {
            position = glm::vec3(x, y, z);
            this->forward = forward;
            this->angle = angle;
        }
        glm::vec3 getProjectilePosition() const
        {
            return position;
        }
        glm::vec3 getProjectileSize() const
        {
            return size;
        }
        float getProjectileAngle() const
        {
            return angle;
        }
        void moveProjectile(float distance, float time)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir*distance;
            this->time += time;
        }
        float getSpeed() const
        {
            return speed;
        }
        void checkTimeOut()
        {
            if(time > 5)
            {
                alive = false;
            }
        }
        bool isAlive() const
        {
            return alive;
        }
        
    };
}