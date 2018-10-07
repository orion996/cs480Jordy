#include "model.h"

Model::Model()
{

}

Model::~Model()
{

}

bool Model::LoadObject(void)
{
    //default constructor creates default cube object

    /*
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
    */

    return false;
}

bool Model::LoadObject(string in_filename) 
{
    Assimp::Importer importer;
    std::vector<Vertex> out_vertices;
    std::vector<unsigned int> out_indices;

    //read in vertices, with triangulation
    const aiScene *scene = importer.ReadFile(
        in_filename.c_str(),
        aiProcess_Triangulate | 
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    //cout << scene->mNumMeshes << " meshes found" << endl;
    //cout << scene->mNumMaterials << " materials found" << endl;

    aiMesh *mesh = scene->mMeshes[0];

    out_vertices.clear();
    out_indices.clear();

    for (int i = 0; i < scene->mNumMeshes; i++) {

        aiMesh *mesh = scene->mMeshes[i];
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiString materialName;
        aiString textureFileName;
        std::string textureFilePath;

        //get the material name, return false if it cannot be found
        if (AI_SUCCESS != material->Get(AI_MATKEY_NAME, materialName))
        {
            cout << "ERROR: Mesh " << i << "is not using a material" << endl;
            return false;
        }
        cout << "using material " 
             << mesh->mMaterialIndex 
             << ": " 
             << materialName.C_Str() 
             << endl;

        //get the texture file name contained in the mateial
        //return false if it cannot be found
        if (AI_SUCCESS != material->Get(
                            AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE,0), 
                            textureFileName
                            )
            )
        {
            cout << "ERROR: Mesh " 
                 << i 
                 << "'s material does not contain a texture file name" 
                 << endl;
            return false;
        }
        cout << "using texture: " << textureFileName.C_Str() << endl;

        for (int j = 0; j < mesh->mNumVertices + 1; j++) 
        {
            aiVector3D aiVec = mesh->mVertices[j];
            glm::vec3 vertex = glm::vec3(aiVec.x, aiVec.y, aiVec.z);

            aiVector3D aiUV = mesh->mTextureCoords[0][j];
            glm::vec2 uv;
            uv.x = aiUV.x;
            uv.y = aiUV.y;

            //uncomment to view the texture coordinate for each vertex
            /*
            cout << "using texture coordinates: [" 
                 << uv.x << ", " << uv.y << "]" 
                 << endl;
            //*/

            //create the Vertex type to be pushed
            Vertex *temp = new Vertex(vertex, uv); 
            out_vertices.push_back(*temp);
            delete temp;
        }

        //cout << "Number of faces: " << mesh->mNumFaces << endl;
        for (int j = 0; j < mesh->mNumFaces; j++) 
        {
            aiFace face = mesh->mFaces[j];

            //push each vertex to create the index
            out_indices.push_back(face.mIndices[0]);
            out_indices.push_back(face.mIndices[1]);
            out_indices.push_back(face.mIndices[2]);
        }

        textureFilePath = "..//assets//" + std::string(textureFileName.C_Str());
        if (!m_texture.LoadTexture(textureFilePath))
        {
            return false;
        }

        GLuint VB;
        GLuint IB;

        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), &out_vertices[0], GL_STATIC_DRAW);
        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * out_indices.size(), &out_indices[0], GL_STATIC_DRAW);

        m_IBs.push_back(IB);
        m_VBs.push_back(VB);
        m_numIndices.push_back(out_indices.size());

        out_indices.clear();
        out_vertices.clear();
    }
}

void Model::BindTexture(int index)
{
    m_texture.Bind(GL_TEXTURE0, index);
}

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