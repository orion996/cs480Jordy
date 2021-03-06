#include "object.h"
#include <SDL2/SDL.h>
#include <iostream>

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  rotAngle = 0.0f;
  orbitAngle= 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}



void Object::Update(unsigned int dt, char cmd)
{
  
 model = glm::mat4(1.0f);//render the cube

 //reference code
 /*orbitAngle += (dt * M_PI/2000);//set angle for rotation
 rotAngle = orbitAngle * 1.5f;
 model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));*/
 
 //set booleans to determine state

 switch(cmd)
 {
	case 'r':
	{
		if(isRotating)
			isRotating = false;
		else
			isRotating = true;
		break;
	}
	case 'o':
	{
		if(isOrbiting)
			isOrbiting = false;
		else
			isOrbiting = true;
		break;
	}
	case 'a':
	{
		if(oReversed)
			oReversed = false;
		else
			oReversed = true;
		break;
	}
	case 'b':
	{
		if(rReversed)
			rReversed = false;
		else
			rReversed = true;
		break;
	}
	default:
	{
		break;
	}
 }
	


 if(isRotating && isOrbiting && !oReversed && !rReversed)//rotating, orbiting, not reversed
 {
	orbitAngle += (dt * M_PI/2000);//set angle for rotation
 	rotAngle += (dt * M_PI/2000);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(!isRotating && isOrbiting && !oReversed && !rReversed)//not rotating, orbiting, not reversed
 {
	orbitAngle += (dt * M_PI/2000);//set angle for rotation
 	rotAngle += 0;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && !isOrbiting && !oReversed && !rReversed)//rotating,  not orbiting, not reversed
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle += (dt * M_PI/2000) * 1.5f;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && isOrbiting && oReversed && !rReversed)//rotating, orbiting, orbit reversed
 {
	orbitAngle -= (dt * M_PI/2000);//set angle for rotation
 	rotAngle += (dt * M_PI/900);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && isOrbiting && !oReversed && rReversed)//rotating, orbiting, rotation reversed
 {
	orbitAngle += (dt * M_PI/2000);//set angle for rotation
 	rotAngle -= (dt * M_PI/900);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && isOrbiting && oReversed && rReversed)//rotating, orbiting, both reversed
 {
	orbitAngle -= (dt * M_PI/2000);//set angle for rotation
 	rotAngle -= (dt * M_PI/2000);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(!isRotating && !isOrbiting)//stopped 
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle += 0;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(!isRotating && isOrbiting && oReversed && !rReversed)//not rotating, orbiting,  orbit reversed
 {
	orbitAngle -= (dt * M_PI/2000);//set angle for rotation
 	rotAngle += 0;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && !isOrbiting && oReversed && !rReversed)//rotating, not orbiting, orbit reversed
 {
	orbitAngle -= 0;//set angle for rotation
 	rotAngle += (dt * M_PI/2000);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(!isRotating && isOrbiting && !oReversed && rReversed)//not rotating, orbiting, rotation reversed
 {
	orbitAngle += (dt * M_PI/2000);//set angle for rotation
 	rotAngle -= 0;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && !isOrbiting && !oReversed && rReversed)//rotating, not orbiting, rotation reversed
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle -= (dt * M_PI/2000);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(!isRotating && isOrbiting && oReversed && rReversed)//not rotating, orbiting, both reversed
 {
	orbitAngle -= (dt * M_PI/2000);//set angle for rotation
 	rotAngle -= 0;
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }
 else if(isRotating && !isOrbiting && oReversed && rReversed)//rotating, not orbiting, both reversed
 {
	orbitAngle -= 0;//set angle for rotation
 	rotAngle -= (dt * M_PI/2000);
 	model = glm::rotate(model, (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
 	model = glm::translate(model, glm::vec3(-7, 0.0f, 0.0f));
 	model = glm::rotate(model, (rotAngle), glm::vec3(0.0, 1.0, 0.0));
 }


   
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

