#pragma once
#include <vector>
#include "components/simple_scene.h"

namespace m1
{
    class Meshes : public gfxc::SimpleScene
    {
    public:
        static Mesh *CreateMesh(const char *name, std::string path);
        // static void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 newColor); 
    };
};
