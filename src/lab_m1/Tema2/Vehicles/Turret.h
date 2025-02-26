﻿#pragma once
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
        float turretAngle = 0;
        float deltaX = 0;
        glm::vec2 deformationDirection;
        public:
        explicit Turret(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
            deformationDirection = glm::vec2(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
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
        float getTurretAngle() const
        {
            return turretAngle;
        }
        void moveTurret(glm::vec3 distance)
        {
            position += distance;
            center += distance;
        }
        void updateTurretPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            center.x = x;
            center.y = y;
            center.z = z;
            turretAngle = 0;
        }
        void rotateTurret(float angle)
        {
            turretAngle += angle;
            position.x = center.x + distanceFromBody.x * cos(-turretAngle);
            position.z = center.z + distanceFromBody.z * sin(-turretAngle);
        }
        float getDeltaX() const
        {
            return deltaX;
        }
        void setDeltaX(float value)
        {
            deltaX = value;
        }
        void incDeltaX(float value)
        {
            deltaX += value;
        }
        glm::vec2 getDeformationDirection() const
        {
            return deformationDirection;
        }
    };
}