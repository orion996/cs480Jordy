#include "model.h"

Model::Model()
{

}

Model::~Model()
{

}

/*
void Model::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    for ( int i = 0; i<VBs.size();i++) {

        glBindBuffer(GL_ARRAY_BUFFER, VBs[i]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBs[i]);



        glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);

    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
*/

void Model::LoadObject(void)
{
    //default constructor creates default cube object

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

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

    GLuint VB;
    GLuint IB;

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

    m_IBs.push_back(IB);
    m_VBs.push_back(VB);
    m_numIndices.push_back(Indices.size());

    Indices.clear();
    Vertices.clear();
}

void Model::LoadObject(string in_filename) {
    std::vector<Vertex> out_vertices;
    std::vector<unsigned int> out_indices;
    //Model* model = new Model();

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(in_filename.c_str(),
                                             aiProcess_Triangulate);//read in vertices, with triangulation
     //uncomment to print how many meshes and materials are found
    //cout << scene->mNumMeshes << " meshes found" << endl;
    //cout << scene->mNumMaterials << " materials found" << endl;


    aiMesh *mesh = scene->mMeshes[0];

    //m_VBs.clear();
    //m_IBs.clear();
    //m_numIndices.clear();

    out_vertices.clear();
    out_indices.clear();

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[i];
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        aiString materialName;
        material->Get(AI_MATKEY_NAME, materialName);
        //uncomment to print which material is being used
       // cout << "using material " << mesh->mMaterialIndex << ": " << materialName.C_Str() << endl;
        //cout << "using material " << i << endl;

        for (int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D aiVec = mesh->mVertices[j];
            glm::vec3 vertex = glm::vec3(aiVec.x, aiVec.y, aiVec.z);

            aiColor4D aiColor;
            glm::vec3 color;
            if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor)
                && scene->mNumMaterials > 1) {

                //cout << "Color obtained: {" << aiColor.r << "," << aiColor.g << "," << aiColor.b << "}" << endl;

                //uncomment to print out the color
               // cout << "Color obtained: {" << aiColor.r << "," << aiColor.g << "," << aiColor.b << "}" << endl;

                color = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
            } else {
                //default setting is random colors
                float default_color = (float) (((float) (rand() % 100 + 1)) / 100);
                color = glm::vec3(default_color, default_color, default_color);
            }

            Vertex *temp = new Vertex(vertex, color); //create the Vertex type to be pushed
            out_vertices.push_back(*temp);
            delete temp;
        }
        //cout << "loaded vertices" << endl;

        //cout << "Number of faces: " << mesh->mNumFaces << endl;
        for (int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];

            //push each vertex to create the index
            out_indices.push_back(face.mIndices[0]);
            out_indices.push_back(face.mIndices[1]);
            out_indices.push_back(face.mIndices[2]);

            //cout << "loaded a face" << endl;
        }

        /*for(unsigned int i = 0; i < Indices.size(); i++)
        {
            Indices[i] = Indices[i] - 1;
        }*/

        //cout << "loading a mesh..." << endl;

        GLuint VB;
        GLuint IB;

        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), &out_vertices[0], GL_STATIC_DRAW);
        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * out_indices.size(), &out_indices[0], GL_STATIC_DRAW);

        //cout << "loaded buffer data" << endl;

        m_IBs.push_back(IB);
        //out << "pushed index buffer onto member buffer" << endl;
        m_VBs.push_back(VB);
        //cout << "pushed vertex buffer onto member buffer" << endl;
        m_numIndices.push_back(out_indices.size());
        //cout << "pushed num indeces onto member buffer" << endl;

        //cout << "pushed buffer data onto member buffers" << endl;

        out_indices.clear();
        out_vertices.clear();

       /* for(const GLuint& IB:IBs) {
            IBs.push_back(IB);
        }*/
        //cout << "loaded a mesh" << endl;
    }
    //cout << "model loaded" << endl;
    //return model;
}
//
// Created by mari on 10/2/18.
//

/*
Model* Model::LoadObject(string in_filename) {
    std::vector<Vertex> out_vertices;
    std::vector<unsigned int> out_indices;
    Model* model = new Model();

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(in_filename.c_str(),
                                             aiProcess_Triangulate);//read in vertices, with triangulation
    cout << scene->mNumMeshes << " meshes found" << endl;
    cout << scene->mNumMaterials << " materials found" << endl;


    aiMesh *mesh = scene->mMeshes[0];

    out_vertices.clear();
    out_indices.clear();

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[i];
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        aiString materialName;
        material->Get(AI_MATKEY_NAME, materialName);
        cout << "using material " << mesh->mMaterialIndex << ": " << materialName.C_Str() << endl;
        //cout << "using material " << i << endl;

        for (int j = 0; j < mesh->mNumVertices; j++) {
            aiVector3D aiVec = mesh->mVertices[j];
            glm::vec3 vertex = glm::vec3(aiVec.x, aiVec.y, aiVec.z);

            aiColor4D aiColor;
            glm::vec3 color;
            if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor)
                && scene->mNumMaterials > 1) {
                //cout << "Color obtained: {" << aiColor.r << "," << aiColor.g << "," << aiColor.b << "}" << endl;
                color = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
            } else {
                //default setting is random colors
                float default_color = (float) (((float) (rand() % 100 + 1)) / 100);
                color = glm::vec3(default_color, default_color, default_color);
            }

            Vertex *temp = new Vertex(vertex, color); //create the Vertex type to be pushed
            out_vertices.push_back(*temp);
            delete temp;
        }

        //cout << "Number of faces: " << mesh->mNumFaces << endl;
        for (int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];

            //push each vertex to create the index
            out_indices.push_back(face.mIndices[0]);
            out_indices.push_back(face.mIndices[1]);
            out_indices.push_back(face.mIndices[2]);
        }
        //for(unsigned int i = 0; i < Indices.size(); i++)
        //{
        //    Indices[i] = Indices[i] - 1;
        //}
        GLuint VB;
        GLuint IB;
        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), &out_vertices[0], GL_STATIC_DRAW);
        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * out_indices.size(), &out_indices[0], GL_STATIC_DRAW);
        model->IBs.push_back(IB);
        model->VBs.push_back(VB);
        model->numIndices.push_back(out_indices.size());
        out_indices.clear();
        out_vertices.clear();
      //  for(const GLuint& VB:VBs){
       //     VBs.push_back(VB);
       // }


        //for(const GLuint& IB:IBs) {
        //    IBs.push_back(IB);
        //}
    }
    return model;
}
//creating multiple models for each material
//
// Created by mari on 10/2/18.
//
*/

vector<GLuint> Model::get_VBs(void)
{
    return m_VBs;
}

vector<GLuint> Model::get_IBs(void)
{
    return m_IBs;
}

vector<unsigned int> Model::get_numIndices(void)
{
    return m_numIndices;
}

void Model::set_VBs(vector<GLuint> VBs)
{
    m_VBs = VBs;
}

void Model::set_IBs(vector<GLuint> IBs)
{
    m_IBs = IBs;
}

void Model::set_numIndices(vector<GLuint> numIndices)
{
    m_numIndices = numIndices;
}