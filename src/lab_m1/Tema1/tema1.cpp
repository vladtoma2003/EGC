#include "lab_m1/Tema1/tema1.h"

#include <complex>
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

    Mesh* rhombusPink = object2D::CreateRhombus("rhombus1", corner, rhombusSide, glm::vec3(227.0/255, 115.0/255, 131.0/255), true);
    AddMeshToList(rhombusPink);

    Mesh* rhombusYellow = object2D::CreateRhombus("rhombus2", corner, rhombusSide, glm::vec3(247.0/255, 239.0/255, 121.0/255), true);
    AddMeshToList(rhombusYellow);

    Mesh* rhombusPurple = object2D::CreateRhombus("rhombus3", corner, rhombusSide, glm::vec3(148.0/255, 0, 211.0/255), true);
    AddMeshToList(rhombusPurple);

    Mesh* rhombusTurquoise = object2D::CreateRhombus("rhombus4", corner, rhombusSide, glm::vec3(64.0/255, 224.0/255, 208.0/255), true);
    AddMeshToList(rhombusTurquoise);

    Mesh* priceStar = object2D::CreateStar("priceStar", corner, starSize, glm::vec3(1, 1, 0), true);
    AddMeshToList(priceStar);

    Mesh* grass = object2D::CreateSquare("grass", corner, squareSide, glm::vec3(72.0f/255, 254.0f/255, 109.0f/255), true);
    AddMeshToList(grass);

    Mesh* enemyPink = object2D::CreateHexagon("enemy1", corner, squareSide, glm::vec3(227.0/255, 115.0/255, 131.0/255), true);
    AddMeshToList(enemyPink);

    Mesh* enemyYellow = object2D::CreateHexagon("enemy2", corner, squareSide, glm::vec3(247.0/255, 239.0/255, 121.0/255), true);
    AddMeshToList(enemyYellow);
    
    Mesh* enemyPurple = object2D::CreateHexagon("enemy3", corner, squareSide, glm::vec3(148.0/255, 0, 211.0/255), true);
    AddMeshToList(enemyPurple);

    Mesh* enemyTurquoise = object2D::CreateHexagon("enemy4", corner, squareSide, glm::vec3(64.0/255, 224.0/255, 208.0/255), true);
    AddMeshToList(enemyTurquoise);

    Mesh* pinkStar = object2D::CreateStar("star1", corner, starSize, glm::vec3(227.0/255, 115.0/255, 131.0/255), true);
    AddMeshToList(pinkStar);

    Mesh* yellowStar = object2D::CreateStar("star2", corner, starSize, glm::vec3(247.0/255, 239.0/255, 121.0/255), true);
    AddMeshToList(yellowStar);

    Mesh* purpleStar = object2D::CreateStar("star3", corner, starSize, glm::vec3(148.0/255, 0, 211.0/255), true);
    AddMeshToList(purpleStar);

    Mesh* turquoiseStar = object2D::CreateStar("star4", corner, starSize, glm::vec3(64.0/255, 224.0/255, 208.0/255), true);
    AddMeshToList(turquoiseStar);

    Mesh* collectStars = object2D::CreateStar("collectStars", corner, starSize, glm::vec3(1, 0, 1), true);
    AddMeshToList(collectStars);
    
}

void Tema1::CheckGameOver()
{
    if(noLives <= 0)
    {
        exit(0);
    }
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
    CheckGameOver();
    
    DetectCollision();
    
    buyRhombus(Tema1::mouseX, Tema1::mouseY, Tema1::buyX, Tema1::buyY);

    ShootStars(deltaTimeSeconds);
    
    SpawnStars(deltaTimeSeconds);

    moveStars(deltaTimeSeconds);


    DestroyEnemies();
    
    RenderScene(deltaTimeSeconds);

    SpawnEnemies(deltaTimeSeconds);
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
    if(key == GLFW_KEY_L)
    {
        noLives = 500;
    }
    if(key == GLFW_KEY_P)
    {
        score = 500;
    }
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
        mouseX = mouseX;
        mouseY = window->GetResolution().y - mouseY;

        
        Tema1::mouseX = mouseX;
        Tema1::mouseY = mouseY;
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    holdingMouse = true;
    mouseX = mouseX;
    mouseY = window->GetResolution().y - mouseY;
    Tema1::mouseX = mouseX;
    Tema1::mouseY = mouseY;
    Tema1::buyX = mouseX;
    Tema1::buyY = mouseY;
    std::cout << mouseX << " " << mouseY << "\n";
    std::cout << "RESOLUTION" << endl;
    std::cout << window->GetResolution().x << " " << window->GetResolution().y << "\n";
    if(button == 2)
    {
        DestroyRhombus(mouseX, mouseY);
    }
    if(!stars.empty())
        CollectStars();
    
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    holdingMouse = false;
    Tema1::buyX = 0;
    Tema1::buyY = 0;
    Tema1::releaseX = mouseX;
    Tema1::releaseY = mouseY;
    // holdingRhombus = false;

}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::buyRhombus(int x, int y, int buyX, int buyY){
    RenderHoldingRhombus(x, y, buyX, buyY);
    PlaceRhombus(mouseX, mouseY);
}

void Tema1::PlaceRhombus(int x, int y)
{
    if(!holdingMouse && holdingRhombus)
    { // life + (j+0.5)*squareSide + (j+1)*space, life + i*squareSide + i*space
        for(int i = 0; i < 9; ++i)
        {
            if(x >= life + (i%3 + 0.5) * squareSide + (i%3 + 1) * space && x <= life + (i%3 + 1.5) * squareSide + (i%3 + 1) * space &&
               y >= life + (i/3) * squareSide + (i/3) * space && y <= life + (i/3 + 1) * squareSide + (i/3) * space &&
               get<0>(board[i]) == 0 && price <= score)
            {
                get<0>(board[i]) = currentColor;
                get<1>(board[i]) = 1;
                score -= price;
                holdingRhombus = false;
                price = 0;
            }
        }
    }
}

void Tema1::DestroyRhombus(int x, int y)
{
    for(int i = 0; i < 9; ++i)
    {
        if(x >= life + (i%3 + 0.5)*(squareSide + space) && x <= life + (i%3 + 1.5)*(squareSide + space) &&
           y >= life + (i/3)*(squareSide + space) && y <= life + (i/3 + 1)*(squareSide + space) &&
           get<0>(board[i]) != 0)
        {
            get<2>(board[i]) = true;
        }
    }
}

void Tema1::ShootStars(float deltaTime)
{
    for(int i = 0; i < 9; ++i)
    {
        // ma plimb prin board
        if(get<0>(board[i]) == 0 || get<2>(board[i]) == true)
        {
            continue;
        }
        get<3>(board[i]) += deltaTime;
        if((int)get<3>(board[i]) % 3 == 0)
        {
            get<3>(board[i]) += 0.5;
            if(checkEnemysRow(i/3, get<0>(board[i]), enemies))
            {
                projectiles.push_back(std::make_tuple(life + (i%3 + 0.5)*(squareSide+space) + 0.5*squareSide,
                    life + (i/3)*(squareSide+space) + 0.5*squareSide, get<0>(board[i]), 0, true));
            }
            
        }
    }
}
/* @param row - the row of the board that is being checked
 * @param color - the color of the rhombus that is being checked
 * @param enemies - the vector of enemies that is being checked
 */
bool Tema1::checkEnemysRow(int row, int color, std::vector<std::tuple<float, float, int, int, float, bool>> enemies)
{
    for(auto enemy : enemies)
    {
        if((int) get<1>(enemy) == (int)(life + row*squareSide + row*space + 0.5*squareSide) && get<2>(enemy) == color)
        {
            return true;
        }
    }
    return false;
}


void Tema1::SpawnEnemies(float deltaTime)
{
    timeElapsed2 += deltaTime;
    if((int)timeElapsed2 % 9 == 0 || enemies.empty())
    {
        int noEnemies = rand()%3 + 1;
        timeElapsed2 += 1;
        for(int i = 0; i < noEnemies; ++i)
        {
            int line = rand() % 3;
            int color = rand() % 4 + 1;
            int hp = 6;
            enemies.push_back(std::make_tuple(window->GetResolution().x + i*squareSide + i*space,
                life + line*squareSide + line*space + 0.5*squareSide, color, hp, 0.25, false));
        }
    }
}

void Tema1::DetectCollision()
{
    for(int i = 0; i < enemies.size(); ++i)
    {
        for(int j = 0; j < projectiles.size(); ++j)
        {
            if(!get<4>(projectiles[j])) continue;
            if(get<0>(projectiles[j]) >= get<0>(enemies[i]) - 0.5*squareSide && get<0>(projectiles[j]) <= get<0>(enemies[i]) + 0.5*squareSide &&
                (int)get<1>(projectiles[j]) == (int)get<1>(enemies[i]) &&
               get<2>(projectiles[j]) == get<2>(enemies[i]) && get<4>(projectiles[j]) == true && !get<5>(enemies[i]))
            {
                --get<3>(enemies[i]);
                get<4>(projectiles[j]) = false;
            }
        }
        DestroyProjectiles();
        for(int j = 0; j < 9; ++j)
        {
            if(get<0>(board[j]) == 0) continue;
            if(get<0>(enemies[i]) - rhombusSide/2 <= life + (j%3 + 0.5)*(squareSide + space) + 1.1*squareSide &&
                get<0>(enemies[i]) - rhombusSide/2 >= life + (j%3 - 0.5)*(squareSide + space) + 1.1*squareSide &&
               (int)get<1>(enemies[i]) == (int)(life + (j/3)*(squareSide + space) + 0.5*squareSide) &&
               !get<5>(enemies[i]))
            {
                get<2>(board[j]) = true;
            }
        }
    }
}



void Tema1::DestroyEnemies()
{
    if(enemies.empty() == false)
        for(int i = 0; i < enemies.size(); ++i)
        {
            if(get<5>(enemies[i])) continue;
            if(get<0>(enemies[i]) <= life + 0.25*squareSide)
            {
                get<5>(enemies[i]) = true;
                --noLives;
            }
            if(get<3>(enemies[i]) <= 0)
            {
                get<5>(enemies[i]) = true;
            }
        }
}


void Tema1::DestroyProjectiles()
{
    if(projectiles.empty() == false)
        for(int i = 0; i < projectiles.size(); ++i)
        {
            if(get<0>(projectiles[i]) >= window->GetResolution().x || get<4>(projectiles[i]) == false)
            {
                projectiles.erase(projectiles.begin() + i);
            }
        }
}


void Tema1::SpawnStars(float time)
{
    timeElapsed += time;
    if(((int)timeElapsed % 5 == 0 || timeElapsed < 2*time) && stars.size() < 10)
    {
        timeElapsed += 0.5;
        int noOfStars = rand() % 3 + 1;
        for(int i = 0; i < noOfStars; ++i)
        {
            int x = rand() % (int)(window->GetResolution().x - 4*squareSide + 3*space - starSize);
            int y = rand() % (int)(window->GetResolution().y - starSize - 2*squareSide - 2*space);

            x = x + 4*squareSide + 3*space - 2*starSize;
            y = window->GetResolution().y - y - starSize - 2*squareSide;

            int spawnX = (rand()%2 == 0)? (x+window->GetResolution().x/2):(x-window->GetResolution().x);
            int spawnY = y + window->GetResolution().y;
            
            stars.push_back(std::make_tuple(x, y, spawnX, spawnY));
        }
    }
}

void Tema1::moveStars(float deltaTime)
{
    // std::cout << "move\n";
    for(int i = 0; i < stars.size(); ++i)
    {
        if(abs(get<0>(stars[i]) - get<2>(stars[i])) > 0.1 && get<1>(stars[i]) < get<3>(stars[i]))
        {
            get<3>(stars[i]) -= 50.0f*deltaTime;
            get<2>(stars[i]) = (get<2>(stars[i]) > get<0>(stars[i]))?
                get<2>(stars[i]) - 50.0f*deltaTime : get<2>(stars[i]) + 50.0f*deltaTime;
        } else if (abs(get<0>(stars[i]) - get<2>(stars[i])) > 0.1)
        {
            get<2>(stars[i]) = (get<2>(stars[i]) > get<0>(stars[i]))?
                get<2>(stars[i]) - 50.0f*deltaTime : get<2>(stars[i]) + 50.0f*deltaTime;
        } else if (get<1>(stars[i]) < get<3>(stars[i]))
        {
            get<3>(stars[i]) -= 50.0f*deltaTime;
        } else
        {
            get<3>(stars[i]) = get<1>(stars[i]);
            get<2>(stars[i]) = get<0>(stars[i]);
        }
    }
}


void Tema1::CollectStars()
{
    for(int i = 0; i < stars.size(); ++i)
    {
        if(Tema1::mouseX >= get<0>(stars[i]) - starSize/2 && Tema1::mouseX <= get<0>(stars[i]) + starSize/2 &&
           Tema1::mouseY >= get<1>(stars[i]) - starSize/2 && Tema1::mouseY <= get<1>(stars[i]) + starSize/2)
        {
            stars.erase(stars.begin() + i);
            Tema1::score += 1;
        }
    }
}

void Tema1::RenderHoldingRhombus(int x, int y, int buyX, int buyY)
{
    //Render the rhombus that is being held
    if(holdingMouse)
    {
        // Pink rhombus
        if(buyX >= outlinePosx && buyX <= outlinePosx + outlineSide &&
           buyY >= outlinePosy && buyY <= outlinePosy + outlineSide)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x - 2*rhombusSide/3, y);
            RenderMesh2D(meshes["rhombus1"], shaders["VertexColor"], modelMatrix);
            holdingRhombus = true;
            currentColor = 1;
            price = 1;
        } else if(buyX >= outlinePosx + outlineSide + space && buyX <= outlinePosx + 2*outlineSide + space &&
           buyY >= outlinePosy && buyY <= outlinePosy + outlineSide) // Turquoise rhombus
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x - 2*rhombusSide/3, y);
            RenderMesh2D(meshes["rhombus2"], shaders["VertexColor"], modelMatrix);
            holdingRhombus = true;
            currentColor = 2;
            price = 2;
        }  else if(buyX >= outlinePosx + 2*outlineSide + 2*space && buyX <= outlinePosx + 3*outlineSide + 2*space &&
           buyY >= outlinePosy && buyY <= outlinePosy + outlineSide)  // Yellow rhombus
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x - 2*rhombusSide/3, y);
            RenderMesh2D(meshes["rhombus3"], shaders["VertexColor"], modelMatrix);
            holdingRhombus = true;
            currentColor = 3;
            price = 2;
        } else if(buyX >= outlinePosx + 3*outlineSide + 3*space && buyX <= outlinePosx + 4*outlineSide + 3*space &&
           buyY >= outlinePosy && buyY <= outlinePosy + outlineSide)  // Purple rhombus
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(x - 2*rhombusSide/3, y);
            RenderMesh2D(meshes["rhombus4"], shaders["VertexColor"], modelMatrix);
            holdingRhombus = true;
            currentColor = 4;
            price = 3;
        } else
        {
            holdingRhombus = false;
        }
    }
}

void Tema1::RenderScene(float deltaTime)
{

    // Render the stars that can be collected
    if(stars.empty() == false)
    {
        for(int i = 0; i < stars.size(); ++i)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(get<2>(stars[i]), get<3>(stars[i]));
            modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
            RenderMesh2D(meshes["collectStars"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Render projectiles
    if(projectiles.empty() == false)
    {
        for(int i = 0; i < projectiles.size(); ++i)
        {
            modelMatrix = glm::mat3(1);
            get<0>(projectiles[i]) += 200*deltaTime;
            modelMatrix *= transform2D::Translate(get<0>(projectiles[i]), get<1>(projectiles[i]));
            get<3>(projectiles[i]) += -1*deltaTime;
            modelMatrix *= transform2D::Rotate(get<3>(projectiles[i]));
            // modelMatrix *= transform2D::Scale(0.25, 0.25);
            RenderMesh2D(meshes["star"+std::to_string(get<2>(projectiles[i]))], shaders["VertexColor"], modelMatrix);
            // projectiles.erase(projectiles.begin() + i);
        }
    }

    
    // Render enemies
    if(enemies.empty() == false)
    {
        for(int i = 0; i < enemies.size(); ++i)
        {
            if(!get<5>(enemies[i]))
            {
                modelMatrix = glm::mat3(1);
                get<0>(enemies[i]) -= 100*deltaTime;
                modelMatrix *= transform2D::Translate(get<0>(enemies[i]), get<1>(enemies[i]));
                modelMatrix *= transform2D::Scale(0.25, 0.25);
                RenderMesh2D(meshes["enemy" + std::to_string(get<2>(enemies[i]))], shaders["VertexColor"], modelMatrix);
            } else
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(get<0>(enemies[i]), get<1>(enemies[i]));
                get<4>(enemies[i]) -= 0.3*deltaTime;
                modelMatrix *= transform2D::Scale(get<4>(enemies[i]), get<4>(enemies[i]));
                RenderMesh2D(meshes["enemy" + std::to_string(get<2>(enemies[i]))], shaders["VertexColor"], modelMatrix);
                if(get<4>(enemies[i]) <= 0)
                {
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
    
    // Render the "Base" line
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(life, life);
    modelMatrix *= transform2D::Scale(0.5, 3 + 2*space/squareSide);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    //formula: life + squareSide - squareSide/2 = pornesc de la viata, adaug un patrat si tai
    // jumate(bara de final este jumatate de patrat pe ox) si apoi adaug spatiul dintre patrate
    for(int i = 0; i < 9; ++i)
    {
        if(std::get<0>(board[i]) != 0)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(life + (i%3+0.5)*squareSide + (i%3+1)*space + 0.5*rhombusSide,
                life + (i/3)*squareSide + (i/3)*space + 1.2*rhombusSide);
            modelMatrix *= transform2D::Scale(std::get<1>(board[i]), std::get<1>(board[i]));
            RenderMesh2D(meshes["rhombus" + std::to_string(std::get<0>(board[i]))], shaders["VertexColor"], modelMatrix);
        }
        if(std::get<2>(board[i]))
        {
            std::get<1>(board[i]) -= 0.75*deltaTime;
            if(std::get<1>(board[i]) <= 0)
            {
                std::get<0>(board[i]) = 0;
                std::get<1>(board[i]) = 0;
                std::get<2>(board[i]) = false;
                std::get<3>(board[i]) = 0;
            }
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(life + (i%3+0.5)*squareSide + (i%3+1)*space, life + (i/3)*squareSide + (i/3)*space);
        RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
    }

    // Outline of rhombus shop
    for(int i = 0; i < 4; ++i)
    {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate( outlinePosx + i*(outlineSide + space), outlinePosy);
        RenderMesh2D(meshes["outlineSquare"], shaders["VertexColor"], modelMatrix);
    }

    // Render rhombus shop
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombus1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + outlineSide + space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombus2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + 2*outlineSide + 2*space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombus3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(outlinePosx + 2*rhombusSide/3 + 3*outlineSide + 3*space, outlinePosy + 1.35*rhombusSide);
    RenderMesh2D(meshes["rhombus4"], shaders["VertexColor"], modelMatrix);
    
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

    // Render points
    for(int i = 0; i < score; ++i)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(get<0>(starPos) + (i%22)*starSize/2,
            get<1>(starPos) - (i/22)*(0.5*starSize));
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Rotate(glm::pi<float>()/10);
        RenderMesh2D(meshes["priceStar"], shaders["VertexColor"], modelMatrix);
        
    }
}
