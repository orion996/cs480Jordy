#include "object.h"
#include <stdlib.h>//rand
#include <iostream>

Object::Object(string fileName)
{  
 
  //run object loader
  LoadOBJ(fileName);
    
  angle = 0.0f;

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

void Object::Update(unsigned int dt)
{
 angle += dt * M_PI/4000;
 model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0f,1.0f,0.0f));
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

void Object::LoadOBJ(string fileName)
{
      //open input file
  FILE *fin = fopen(fileName.c_str(), "r");
  FILE *mat;
 
  if(fin == NULL)
  {
	std::cerr << "File is NULL!!" << std::endl; 
	return;
  }

  //read in stuff
  while(1)
  {
	char* lineHead = new char;

	int res = fscanf(fin, "%s", lineHead);
	if(res == EOF)//break if end of file
		break;

	if(strcmp(lineHead, "v") == 0)
	{
		glm::vec3 vertex;
		glm::vec3 color;
		fscanf(fin, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                
		color.x = (float)(rand() % 3);
		color.y = (float)(rand() % 3);
		color.z = (float)(rand() % 3); 

		Vertex *temp = new Vertex(vertex, color);
		Vertices.push_back(*temp);//add to vertices
	}
	else if(strcmp(lineHead, "f") == 0)
	{
		unsigned int firstVal[3], secondVal[3];
		fscanf(fin, "%i//%i %i//%i %i//%i\n", &firstVal[0], &secondVal[0], &firstVal[1], &secondVal[1], &firstVal[2], &secondVal[2]);
		Indices.push_back(firstVal[0]);
		Indices.push_back(firstVal[1]);	
		Indices.push_back(firstVal[2]);
	}

  }

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }
}
