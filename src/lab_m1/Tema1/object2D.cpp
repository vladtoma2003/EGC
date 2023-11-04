#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRhombus(
    const std::string &name,
    glm::vec3 leftCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftCorner;
    float center = length / 2;

    std::vector<VertexFormat> vertices =
    {   // center of a rhombus = 1/2*sqrt(l^2/2)
        VertexFormat(corner, color), // left 0
        VertexFormat(corner + glm::vec3(length/2, length, 0), color), // top 1
        VertexFormat(corner + glm::vec3(center + 2*center/3,  length/5, 0), color), // top right 2
        VertexFormat(corner + glm::vec3(center + 2*center/3 + 0.8*length, length/5, 0), color), // most right top 3
        VertexFormat(corner + glm::vec3(length, 0, 0), color), // right 4
        VertexFormat(corner + glm::vec3(center + 2*center/3 + 0.8*length, -length/5, 0), color), // most right bottom 5
        VertexFormat(corner + glm::vec3(center + 2*center/3, -length/5, 0), color), // bottom right 6
        VertexFormat(corner + glm::vec3(length/2, -length, 0), color), // bottom 7
        
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 4,
                                          2, 3, 4,
                                          4, 3, 5,
                                          6, 4, 5,
                                          4, 7, 0};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string &name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;
    float a = 0.4*length;
    float b = 0.2*length;
    float h = sqrt(a*b + 3*b*b/4);
    float h2 = sqrt(a*a - b*b/4);

    // 0.38, 0.24
    // 0.71 down, 0.6 up, 0.34 side, angle = 36 deg
    
    std::vector<VertexFormat> vertices =
    {   // star, length = a + b + a, a = 0.38 length, b = 0.24 length
        VertexFormat(corner, color), // Left 0
        VertexFormat(corner + glm::vec3(length, 0, 0), color), // Right 1
        VertexFormat(corner + glm::vec3(a + b/2, -h, 0), color), // Bottom 2
        VertexFormat(corner + glm::vec3(0.33*a, - h - h2, 0), color), // Bottom left 3
        VertexFormat(corner + glm::vec3(a + b/2, h2, 0), color), // Top 4
        VertexFormat(corner + glm::vec3(a + b + 0.1*a, -2*h/3, 0), color), // Mid Right 5
        VertexFormat(corner + glm::vec3(a + b + 0.66*a, - h - h2, 0), color), // Bottom right 6
        
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          3, 4, 5,
                                         6, 2, 5
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 leftCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // Top Left 0
        VertexFormat(corner + glm::vec3(length/2, 0, 0), color), // Top Right 1
        VertexFormat(corner + glm::vec3(length/2, -length, 0), color), // Bottom Right 2
        VertexFormat(corner + glm::vec3(0, -length, 0), color), // Bottom Left 3
        VertexFormat(corner + glm::vec3(length/2 + length/3, -length/2, 0), color), // Mid right 4
        VertexFormat(corner + glm::vec3(-length/3, -length/2, 0), color) // Mid left 5
        
        
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2,
    1, 4, 2,
    0, 2, 3,
    0, 3, 5};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


