﻿#include "Tank.h"

#include <iostream>

#include "Cannon.h"
#include "Tracks.h"
#include "Turret.h"
#include "..\Tema2.h"
#include "lab_m1/Tema2/Meshes/Meshes.h"
using namespace m1;

void Tank::renderTank(implemented::CameraTema *camera, glm::mat4 projectionMatrix, std::unordered_map<std::string, Shader *> shaders,float time)
{
    { // Body
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getBody()->getBodyPosition());    
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        Meshes::RenderSimpleMesh(getComponent("body"), shaders["LabShader"], modelMatrix,
            glm::vec3(15.f/255, 39.f/255, 10.f/255), camera, time, projectionMatrix);
    }
    { // Track Left
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTracks()[0]->getTracksPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, tracks[0]->getTrackAngle(), glm::vec3(0, 1, 0));
        Meshes::RenderSimpleMesh(getComponent("track"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
    { // Track Right
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTracks()[1]->getTracksPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, tracks[1]->getTrackAngle(), glm::vec3(0, 1, 0));
        Meshes::RenderSimpleMesh(getComponent("track"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
    { // Turret
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTurret()->getTurretPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, turret->getTurretAngle(), glm::vec3(0, 1, 0));
        Meshes::RenderSimpleMesh(getComponent("turret"), shaders["LabShader"], modelMatrix,
            glm::vec3(30.f/255, 49.f/255, 30.f/255), camera, time, projectionMatrix);
    }
    { // Cannon
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getCannon()->getCannonPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, cannon->getCannonAngle(), glm::vec3(0, 1, 0));
        Meshes::RenderSimpleMesh(getComponent("cannon"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
    { // Projectiles
        for(auto projectile:projectiles)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, projectile->getProjectilePosition());
            modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
            modelMatrix = glm::rotate(modelMatrix, projectile->getProjectileAngle(), glm::vec3(0, 1, 0));
            Meshes::RenderSimpleMesh(getComponent("projectile"), shaders["LabShader"], modelMatrix,
                glm::vec3(1,1,1), camera, time, projectionMatrix);
        }
    }
}

void Tank::updatePosition(float x, float y, float z)
{
    tankPosition.x = x;
    tankPosition.y = y;
    tankPosition.z = z;
    tankAngle = 0;
    body->updateBodyPosition(x,y,z);
    
    const float trackDistanceZ = scale * body->getBodySize().z/4;
    const float trackDistanceY = scale * body->getBodySize().y/2;
    tracks[0]->updateTracksPosition(x, y - trackDistanceY, z + trackDistanceZ);
    tracks[1]->updateTracksPosition(x, y - trackDistanceY, z - trackDistanceZ);
    
    const float turretDistanceY = scale * body->getBodySize().y;
    const float turretDistanceX = scale * body->getBodySize().x/8;
    turret->updateTurretPosition(x - turretDistanceX, y + turretDistanceY, z);

    const float cannonDistanceY = scale * body->getBodySize().y;
    const float cannonDistanceX = scale * turret->getTurretSize().x;
    cannon->updateCannonPosition(x + cannonDistanceX, y + cannonDistanceY, z);
}

void Tank::rotateTank(float angle)
{
    tankAngle += angle;
    forwardTank = normalize(rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forwardTank, 0));
    rightTank   = normalize(rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(rightTank, 0));
    body->rotateBody(angle);
    tracks[0]->rotateTracks(angle);
    tracks[1]->rotateTracks(angle);
    turret->rotateTurret(angle);
    cannon->rotateCannon(angle);
}

void Tank::moveTank(float distance)
{
    glm::vec3 dir = glm::normalize(glm::vec3(forwardTank.x, 0, forwardTank.z));
    tankPosition += dir*distance;
    body->moveBody(dir * distance);
    tracks[0]->moveTracks(dir*distance);
    tracks[1]->moveTracks(dir*distance);
    turret->moveTurret(dir*distance);
    cannon->moveCannon(dir*distance);
}

// This function moves the tank in a straight line
void Tank::moveTank(glm::vec3 distance)
{
    tankPosition += distance;
    body->moveBody(distance);
    tracks[0]->moveTracks(distance);
    tracks[1]->moveTracks(distance);
    turret->moveTurret(distance);
    cannon->moveCannon(distance);
}

Projectile *Tank::createProjectile(float x, float y, float z, glm::vec3 forward, float angle)
{
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    x += dir.x * cannon->getCannonSize().x*scale;
    z += dir.z * cannon->getCannonSize().x*scale;
    return new Projectile(x, y, z, cannon->getForward(), cannon->getCannonAngle());
}

Cannon *Tank::createCannon(float x, float y, float z)
{
    components["cannon"] = Meshes::CreateMesh("cannon", "src/lab_m1/Tema2/Models/cannon/");
    const float distanceY = scale * body->getBodySize().y;
    return new Cannon(x, y + distanceY, z, glm::vec3(0, distanceY, 0), turret->getTurretPosition(), getTankForward());
}

Turret *Tank::createTurret(float x, float y, float z)
{
    components["turret"] = Meshes::CreateMesh("turret", "src/lab_m1/Tema2/Models/turret/");
    const float distanceY = scale * body->getBodySize().y;
    return new Turret(x, y + distanceY, z, glm::vec3(0, distanceY, 0), body->getBodyPosition());
}

Body* Tank::createBody(float x, float y, float z)
{
    components["body"] = Meshes::CreateMesh("body", "src/lab_m1/Tema2/Models/body/");
    return new Body(x, y, z);
}

Tracks **Tank::createTracks(float x, float y, float z)
{
    Mesh *mesh = Meshes::CreateMesh("track", "src/lab_m1/Tema2/Models/track/");
    components[mesh->GetMeshID()] = mesh;
    Tracks **tracks = new Tracks*[2];
    const float distanceX = scale * body->getBodySize().x / 4;
    const float distanceY = scale * body->getBodySize().y / 2;
    const float distanceZ = scale * body->getBodySize().z / 2;
    tracks[0] = new Tracks(x, y - distanceY, z + distanceZ, glm::vec3(0, -distanceY, distanceZ), body->getBodyPosition(), 0);
    tracks[1] = new Tracks(x, y - distanceY, z - distanceZ, glm::vec3(0, -distanceY, distanceZ), body->getBodyPosition(), RADIANS(180));
    return tracks;
}


void Tank::createTank(const float x, const float y, const float z)
{
    this->body = createBody(x, y, z);
    this->tracks = createTracks(x, y, z);
    this->turret = createTurret(x, y, z);
    this->cannon = createCannon(x, y, z);
    components["projectile"] = Meshes::CreateMesh("projectile", "src/lab_m1/Tema2/Models/projectile/");
}

void Tank::shoot()
{
    projectiles.push_back(createProjectile(cannon->getCannonPosition().x, cannon->getCannonPosition().y, cannon->getCannonPosition().z, cannon->getForward(), cannon->getCannonAngle()));
}

void Tank::rotateTurretTowardsPlayer(glm::vec3 playerPosition)
{
    // glm::vec3 dir = glm::normalize(glm::vec3(cannon->getForward().x, 0, cannon->getForward().z));
    // float x = cannon->getCannonPosition().x + dir.x * cannon->getCannonSize().x*scale;
    // float z = cannon->getCannonPosition().z + dir.z * cannon->getCannonSize().x*scale;
    // float angle = atan2(playerPosition.z - z, playerPosition.x - x);
    // std::cout << angle << std::endl;
    // std::cout << "Caca " << cannon->getCannonAngle() << std::endl;
    // if(angle > cannon->getCannonAngle())
    // {
    //     cannon->rotateCannon(RADIANS(1));
    //     turret->rotateTurret(RADIANS(1));
    // }
    // else if(angle < cannon->getCannonAngle())
    // {
    //     cannon->rotateCannon(RADIANS(-1));
    //     turret->rotateTurret(RADIANS(-1));
    // }
    auto fw = glm::normalize(cannon->getForward());
    float dotProduct = glm::dot(fw,  glm::normalize(playerPosition));

    glm::vec3 dir = glm::normalize(glm::vec3(cannon->getForward().x, 0, cannon->getForward().z));
    float x = cannon->getCannonPosition().x + dir.x * cannon->getCannonSize().x*scale;
    float z = cannon->getCannonPosition().z + dir.z * cannon->getCannonSize().x*scale;

    float angle = atan2(playerPosition.z, playerPosition.x) - atan2(z, x);

    while (angle > glm::pi<float>()) {
        angle -= glm::two_pi<float>();
    }
    while (angle <= -glm::pi<float>()) {
        angle += glm::two_pi<float>();
    }

    if(angle != 0.f)
    {
        float rotation = RADIANS(1);
        if(angle > glm::pi<float>() / 2 || angle < -glm::pi<float>() / 2)
        {
            rotation = -rotation;
        }
        cannon->rotateCannon(rotation);
        turret->rotateTurret(rotation);
    }
    
    // if(dotProduct != 0.f)
    // {
    //     if(dotProduct > 0)
    //     {
    //         cannon->rotateCannon(RADIANS(1));
    //         turret->rotateTurret(RADIANS(1));
    //     }
    //     else
    //     {
    //         cannon->rotateCannon(RADIANS(-1));
    //         turret->rotateTurret(RADIANS(-1));
    //     }
    // }
    
}

void Tank::checkCollisionWithTank(Tank *tank)
{
    float razaTank1 = tank->getScale() * tank->getBody()->getBodySize().x/2;
    float razaTank2 = getScale() * getBody()->getBodySize().x/2;
    float distance = glm::distance(tank->getPosition(), getPosition());
    if(distance < razaTank1 + razaTank2)
    {
        glm::vec3 dif = tank->getPosition() - getPosition();
        if(glm::any(glm::isnan(glm::normalize(dif))))
        { // Protection agains spawning on eachother
            tank->moveTank(glm::vec3(tank->getScale()*tank->getBody()->getBodySize().x, 0, 0));
        }
        else
        {
            glm::vec3 P = glm::normalize(dif) * abs(razaTank1 + razaTank2 - distance);
            moveTank(-P);
            tank->moveTank(P);
        }
    }
}

void Tank::removeProjectiles()
{
    for(auto projectile:projectiles)
    {
        if(!projectile->isAlive())
        {
            projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
        }
    }
}



Tank::Tank()
{
}

Tank::~Tank()
{
}
