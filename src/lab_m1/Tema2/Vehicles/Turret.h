#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Turret : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(2, 1, 2.5);
        public:
        explicit Turret(const float x, const float y, const float z)
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
    };
}