#pragma once
#include <vector>
#include "components/simple_scene.h"
#include "../camera.h"

namespace m1
{
    class Meshes : public gfxc::SimpleScene
    {
    public:
        static Mesh *CreateMesh(const char *name, std::string path);
        static void Meshes::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 newColor, implemented::CameraTema 
        *camera, float time, glm::mat4 projectionMatrix);
        static Mesh *CreateMesh(const char* name, std::vector<VertexFormat> vertices, std::vector<unsigned int> indices);
    };
};
