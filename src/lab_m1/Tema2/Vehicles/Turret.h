#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Turret : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(3, 1.5, 3.5);
        glm::vec3 distanceFromBody;
        glm::vec3 center;
        public:
        explicit Turret(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
        }
        void setTurretPosition(float x, float y, float z)
        {
            position = glm::vec3(x, y, z);
        }
        glm::vec3 getTurretPosition() const
        {
            return position;
        }
        glm::vec3 getTurretSize() const
        {
            return size;
        }
        void moveTurret(float x, float y, float z)
        {
            position.x += x;
            position.y += y;
            position.z += z;
            center.x += x;
            center.y += y;
            center.z += z;
        }
        void updateTurretPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            center.x = x;
            center.y = y;
            center.z = z;
        }
        void rotateTurret(Tank *tank, float angle)
        {
            position.x = center.x + distanceFromBody.x * cos(angle);
            position.z = center.z + distanceFromBody.z * sin(angle);
            
        }
        void rotateTurret(float angle)
        {
            position.x = center.x + distanceFromBody.x * cos(-angle);
            position.z = center.z + distanceFromBody.z * sin(-angle);
        }
    };
}