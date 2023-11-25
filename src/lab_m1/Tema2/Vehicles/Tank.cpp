#include "Tank.h"

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
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(10.f, -20.f, 10.f));
        modelMatrix = glm::translate(modelMatrix, getBody()->getBodyPosition());    
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -getBody()->getBodySize().y/2, 0));
        Meshes::RenderSimpleMesh(getComponent("body"), shaders["LabShader"], modelMatrix,
            glm::vec3(15.f/255, 39.f/255, 10.f/255), camera, time, projectionMatrix);
    }
    { // Track Left
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTracks()[0]->getTracksPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        // modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, getTracks()[0]->getTracksSize().z));
        Meshes::RenderSimpleMesh(getComponent("track"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
    { // Track Right
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTracks()[1]->getTracksPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(-getPosition().x, 0, -getPosition().z));
        // modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(getPosition().x, 0, getPosition().z));
        Meshes::RenderSimpleMesh(getComponent("track"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
    { // Turret
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getTurret()->getTurretPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -getTurret()->getTurretSize().z/2));
        Meshes::RenderSimpleMesh(getComponent("turret"), shaders["LabShader"], modelMatrix,
            glm::vec3(30.f/255, 49.f/255, 30.f/255), camera, time, projectionMatrix);
    }
    { // Cannon
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, getCannon()->getCannonPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(getScale()));
        // modelMatrix = glm::rotate(modelMatrix, getAngle(), glm::vec3(0, 1, 0));
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -getCannon()->getCannonSize().z/2));
        Meshes::RenderSimpleMesh(getComponent("cannon"), shaders["LabShader"], modelMatrix,
            glm::vec3(50.f/255, 50.f/255, 50.f/255), camera, time, projectionMatrix);
    }
}

void Tank::updatePosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
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
    body->rotateBody(angle);
    tracks[0]->rotateTracks(angle);
    tracks[1]->rotateTracks(angle);
    turret->rotateTurret(angle);
    cannon->rotateCannon(angle);
}

void Tank::moveTank(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
    body->moveBody(x, y, z);
    tracks[0]->moveTracks(x, y, z);
    tracks[1]->moveTracks(x, y, z);
    turret->moveTurret(x, y, z);
    cannon->moveCannon(x, y, z);
}

Cannon *Tank::createCannon(float x, float y, float z)
{
    components["cannon"] = Meshes::CreateMesh("cannon", "src/lab_m1/Tema2/Models/cannon/");
    const float distanceY = scale * body->getBodySize().y;
    const float distanceX = scale * turret->getTurretSize().x;
    return new Cannon(x + distanceX, y + distanceY, z);
}

Turret *Tank::createTurret(float x, float y, float z)
{
    components["turret"] = Meshes::CreateMesh("turret", "src/lab_m1/Tema2/Models/turret/");
    const float distanceY = scale * body->getBodySize().y;
    const float distanceX = scale * body->getBodySize().x/8;
    const float distanceZ = scale * body->getBodySize().z/4;
    return new Turret(x - distanceX, y + distanceY, z, glm::vec3(distanceX, distanceY, distanceZ), body->getBodyPosition());
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
    float distanceX = scale * body->getBodySize().x / 2;
    const float distanceZ = scale * body->getBodySize().z / 4;
    const float distanceY = scale * body->getBodySize().y / 2;
    tracks[0] = new Tracks(x, y - distanceY, z + distanceZ, glm::vec3(distanceX, distanceY, distanceZ), body->getBodyPosition(), 0);
    tracks[1] = new Tracks(x, y - distanceY, z - distanceZ, glm::vec3(distanceX, distanceY, distanceZ), body->getBodyPosition(), 180);
    return tracks;
}


void Tank::createTank(const float x, const float y, const float z)
{
    std::cout << "Tank created\n";
    this->body = createBody(x, y, z);
    this->tracks = createTracks(x, y, z);
    this->turret = createTurret(x, y, z);
    this->cannon = createCannon(x, y, z);
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
