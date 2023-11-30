#pragma once

#include "components/simple_scene.h"
#include "Meshes/Meshes.h"

namespace m1
{
    class Building : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 color = glm::vec3( 146.f/255, 139.f/255, 126.f/255);
    public:
        Building();
        ~Building();
        void createBuilding()
        {
            position = glm::vec3(rand()%100-50, 0, rand()%100-50);
            scale = glm::vec3(rand()%6+7, rand()%6+15, rand()%6+7); // [7-12], [15-20], [7-12]
        }
        glm::vec3 getPosition() const
        {
            return position;
        }
        glm::vec3 getScale() const
        {
            return scale;
        }
        glm::vec3 getColor() const
        {
            return color;
        }
        static Mesh* createMesh()
        {
            std::vector<VertexFormat> vertices{
                VertexFormat (glm::vec3(0, 0, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 0
                VertexFormat (glm::vec3(1, 0, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 1
                VertexFormat (glm::vec3(1, 1, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 2
                VertexFormat (glm::vec3(0, 1, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 3
                VertexFormat (glm::vec3(0, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 4
                VertexFormat (glm::vec3(1, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 5
                VertexFormat (glm::vec3(1, 1, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 6
                VertexFormat (glm::vec3(0, 1, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 7
            };
            std::vector<unsigned int> indices{
                0, 1, 2,
                0, 2, 3,
                1, 2, 5,
                2, 5, 6,
                2, 3, 6,
                3, 6, 7,
                0, 3, 4,
                3, 4, 7,
                4, 5, 6,
                4, 6, 7,
                0, 1, 4,
                1, 4, 5,
            };
            return Meshes::CreateMesh("building", vertices, indices);
        }
    };

    inline Building::Building()
    {
        createBuilding();
    }

    inline Building::~Building()
    {
        createBuilding();
    }
}
