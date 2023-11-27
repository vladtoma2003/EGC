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

Cannon *Tank::createCannon(float x, float y, float z)
{
    components["cannon"] = Meshes::CreateMesh("cannon", "src/lab_m1/Tema2/Models/cannon/");
    const float distanceY = scale * body->getBodySize().y;
    return new Cannon(x, y + distanceY, z, glm::vec3(0, distanceY, 0), turret->getTurretPosition());
}

Turret *Tank::createTurret(float x, float y, float z)
{
    components["turret"] = Meshes::CreateMesh("turret", "src/lab_m1/Tema2/Models/turret/");
    // const float distanceX = scale * body->getBodySize().x/8;
    const float distanceY = scale * body->getBodySize().y;
    // const float distanceZ = scale * body->getBodySize().z/4;
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
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
