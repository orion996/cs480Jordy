#include "object.h"
#include <iostream>

#define DIV 2000 //divisor constant for setting orbit/rotation speeds

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

  //set all angles to 0
  rotAngle = 0.0f;
  orbitAngle = 0.0f;
  mRotAngle = 0.0f;
  mOrbitAngle = 0.0f;

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
 const int div = DIV;//const divisor for setting orbit/rotation speed
 
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
	case 's':
	{
		isRotating = isOrbiting = true;
		rReversed = oReversed = false;
		
	}
	default:
	{
		break;
	}
 }

 if(isRotating && isOrbiting && !oReversed && !rReversed)//rotating, orbiting, not reversed
 {
	orbitAngle += (dt * M_PI/div);//set angle for rotation
 	rotAngle += (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && !oReversed && !rReversed)//not rotating, orbiting, not reversed
 {
	orbitAngle += (dt * M_PI/div);//set angle for rotation
 	rotAngle += 0;
 }
 else if(isRotating && !isOrbiting && !oReversed && !rReversed)//rotating,  not orbiting, not reversed
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle += (dt * M_PI/div);
 }
 else if(isRotating && isOrbiting && oReversed && !rReversed)//rotating, orbiting, orbit reversed
 {
	orbitAngle -= (dt * M_PI/div);//set angle for rotation
 	rotAngle += (dt * M_PI/(div/2));
 }
 else if(isRotating && isOrbiting && !oReversed && rReversed)//rotating, orbiting, rotation reversed
 {
	orbitAngle += (dt * M_PI/div);//set angle for rotation
 	rotAngle -= (dt * M_PI/(div/2));
 }
 else if(isRotating && isOrbiting && oReversed && rReversed)//rotating, orbiting, both reversed
 {
	orbitAngle -= (dt * M_PI/div);//set angle for rotation
 	rotAngle -= (dt * M_PI/div);
 }
 else if(!isRotating && !isOrbiting)//stopped 
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle += 0;
 }
 else if(!isRotating && isOrbiting && oReversed && !rReversed)//not rotating, orbiting,  orbit reversed
 {
	orbitAngle -= (dt * M_PI/div);//set angle for rotation
 	rotAngle += 0;
 }
 else if(isRotating && !isOrbiting && oReversed && !rReversed)//rotating, not orbiting, orbit reversed
 {
	orbitAngle -= 0;//set angle for rotation
 	rotAngle += (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && !oReversed && rReversed)//not rotating, orbiting, rotation reversed
 {
	orbitAngle += (dt * M_PI/div);//set angle for rotation
 	rotAngle -= 0;
 }
 else if(isRotating && !isOrbiting && !oReversed && rReversed)//rotating, not orbiting, rotation reversed
 {
	orbitAngle += 0;//set angle for rotation
 	rotAngle -= (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && oReversed && rReversed)//not rotating, orbiting, both reversed
 {
	orbitAngle -= (dt * M_PI/div);//set angle for rotation
 	rotAngle -= 0;
 }
 else if(isRotating && !isOrbiting && oReversed && rReversed)//rotating, not orbiting, both reversed
 {
	orbitAngle -= 0;//set angle for rotation
 	rotAngle -= (dt * M_PI/div);
 }
 model = (glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 1.0, 0.0))) *
 	(glm::translate(glm::mat4(1.0f), glm::vec3(-7, 0.0f, 0.0f))) *
 	(glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 1.0, 0.0)));


   
}


void Object::UpdateMoon(unsigned int dt, char cmd, glm::mat4 Planet)
{
 const int div = (int)(DIV/2);//const divisor for setting moon orbit/rotation speed

 //set booleans
 switch(cmd)
 {
	case '^':
	{
		if(isRotating)
			isRotating = false;
		else
			isRotating = true;
		break;
	}
	case 'v':
	{
		if(isOrbiting)
			isOrbiting = false;
		else
			isOrbiting = true;
		break;
	}
	case '>':
	{
		if(oReversed)
			oReversed = false;
		else
			oReversed = true;
		break;
	}
	case '<':
	{
		if(rReversed)
			rReversed = false;
		else
			rReversed = true;
		break;
	}
	case 's':
	{
		isRotating = isOrbiting = true;
		rReversed = oReversed = false;
		
	}
	default:
	{
		break;
	}


 }

 if(isRotating && isOrbiting && !oReversed && !rReversed)//rotating, orbiting, not reversed
 {
	mOrbitAngle += (dt * M_PI/div);//set angle for rotation
 	mRotAngle += (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && !oReversed && !rReversed)//not rotating, orbiting, not reversed
 {
	mOrbitAngle += (dt * M_PI/div);//set angle for rotation
 	mRotAngle += 0;
 }
 else if(isRotating && !isOrbiting && !oReversed && !rReversed)//rotating,  not orbiting, not reversed
 {
	mOrbitAngle += 0;//set angle for rotation
 	mRotAngle += (dt * M_PI/div);
 }
 else if(isRotating && isOrbiting && oReversed && !rReversed)//rotating, orbiting, orbit reversed
 {
	mOrbitAngle -= (dt * M_PI/div);//set angle for rotation
 	mRotAngle += (dt * M_PI/1000);
 }
 else if(isRotating && isOrbiting && !oReversed && rReversed)//rotating, orbiting, rotation reversed
 {
	mOrbitAngle += (dt * M_PI/div);//set angle for rotation
 	mRotAngle -= (dt * M_PI/div);
 }
 else if(isRotating && isOrbiting && oReversed && rReversed)//rotating, orbiting, both reversed
 {
	mOrbitAngle -= (dt * M_PI/div);//set angle for rotation
 	mRotAngle -= (dt * M_PI/div);
 }
 else if(!isRotating && !isOrbiting)//stopped 
 {
	mOrbitAngle += 0;//set angle for rotation
 	mRotAngle += 0;
 }
 else if(!isRotating && isOrbiting && oReversed && !rReversed)//not rotating, orbiting,  orbit reversed
 {
	mOrbitAngle -= (dt * M_PI/div);//set angle for rotation
 	mRotAngle += 0;
 }
 else if(isRotating && !isOrbiting && oReversed && !rReversed)//rotating, not orbiting, orbit reversed
 {
	mOrbitAngle -= 0;//set angle for rotation
 	mRotAngle += (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && !oReversed && rReversed)//not rotating, orbiting, rotation reversed
 {
	mOrbitAngle += (dt * M_PI/div);//set angle for rotation
 	mRotAngle -= 0;
 }
 else if(isRotating && !isOrbiting && !oReversed && rReversed)//rotating, not orbiting, rotation reversed
 {
	mOrbitAngle += 0;//set angle for rotation
 	mRotAngle -= (dt * M_PI/div);
 }
 else if(!isRotating && isOrbiting && oReversed && rReversed)//not rotating, orbiting, both reversed
 {
	mOrbitAngle -= (dt * M_PI/div);//set angle for rotation
 	mRotAngle -= 0;
 }
 else if(isRotating && !isOrbiting && oReversed && rReversed)//rotating, not orbiting, both reversed
 {
	mOrbitAngle -= 0;//set angle for rotation
 	mRotAngle -= (dt * M_PI/div);
 }
	model = glm::translate(glm::mat4(1.0f), glm::vec3(sin(mOrbitAngle*2) * 5, 0, cos(mOrbitAngle*2) * 5));
	model = model * Planet * glm::rotate(glm::mat4(1.0f), (mRotAngle*3), glm::vec3(0.0, 1.0, 0.0));
	model = glm::scale(model, glm::vec3(.6, .6, .6));
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

