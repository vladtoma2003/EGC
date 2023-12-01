#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "Building.h"
#include "Vehicles/Cannon.h"
#include "Vehicles/Turret.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    tank = new Tank();
    tank->createTank(0, tank->getScale(), 0, glm::vec3(15.f/255, 39.f/255, 10.f/255));
    
    camera = new implemented::CameraTema();
    camera->Set(tank->getPosition() + glm::vec3(-3.5f, 1.5, 0), tank->getPosition(), glm::vec3(0, 1, 0));
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Big square for ground
    {
        vector<VertexFormat> vertices{
            VertexFormat (glm::vec3(0, 0, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 0
            VertexFormat (glm::vec3(1, 0, -1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 1
            VertexFormat (glm::vec3(1, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 2
            VertexFormat (glm::vec3(-1, 0, -1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 3
            VertexFormat (glm::vec3(-1, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 4
        };
        vector<unsigned int> indices{
            1, 2, 3,
            2, 3, 4,
        };
        meshes["ground"] = Meshes::CreateMesh("ground", vertices, indices);
    }
    // Cube for buildings
   meshes["cube"] = Building::createMesh();

    createNTanks(10);
    initBuildings();
    
    aspectRatio = window->props.aspectRatio;
    projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(68.f/255, 176.f/255, 241.f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

// AICI
void Tema2::Update(float deltaTimeSeconds)
{
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    time = Engine::GetElapsedTime();
    
    std::cout << "time: " << time << std::endl;
    tank->renderTank(camera, projectionMatrix, shaders, time);
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(100.f));
        Meshes::RenderSimpleMesh(meshes["ground"], shaders["LabShader"], modelMatrix,
            glm::vec3(69.f/255, 158.f/255, 19.f/255), camera, 100, projectionMatrix);
    }
    for(auto enemyTank:enemyTanks)
    {
        enemyTank->renderTank(camera, projectionMatrix, shaders, time);
    }
    for(auto building:buildings)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, building->getPosition());
        modelMatrix = glm::scale(modelMatrix, building->getScale());
        Meshes::RenderSimpleMesh(meshes["cube"], shaders["LabShader"], modelMatrix, building->getColor(), camera, 100, projectionMatrix);
    }
    if(time > 60 || tank->getHP() <= 0)
    {
        gameOver = true;
        vClipping = true;
        std::cout << "GAME OVER\n";
    }
    if(!gameOver)
    {
        std::cout<<"CACA\n";
        for(auto projectile:tank->getProjectiles())
        {
            projectile->moveProjectile(projectile->getSpeed() * deltaTimeSeconds, deltaTimeSeconds);
            checkCollisionProjectileBuilding(projectile);
            projectile->checkTimeOut();
        }
        tank->removeProjectiles();
        // std::cout << "CACA\n";
        for(auto enemyTank:enemyTanks)
        {
            // std::cout << "Rendering enemy tank\n" << enemyTank->getPosition() << endl;
            checkCollisionWithProjectiles(enemyTank, tank->getProjectiles());
            checkCollisionWithProjectiles(tank, enemyTank->getProjectiles());
            for(auto projectile:enemyTank->getProjectiles()) // enemy tank projectiles
                {
                projectile->moveProjectile(projectile->getSpeed() * deltaTimeSeconds, deltaTimeSeconds);
                projectile->checkTimeOut();
                }
            enemyTank->removeProjectiles();
            // tank->checkCollisionWithTank(enemyTank);
            tankCollision(tank, enemyTank);
            checkBuildingsCollision(enemyTank);
            if(enemyTank->getHP() <= 0)
            {
                continue;
            }
            searchForPlayer(enemyTank, deltaTimeSeconds, tank->getPosition());
            for(auto enemyTank2:enemyTanks)
            {
                if(enemyTank != enemyTank2)
                {
                    enemyTank->checkCollisionWithTank(enemyTank2);
                    checkCollisionWithProjectiles(enemyTank, enemyTank2->getProjectiles());
                    checkCollisionWithProjectiles(enemyTank2, enemyTank->getProjectiles());
                }
            }
            enemyTank->rotateTurretTowardsPlayer(tank->getPosition());
            enemyTank->reload(deltaTimeSeconds);
            // spawnEnemyTank();
            // std::cout << tank->getHP() << endl;
        }
    
        // Set Tank position to camera
        if(!vClipping)
        {
            camera->Set(tank->getPosition(), glm::vec3(0, 1, 0));
        }
        tank->reload(deltaTimeSeconds);
        checkBuildingsCollision(tank);
    }
}

void Tema2::checkCollisionWithProjectiles(Tank* tank, std::vector<Projectile*> projectiles)
{
    for(auto projectile:projectiles)
    {
        float projectileRadius = tank->getScale()*projectile->getProjectileSize().x/2;
        float tankRadius = tank->getScale()*tank->getBody()->getBodySize().x/2;
        float distance = glm::distance(tank->getPosition(), projectile->getProjectilePosition());
        if(distance < projectileRadius + tankRadius)
        {
            tank->setHP(projectile->getDamage());
            projectile->setAlive(false);
        }
    }
}

void Tema2::initBuildings()
{
    int n = rand()%6 + 10; // [10,15] buildings
    for(int i = 0; i < n; ++i)
    {
        buildings.emplace_back(new Building);
    }
}

void Tema2::checkBuildingsCollision(Tank* tank)
{
    for(auto building:buildings)
    {
        float tankRadius = tank->getScale()*tank->getBody()->getBodySize().x/2;
        // check tank radius with each side of the building
        glm::vec3 corner0 = building->getPosition();
        glm::vec3 corner1 = building->getPosition() + glm::vec3(building->getScale().x, 0, 0);
        glm::vec3 corner2 = building->getPosition() + glm::vec3(0, 0, building->getScale().z);
        glm::vec3 corner3 = building->getPosition() + glm::vec3(building->getScale().x, 0, building->getScale().z);
        float side0 = glm::distance(corner0, corner1);
        float side1 = glm::distance(corner0, corner2);
        float side2 = glm::distance(corner1, corner3);
        float side3 = glm::distance(corner2, corner3);

        glm::vec3 side0Direction = glm::normalize(corner1 - corner0);
        glm::vec3 side1Direction = glm::normalize(corner2 - corner0);
        glm::vec3 side2Direction = glm::normalize(corner3 - corner1);
        glm::vec3 side3Direction = glm::normalize(corner3 - corner2);

        glm::vec3 side0ToTank = tank->getPosition() - corner0;
        glm::vec3 side1ToTank = tank->getPosition() - corner0;
        glm::vec3 side2ToTank = tank->getPosition() - corner1;
        glm::vec3 side3ToTank = tank->getPosition() - corner2;

        float distance0 = glm::dot(side0ToTank, side0Direction);
        distance0 = glm::clamp(distance0, 0.f, side0);
        glm::vec3 closestPoint0 = corner0 + distance0 * side0Direction;
        
        float distance1 = glm::dot(side1ToTank, side1Direction);
        distance1 = glm::clamp(distance1, 0.f, side1);
        glm::vec3 closestPoint1 = corner0 + distance1 * side1Direction;
        
        float distance2 = glm::dot(side2ToTank, side2Direction);
        distance2 = glm::clamp(distance2, 0.f, side2);
        glm::vec3 closestPoint2 = corner1 + distance2 * side2Direction;
        
        float distance3 = glm::dot(side3ToTank, side3Direction);
        distance3 = glm::clamp(distance3, 0.f, side3);
        glm::vec3 closestPoint3 = corner2 + distance3 * side3Direction;

        float distanceToTank0 = glm::distance(closestPoint0, tank->getPosition());
        float distanceToTank1 = glm::distance(closestPoint1, tank->getPosition());
        float distanceToTank2 = glm::distance(closestPoint2, tank->getPosition());
        float distanceToTank3 = glm::distance(closestPoint3, tank->getPosition());

        if(checkIfTankIsInsideBuilding(tank, building))
        {
            tank->moveTank(glm::vec3(building->getScale().x, 0, 0));
            if(!vClipping && tank == this->tank)
                camera->Set(tank->getPosition() + glm::vec3(-3.5f, 1.5, 0), tank->getPosition(), glm::vec3(0, 1, 0));
        }
        
        if(distanceToTank0 < tankRadius || distanceToTank1 < tankRadius || distanceToTank2 < tankRadius || distanceToTank3 < tankRadius)
        {
            glm::vec3 closestPoint;
            float distance;
            if(distanceToTank0 < tankRadius)
            {
                closestPoint = closestPoint0;
                distance = distanceToTank0;
            } else if(distanceToTank1 < tankRadius)
            {
               closestPoint = closestPoint1;
                distance = distanceToTank1;
            } else if(distanceToTank2 < tankRadius)
            {
                closestPoint = closestPoint2;
                distance = distanceToTank2;
            } else
            {
                closestPoint = closestPoint3;
                distance = distanceToTank3;
            }
            glm::vec3 dif = tank->getPosition() - closestPoint - glm::vec3(0, tank->getPosition().y, 0);
            if(glm::any(glm::isnan(glm::normalize(dif))))
            { // protection against spawning tanks on top of each other
                tank->moveTank(glm::vec3(building->getScale().x+tank->getBody()->getBodySize().x,  0, 0));
            }
            else
            {
                glm::vec3 P = glm::normalize(dif) * abs(tankRadius - distance);
                // tank->moveTank(P);
                if(!vClipping && tank == this->tank && tank->moveTank(P))
                    camera->MoveForward(P);
            }
            
        }
    }
}

bool Tema2::checkIfTankIsInsideBuilding(Tank* tank, Building* building)
{
    if(tank->getPosition().x > building->getPosition().x && tank->getPosition().x < building->getPosition().x + building->getScale().x &&
        tank->getPosition().z > building->getPosition().z && tank->getPosition().z < building->getPosition().z + building->getScale().z)
    {
        return true;
    }
    return false;
}

void Tema2::spawnEnemyTank()
{
    if(atLeastOneTankDead())
    {
        std::cout << "Spawning new tank" << std::endl;
        float x = rand() % 100 - 50;
        float z = rand() % 100 - 50;
        Tank *newTank = new Tank();
        newTank->createTank(x, newTank->getScale(), z, glm::vec3(0.545, 0, 0.123f));
        std::cout << "tank created at " << x << " " << z << "\n";
        enemyTanks.push_back(newTank);
        std::cout << "tank pushed\n";
    }
}

bool Tema2::atLeastOneTankDead()
{
    for(auto enemyTank:enemyTanks)
    {
        if(enemyTank->getHP() <= 0)
        {
            return true;
        }
    }
    return false;
}

void Tema2::tankCollision(Tank *tank1, Tank *tank2) const
{
    const float tank1Scale = tank1->getScale();
    const float tank2Scale = tank2->getScale();
    const float tank1Radius = tank1Scale*tank1->getBody()->getBodySize().x/2;
    const float tank2Radius = tank2Scale*tank2->getBody()->getBodySize().x/2;
    const float distance = glm::distance(tank1->getPosition(), tank2->getPosition());
    if(distance < tank1Radius + tank2Radius)
    {
        const glm::vec3 dif = tank1->getPosition() - tank2->getPosition();
        if(glm::any(glm::isnan(glm::normalize(dif))))
        { // protection against spawning tanks on top of each other
            tank2->moveTank(glm::vec3(tank1Scale*tank1->getBody()->getBodySize().x, 0, 0));
        }
        else
        {
            glm::vec3 P = glm::normalize(dif) * abs(tank1Radius + tank2Radius - distance);
            // tank1->moveTank(P);
            tank2->moveTank(-P);
            if(!vClipping && tank1->moveTank(P))
                camera->MoveForward(P);
            // tank->setSpeed(0.5f);
        }
    }
}

void Tema2::searchForPlayer(Tank* tank, float deltaTime, glm::vec3 playerPosition)
{
    if(tank->getHP() <= 0)
    {
        return;
    }
    if(tank->getMoveTime() < tank->getMoveTotal())
    {
        if(glm::distance(tank->getPosition(), playerPosition) > 10) // randomly move when not in range
        {
  
            if(tank->getDecision() % 2 == 1) // Rotate            {
            {
                if(tank->getDecision() == 1) // Right
                    {
                    tank->rotateTank(RADIANS(1));
                    }
                else if (tank->getDecision() == 3) // Left
                {
                    tank->rotateTank(RADIANS(-1));
                } else { // Rotate turret
                    if(tank->getDecision() == 5)
                    {
                        tank->getTurret()->rotateTurret(RADIANS(0.1));
                        tank->getCannon()->rotateCannon(RADIANS(0.1));
                    } else
                    {
                        tank->getTurret()->rotateTurret(-RADIANS(0.1));
                        tank->getCannon()->rotateCannon(-RADIANS(0.1));
                    }
                }
            }
            else // Move
                {
                if(tank->getDecision() == 0 || tank->getDecision() == 2 || tank->getDecision() == 4) // Forward
                {
                    tank->moveTank(deltaTime*tank->getSpeed());
                }
                else
                {
                    tank->moveTank(-deltaTime*tank->getSpeed());
                }
            }
            
            tank->setMoveTime(deltaTime);
        }
    } else
    {
        const float newTime = rand() % 3 + 1; // 1-3 seconds
        tank->setMoveTotal(newTime);
        tank->resetMoveTime();
        const int decision = rand() % 8; // move or rotate
        tank->setDecision(decision);
    }
}

void Tema2::createNTanks(int n)
{
    for(int i = 0; i < n; i++)
    {
        const float x = rand() % 100 - 50;
        const float z = rand() % 100 - 50;
        std::cout << "Spawning tank at " << x << " " << z << std::endl;
        // enemyTanks.push_back(new Tank(x, enemyTanks[0]->getScale(), z, glm::vec3(0.545, 0, 0.123f)));
        enemyTanks.push_back(new Tank());
        enemyTanks[enemyTanks.size()-1]->createTank(x, enemyTanks[enemyTanks.size()-1]->getScale(), z, glm::vec3(0.545, 0, 0.123f));
    }
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}
/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f;
    if (window->KeyHold(GLFW_KEY_W)) {
        if(vClipping)
        {
            camera->TranslateForward(deltaTime*cameraSpeed*10);
        } else {
            if(tank->moveTank(deltaTime*tank->getSpeed()))
                camera->MoveForward(deltaTime*tank->getSpeed(), tank->getTankForward());
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        if(vClipping)
        {
            camera->TranslateRight(-deltaTime*cameraSpeed*10);
        } else
        {
            tank->rotateTank(RADIANS(1));
            // camera->TranslateForward(2);
            camera->RotateThirdPerson_OY(RADIANS(1));
            // camera->TranslateForward(-2);
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if(vClipping)
        {
            camera->TranslateForward(-deltaTime*cameraSpeed*10);
        } else {
            if(tank->moveTank(-deltaTime*tank->getSpeed()))
                camera->MoveForward(-deltaTime*tank->getSpeed(), tank->getTankForward());
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        if(vClipping)
        {
            camera->TranslateRight(deltaTime*cameraSpeed*10);
        } else
        {
            tank->rotateTank(-RADIANS(1));
            // camera->TranslateForward(2);
            camera->RotateThirdPerson_OY(-RADIANS(1));
            // camera->TranslateForward(-2);
        }
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        // TODO(student): Translate the camera downward
        if(vClipping)
        {
            camera->TranslateUpward(-deltaTime*cameraSpeed*10);
        }
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        if(vClipping)
        {
            camera->TranslateUpward(deltaTime*cameraSpeed*10);
        }
    }

    
    if(isPerspective && window->KeyHold(GLFW_KEY_F))
    {
        fov += 0.5f*deltaTime;
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }
    if(isPerspective && window->KeyHold(GLFW_KEY_R))
    {
        fov -= 0.5f*deltaTime;
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }
    if(!isPerspective && window->KeyHold(GLFW_KEY_K))
    {
        orthoLeft += 0.5f*deltaTime;
        orthoRight -= 0.5f*deltaTime;
        orthoUp -= 0.5f*deltaTime;
        orthoDown += 0.5f*deltaTime;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.00f, 200.0f);
    }
    
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if(key == GLFW_KEY_O)
    {
        orthoLeft = -8.0f;
        orthoRight = 8.0f;
        orthoUp = 4.5f;
        orthoDown = -4.5f;
        isPerspective = false;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, zNear, zFar);
    }
    if(key == GLFW_KEY_V)
    {
        vClipping = !vClipping;
        if(!vClipping) // reset camera
        {
            glm::vec3 newPos = glm::normalize(glm::vec3(tank->getTankForward().x, 0, tank->getTankForward().z))*3.5f;
            newPos += glm::vec3(0, -1.5, 0);
            camera->Set(tank->getPosition() - newPos , tank->getPosition(), glm::vec3(0, 1, 0));
        }
    }

    if(key == GLFW_KEY_M)
    {
        tank->updateHP(100000);
    }

    // if(key == GLFW_KEY_L)
    // {
    //     tank->updatePosition(0,0,0);
    // }
    if(key == GLFW_KEY_P)
    {
        enemyTanks.push_back(new Tank());
        enemyTanks[enemyTanks.size()-1]->createTank(5, enemyTanks[enemyTanks.size()-1]->getScale(), 5, glm::vec3(0.545, 0, 0.123f));
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    // Add mouse move event
    if(!vClipping)
    {
        if(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            camera->RotateThirdPerson_OX(-sensivityOX*deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY*deltaX);
        } else
        {
            tank->getTurret()->incDeltaX(10*(deltaX>1?1:deltaX< -1?-1:0));
            tank->getCannon()->incDeltaX(10*(deltaX>1?1:deltaX < -1?-1:0));
            tank->getTurret()->rotateTurret(-sensivityOY*tank->getTurret()->getDeltaX());
            tank->getCannon()->rotateCannon(-sensivityOY*tank->getCannon()->getDeltaX());
            tank->getTurret()->setDeltaX(0);
            tank->getCannon()->setDeltaX(0);
        }
    }
    else
    {
        if(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            camera->RotateFirstPerson_OX(-sensivityOX*deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY*deltaX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if(button == 1)
    {
        tank->shoot();
    }
}

void Tema2::checkCollisionProjectileBuilding(Projectile* projectile)
{
    for(auto building:buildings){
        if(projectile->getProjectilePosition().x < building->getPosition().x + building->getScale().x &&
            projectile->getProjectilePosition().x > building->getPosition().x &&
            projectile->getProjectilePosition().z < building->getPosition().z + building->getScale().z &&
            projectile->getProjectilePosition().z > building->getPosition().z)
        {
            projectile->setAlive(false);
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if(button == 2 && !vClipping)
    {
        glm::vec3 newPos = glm::normalize(glm::vec3(tank->getTankForward().x, 0, tank->getTankForward().z))*3.5f;
        newPos += glm::vec3(0, -1.5, 0);
        camera->Set(tank->getPosition() - newPos, tank->getPosition(), glm::vec3(0, 1, 0));
    }
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
