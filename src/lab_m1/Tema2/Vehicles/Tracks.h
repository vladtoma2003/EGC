#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Tracks : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(1, 1, 8);
        // Mesh *tracks = new Mesh("tracks");
    public:
        explicit Tracks(const float x, const float y, const float z)
        {
            position = glm::vec3(x, y, z);
        }
        glm::vec3 getTracksPosition() const
        {
            return position;
        }
        glm::vec3 getTracksSize() const
        {
            return size;
        }
    };
}