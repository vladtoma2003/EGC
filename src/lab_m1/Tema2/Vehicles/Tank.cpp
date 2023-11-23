#include "Tank.h"

#include <iostream>

#include "Cannon.h"
#include "Tracks.h"
#include "Turret.h"
#include "..\Tema2.h"
#include "lab_m1/Tema2/Meshes/Meshes.h"
using namespace m1;

Cannon *Tank::createCannon(float x, float y, float z)
{
    components["cannon"] = Meshes::CreateMesh("cannon", "src/lab_m1/Tema2/Models/cannon/");
    const float distanceY = scale * body->getBodySize().y;
    const float distanceZ = scale * turret->getTurretSize().z;
    return new Cannon(x, y + distanceY, z + distanceZ);
}

Turret *Tank::createTurret(float x, float y, float z)
{
    components["turret"] = Meshes::CreateMesh("turret", "src/lab_m1/Tema2/Models/turret/");
    const float distanceY = scale * body->getBodySize().y;
    const float distanceZ = scale * body->getBodySize().z/8;
    return new Turret(x, y + distanceY, z - distanceZ);
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
    const float distanceX = scale * body->getBodySize().x / 2;
    const float distanceY = scale * body->getBodySize().y / 2;
    std::cout << "distanceX: " << distanceX << "\n" << "distanceY: " << distanceY << "\n";
    tracks[0] = new Tracks(x + distanceX, y - distanceY, z);
    tracks[1] = new Tracks(x - distanceX, y - distanceY, z);
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
