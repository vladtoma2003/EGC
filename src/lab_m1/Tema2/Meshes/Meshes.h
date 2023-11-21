#pragma once
#include <vector>
#include "components/simple_scene.h"

namespace m1
{
    class Meshes : public gfxc::SimpleScene
    {
    public:
        static Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
    };
};
