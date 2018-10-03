#include "object.h"
Object::Object()
{ 
  m_parent = NULL;

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
    f 5 1 8        */

  m_renderData = new Model();

  m_renderData->LoadObject();

  angleTranslate = 0.0f;
  angleRotate = 0.0f;

  m_paused = 0; //not paused
  m_spinDirection = 0; //spinning counter-clockwise
  m_orbitDirection = 0; //orbiting counter-clockwise
}

Object::Object(string filename)
{

 //cout << "in parameterized object constructor" << endl;

 m_renderData = new Model();

 m_renderData->LoadObject(filename);

  //uncomment below to print all vertices
  /*
  cout << "Vertices:" << endl;
  cout << "{" << endl;
  for (int i = 0; i < Vertices.size(); i++)
  {
    cout << "{{"
         << Vertices[i].vertex.x
         << ", "
         << Vertices[i].vertex.y
         << ", "
         << Vertices[i].vertex.z
         << "}{"
         << Vertices[i].color.x
         << ", "
         << Vertices[i].color.y
         << ", "
         << Vertices[i].color.z
         << "}}" << endl;
  }
  cout << "}" << endl;
  //*/

  //uncomment below to print all indices
  /*
  cout << "Indices:" << endl;
  cout << "{" << endl;
  for (int i = 0; i < Indices.size(); i++)
  {
    cout << Indices[i] << " ";
    if (((i + 1) % 3) == 0) cout << endl;
  }
  cout << "}" << endl;
  //*/



  angleTranslate = 0.0f;
  angleRotate = 0.0f;

  m_paused = 0; //not paused
  m_spinDirection = 0; //spinning counter-clockwise
  m_orbitDirection = 0; //orbiting counter-clockwise
}

Object::~Object()
{
  delete m_renderData;
  m_children.clear();
}

void Object::Update(unsigned int dt)
{
  angleRotate += dt * (M_PI/5000);
  model = glm::rotate(glm::mat4(1.0), angleRotate, glm::vec3(0.0,1.0,0.0));
}

void Object::Render()
{
  //m_renderData->Render();

  //cout << "render function entry" << endl;

  vector<GLuint> VBs = m_renderData->get_VBs();
  vector<GLuint> IBs = m_renderData->get_IBs();
  vector<unsigned int> numIndices = m_renderData->get_numIndices();

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  for ( int i = 0; i<VBs.size();i++) 
  {

    glBindBuffer(GL_ARRAY_BUFFER, VBs[i]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBs[i]);



    glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);

  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

/*bool Object::LoadObject(string in_filename, vector<Vertex>* out_vertices, vector<unsigned int>* out_indices)
{
  
  Assimp::Importer importer;
   
  const aiScene *scene = importer.ReadFile(in_filename.c_str(), aiProcess_Triangulate);//read in vertices, with triangulation
  cout << scene->mNumMeshes << " meshes found" << endl;
  cout << scene->mNumMaterials << " materials found" << endl; 
  
  
  aiMesh *mesh = scene -> mMeshes[0];

  out_vertices->clear();
  out_indices->clear();

  for (int i = 0; i < scene->mNumMeshes; i++)
  {
    aiMesh *mesh = scene->mMeshes[i];
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    aiString materialName;
    material->Get(AI_MATKEY_NAME, materialName);
    cout << "using material " << mesh->mMaterialIndex << ": " << materialName.C_Str() << endl;
    //cout << "using material " << i << endl;

    for (int j = 0; j < mesh->mNumVertices; j++)
    {
      aiVector3D aiVec = mesh->mVertices[j];
      glm::vec3 vertex = glm::vec3(aiVec.x, aiVec.y, aiVec.z);

      aiColor4D aiColor;
      glm::vec3 color;
      if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor)
          && scene->mNumMaterials > 1)
      {
        cout << "Color obtained: {" << aiColor.r << "," << aiColor.g << "," << aiColor.b << "}" << endl;
        color = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
      }
      else
      {
        //default setting is random colors
        float default_color = (float) (((float) (rand() % 100 + 1)) / 100);
        color = glm::vec3(default_color, default_color, default_color);
      }
      
      Vertex *temp = new Vertex(vertex, color); //create the Vertex type to be pushed
      out_vertices->push_back(*temp);
      delete temp;
    }

    //cout << "Number of faces: " << mesh->mNumFaces << endl;
    for (int j = 0; j < mesh->mNumFaces; j++)
    {
      aiFace face = mesh->mFaces[j];

      //push each vertex to create the index
      out_indices -> push_back(face.mIndices[0]);
      out_indices -> push_back(face.mIndices[1]);
      out_indices -> push_back(face.mIndices[2]);
    }
  }
  
  /*
  if(aiMesh -> mNumVertices > 0)
  {
      for(int i=0; i<aiMesh->mNumVertices ; i++)//go through each vertex read in
      {
          aiVector3D aiVec = aiMesh -> mVertices[i];
          
          glm::vec3 vert = glm::vec3(aiVec.x, aiVec.y, aiVec.z);//set xyz of vertex
          
          glm::vec3 color = glm::vec3((rand() % 5), (rand() % 5), (rand() % 5));//random colors
          
          Vertex *temp = new Vertex(vert, color); //create the Vertex type to be pushed
          
          out_vertices -> push_back(*temp); //push vertex
      }
      
      for(int i=0 ; i<aiMesh->mNumFaces ; i++)//go through each index read in
      {
          aiFace *face = &aiMesh -> mFaces[i];
          
          out_indices -> push_back(face -> mIndices[0]);//push each vertex to create the index
          out_indices -> push_back(face -> mIndices[1]);
          out_indices -> push_back(face -> mIndices[2]);
      }
  }
  */
  
 // return true;
//}

/*
bool Object::LoadMaterial(string in_filename, vector<Material>* out_materials)
{
  ifstream fin;
  string fileData;

  fin.open(in_filename);
  if (!fin.is_open())
  {
    cout << "Could not open material file. Using default color option..." << endl;
    return false;
  }

  out_materials->clear();

  while (fin >> fileData)
  {
    if (fileData == "newmtl")
    {
      Material newMaterial;

      fin >> newMaterial.name;

      //loop until diffuse is found
      while (fileData != "Kd")
      {
        if (!(fin >> fileData)) //return false if diffuse is not found
        {
          fin.close();
          return false;
        }
      }

      fin >> newMaterial.color.x;
      fin >> newMaterial.color.y;
      fin >> newMaterial.color.z;

      out_materials->push_back(newMaterial);
    }
  }

  fin.close();
  return true;
}
*/

glm::mat4 Object::GetModel()
{
  return model;
}

/*
glm::mat4* Object::GetModelReference()
{
  return &model;
}
*/

glm::mat4 Object::GetTranslation()
{
  return translation;
}

glm::mat4 Object::GetRotation()
{
  return rotation;
}

glm::mat4 Object::GetScale()
{
  return scale;
}

bool Object::IsPaused()
{
  return m_paused;
}

unsigned int Object::GetSpinDirection()
{
  return m_spinDirection;
}

unsigned int Object::GetOrbitDirection()
{
  return m_orbitDirection;
}

/*
void SetParent(glm::mat4* parent)
{
  m_parent = parent;
}
*/

void Object::SetParent(Object* parent)
{
  m_parent = parent;
}

void Object::AddChild(Object* child)
{
  m_children.push_back(child);
}

void Object::RemoveChild()
{
  if (!m_children.empty())
  {
    m_children.pop_back();
  }
}

void Object::SetPaused(bool paused)
{
  m_paused = paused;
}

void Object::SetSpinDirection(unsigned int spinDirection)
{
  m_spinDirection = spinDirection;
}

void Object::SetOrbitDirection(unsigned int orbitDirection)
{
  m_orbitDirection = orbitDirection;
}
