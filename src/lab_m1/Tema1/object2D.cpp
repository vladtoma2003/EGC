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

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 4,
                                          2, 3, 4,
                                          4, 3, 5,
                                          6, 4, 5,
                                          4, 7, 0};

    if (!fill) {
        rhombus->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}
/* @brief Creates a star. The star is made out of 3 triangles. The points are on a big circle and a small circle.
 * The radius of the small circle is 0.4 times the radius of the big circle. The only point on the small circle is 2.
 * The 0 is in center. The points are equally distanced by dividing the circle in 10 equal parts(10 because a 5 pointed
 * star has 10 points including the ones inside).
*/
Mesh* object2D::CreateStar(
    const std::string &name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    constexpr float angle = 2*glm::pi<float>()/10;
    constexpr float outerRadius = 25.0f;
    
    const std::vector<VertexFormat> vertices =
    {  
        VertexFormat(center, color), // Center 0
        VertexFormat(center + glm::vec3(outerRadius, 0, 2), color), // 1
        VertexFormat(center + glm::vec3(0.4*outerRadius*cos(angle), 0.4*outerRadius*sin(angle), 2), color), // 2
        VertexFormat(center + glm::vec3(outerRadius*cos(angle*2), outerRadius*sin(angle*2), 2), color), // 3
        VertexFormat(center + glm::vec3(outerRadius*cos(angle*4), outerRadius*sin(angle*4), 2), color), // 4
        VertexFormat(center + glm::vec3(outerRadius*cos(angle*6), outerRadius*sin(angle*6), 2), color), // 5
        VertexFormat(center + glm::vec3(outerRadius*cos(angle*8), outerRadius*sin(angle*8), 2), color), // 6
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {
        5, 1, 2,
        6, 4, 2,
        3, 5, 2
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 leftCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 middle = leftCorner;
    double h = sqrt(3)*length/2;
    
    float outline = length/3;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(middle, color), // Middle 0
        VertexFormat(middle + glm::vec3(length, 0, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Right 1
        VertexFormat(middle + glm::vec3(length/2, h, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Top right 2
        VertexFormat(middle + glm::vec3(-length/2, h, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Top left 3
        VertexFormat(middle + glm::vec3(-length, 0, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Left 4
        VertexFormat(middle + glm::vec3(-length/2, -h, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Bottom left 5
        VertexFormat(middle + glm::vec3(length/2, -h, 1), glm::vec3(128.0/255,128.0/255,128.0/255)), // Bottom right 6
        VertexFormat(middle + glm::vec3(1.5*length, 0, 0), color), // Outline right 7
        VertexFormat(middle + glm::vec3(1.5*length/2, 1.5*h, 0), color), // Outline top right 8
        VertexFormat(middle + glm::vec3(-1.5*length/2, 1.5*h, 0), color), // Outline top left 9
        VertexFormat(middle + glm::vec3(-1.5*length, 0, 0), color), // Outline left 10
        VertexFormat(middle + glm::vec3(-1.5*length/2, -1.5*h, 0), color), // Outline bottom left 11
        VertexFormat(middle + glm::vec3(1.5*length/2, -1.5*h, 0), color), // Outline bottom right 12
        VertexFormat(middle + glm::vec3(0, 0, 1), glm::vec3(128.0/255,128.0/255,128.0/255)) // Top 13
        
    };

    Mesh* hexa = new Mesh(name);
    std::vector<unsigned int> indices = {
        // 13, 2, 1,
        // 13, 3, 2,
        // 13, 4, 3,
        // 13, 5, 4,
        // 13, 6, 5,
        // 13, 1, 6,
        // 0, 8, 7,
        // 0, 9, 8,
        // 0, 10, 9,
        // 0, 11, 10,
        // 0, 12, 11,
        // 0, 7, 12
        1, 6, 5,
        1, 5, 2,
        2, 5, 3,
        3, 5, 4,
        7, 12, 11,
        7, 11, 8,
        8, 11, 9,
        9, 11, 10
    };

    if (!fill) {
        hexa->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    hexa->InitFromData(vertices, indices);
    return hexa;
}


