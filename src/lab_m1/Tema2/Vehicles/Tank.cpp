#include "Tank.h"

#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/Meshes/Meshes.h"
using namespace m1;

Body* Tank::createBody(float x, float y, float z)
{
    // glm::vec3 center = glm::vec3(x, y, z);
    // std::vector<VertexFormat> vertices
    // {
    //     VertexFormat(center, glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.2, 0.8, 0.2)),
    //     VertexFormat(center + glm::vec3(-1, -1,  1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.2, 0.8, 0.2)),
    //     VertexFormat(center + glm::vec3( 1, -1,  1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.9, 0.4, 0.2)),
    //     VertexFormat(center + glm::vec3(-1,  1,  1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.7, 0.7, 0.1)),
    //     VertexFormat(center + glm::vec3( 1,  1,  1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.7, 0.3, 0.7)),
    //     VertexFormat(center + glm::vec3(-1, -1, -1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.3, 0.5, 0.4)),
    //     VertexFormat(center + glm::vec3( 1, -1, -1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.5, 0.2, 0.9)),
    //     VertexFormat(center + glm::vec3(-1,  1, -1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.7, 0.0, 0.7)),
    //     VertexFormat(center + glm::vec3( 1,  1, -1), glm::vec3(15.f/2555, 39.f/255, 10.f/255), glm::vec3(0.1, 0.5, 0.8)),
    // };
    //
    // std::vector<unsigned int> indices =
    // {
    //     1, 2, 3,       2, 4, 3,
    //     3, 4, 8,       3, 8, 7,
    //     2, 8, 4,       2, 6, 8,
    //     7, 8, 5,       8, 6, 5,
    //     1, 5, 2,       2, 5, 6,
    //     3, 7, 5,       1, 3, 5,
    //     // 0, 1, 2,        1, 3, 2,
    //     // 2, 3, 7,        2, 7, 6,
    //     // 1, 7, 3,        1, 5, 7,
    //     // 6, 7, 4,        7, 5, 4,
    //     // 0, 4, 1,        1, 4, 5,
    //     // 2, 6, 4,        0, 2, 4,
    // };
    //
    components["body"] = Meshes::CreateMesh("body", "src/lab_m1/Tema2/Models/body.obj");
    
    return new Body(x, y, z);
}

void Tank::createTank(float x, float y, float z)
{
    this->body = createBody(x, y, z);
    
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
