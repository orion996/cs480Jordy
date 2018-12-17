#ifndef BOARD_H
#define BOARD_H

#include "physics_object.h"

using namespace std;

class Board : public PhysicsObject
{
public:
  Board();
  Board(string filename);
  Board(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  Board(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~Board();

  bool Initialize(btTriangleMesh *triMesh);
  void Update(unsigned int dt);

private:

};

#endif /* BOARD_H */
