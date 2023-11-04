#include "lab_m1/Tema1/tema1.h"

#include <corecrt_wctype.h>
#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* redSquare = object2D::CreateSquare("redSquare", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(redSquare);

    Mesh* outlineSquare = object2D::CreateSquare("outlineSquare", corner, outlineSide, glm::vec3(0, 0, 0));
    AddMeshToList(outlineSquare);

    Mesh* rhombusPink = object2D::CreateRhombus("rhombusPink", corner, rhombusSide, glm::vec3(227.0/255, 115.0/255, 131.0/255), true);
    AddMeshToList(rhombusPink);

    Mesh* rhombusYellow = object2D::CreateRhombus("rhombusYellow", corner, rhombusSide, glm::vec3(247.0/255, 239.0/255, 121.0/255), true);
    AddMeshToList(rhombusYellow);

    Mesh* rhombusPurple = object2D::CreateRhombus("rhombusPurple", corner, rhombusSide, glm::vec3(148.0/255, 0, 211.0/255), true);
    AddMeshToList(rhombusPurple);

    Mesh* rhombusTurquoise = object2D::CreateRhombus("rhombusTurquoise", corner, rhombusSide, glm::vec3(64.0/255, 224.0/255, 208.0/255), true);
    AddMeshToList(rhombusTurquoise);

    Mesh* priceStar = object2D::CreateStar("priceStar", corner, starSize, glm::vec3(1, 1, 0), true);
    AddMeshToList(priceStar);

    Mesh* grass = object2D::CreateSquare("grass", corner, squareSide, glm::vec3(72.0f/255, 254.0f/255, 109.0f/255), true);
    AddMeshToList(grass);

    Mesh* enemyPink = object2D::CreateHexagon("enemyPink", corner, squareSide, glm::vec3(227.0/255, 115.0/255, 131.0/255), true);
    AddMeshToList(enemyPink);

    Mesh* enemyYellow = object2D::CreateHexagon("enemyYellow", corner, squareSide, glm::vec3(247.0/255, 239.0/255, 121.0/255), true);
    AddMeshToList(enemyYellow);
    
    Mesh* enemyPurple = object2D::CreateHexagon("enemyPurple", corner, squareSide, glm::vec3(148.0/255, 0, 211.0/255), true);
    AddMeshToList(enemyPurple);

    Mesh* enemyTurquoise = object2D::CreateHexagon("enemyTurquoise", corner, squareSide, glm::vec3(64.0/255, 224.0/255, 208.0/255), true);
    AddMeshToList(enemyTurquoise);


}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(51.0f/255, 51.0f/255, 51.0f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    
    RenderScene();

    // Render points
    for(int i = 0; i < score; ++i)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(get<0>(starPos) + i*starSize/2, get<1>(starPos));
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
        RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
        
    }
    
    // Test star
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( 600, 500);
    //modelMatrix *= transform2D::Scale(50, 50);
    angularStep += 0.5*deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    // Test hexagon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( 700, 300);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
   // angularStep += 0.5*deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["enemyPink"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( 800, 300);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    //angularStep += 0.5*deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["enemyYellow"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( 900, 300);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    //angularStep += 0.5*deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["enemyPurple"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( 1000, 300);
    modelMatrix *= transform2D::Scale(0.25f, 0.25f);
    //angularStep += 0.5*deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["enemyTurquoise"], shaders["VertexColor"], modelMatrix);
    
    
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if(holdingMouse)
    {
        mouseX = window->GetResolution().x - mouseX;
        mouseY = window->GetResolution().y - mouseY;

        Tema1::mouseX = mouseX;
        Tema1::mouseY = mouseY;
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    holdingMouse = true;
    mouseX = window->GetResolution().x - mouseX;
    mouseY = window->GetResolution().y - mouseY;
    Tema1::mouseX = mouseX;
    Tema1::mouseY = mouseY;
    Tema1::buyX = mouseX;
    Tema1::buyY = mouseY;
    
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    holdingMouse = false;
    Tema1::buyX = 0;
    Tema1::buyY = 0;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::buyRhombus(int x, int y, int score)
{
    while(holdingMouse)
    {
        // Pink rhombus
        if(Tema1::mouseX >= outlinePosx && Tema1::mouseY <= outlinePosx + outlineSide &&
           Tema1::mouseY >= outlinePosy && Tema1::mouseY <= outlinePosy + outlineSide)
        {
            if(score >= 1)
            {
                score -= 1;
                
            }
        }
    }
}


void Tema1::RenderScene()
{
    // Render the "Base" line
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life, life);
    modelMatrix *= transform2D::Scale(0.5, 3 + 2*space/squareSide);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    
    // Render rombus shop
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombusPink"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + outlineSide + space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombusTurquoise"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + 2*outlineSide + 2*space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombusYellow"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + 3*outlineSide + 3*space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombusPurple"], shaders["VertexColor"], modelMatrix);
    
    // Row 1 of the board - formula: life + squareSide - squareSide/2 = pornesc de la viata, adaug un patrat si tai
    // jumate(bara de final este jumatate de patrat pe ox) si apoi adaug spatiul dintre patrate
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + squareSide - squareSide/2 + space, life);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 2*squareSide - squareSide/2 + 2*space, life);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 3*squareSide - squareSide/2 + 3*space, life);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    
    // Row 2 of the board
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + squareSide - squareSide/2 + space, life + squareSide + space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 2*squareSide - squareSide/2 + 2*space, life + squareSide + space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 3*squareSide - squareSide/2 + 3*space, life + squareSide + space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    
    // Row 3 of the board
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + squareSide - squareSide/2 + space, life + 2*squareSide + 2*space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 2*squareSide - squareSide/2 + 2*space, life + 2*squareSide + 2*space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life + 3*squareSide - squareSide/2 + 3*space, life + 2*squareSide + 2*space);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    
    // Rhombus Shop
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( outlinePosx, outlinePosy);
    RenderMesh2D(meshes["outlineSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( outlinePosx + outlineSide + space, outlinePosy);
    RenderMesh2D(meshes["outlineSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( outlinePosx + 2*outlineSide + 2*space, outlinePosy);
    RenderMesh2D(meshes["outlineSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate( outlinePosx + 3*outlineSide + 3*space, outlinePosy);
    RenderMesh2D(meshes["outlineSquare"], shaders["VertexColor"], modelMatrix);

    
    // Render the lives - posibil sa le schimb sa arate ca niste inimi
    for(int i = 0; i < noLives; ++i) // render the no of lives
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate( lifeX  + i*(0.75*squareSide + space),  lifeY);
        modelMatrix *= transform2D::Scale(0.75, 0.75);
        RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);
    }


    // Render the price stars
    // Pink rhombus, 1 star
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + outlineSide/2, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    // Turquoise rhombus, 2 stars
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + space + 1.5f*outlineSide - 0.3f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + space + 1.5f*outlineSide + 0.3f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    // Yellow rhombus, 2 stars
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*space + 2.5f*outlineSide - 0.3f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*space + 2.5f*outlineSide + 0.3f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
    
    // Purple rhombus, 3 stars
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 3*space + 3.5f*outlineSide - 0.5f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 3*space + 3.5f*outlineSide, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 3*space + 3.5f*outlineSide + 0.5f*starSize, outlinePosy-starSize/3);
    modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
}