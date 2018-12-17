//
// Created by mari on 10/27/18.
//

#ifndef BULLETTUTORIAL_CYLINDER_H
#define BULLETTUTORIAL_CYLINDER_H
#include "physics_object.h"

using namespace std;

class Cylinder : public PhysicsObject
{
public:
    Cylinder();
    Cylinder(string filename);
    Cylinder(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    Cylinder(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
    ~Cylinder();

    bool Initialize(btTriangleMesh *triMesh);

    void Update(unsigned int dt);

private:

};


#endif //BULLETTUTORIAL_CYLINDER_H
