//
// Created by mari on 10/2/18.
//
#ifndef TUTORIAL_MODEL_H
#define TUTORIAL_MODEL_H


#include <vector>
#include <string>
#include "graphics_headers.h"
#include "texture.h"
#include <btBulletDynamicsCommon.h>

using namespace std;

class Model {
public:
    Model();
    ~Model();

    bool LoadObject(void);
    bool LoadObject(string in_filename);
    bool LoadObject(string in_filename, btTriangleMesh *triMesh, float scale);

    //void Render();
    void BindTexture(int index);

    vector<GLuint> get_VBs(void);
    vector<GLuint> get_IBs(void);
    vector<unsigned int> get_numIndices(void);

    void set_VBs(vector<GLuint> VBs);
    void set_IBs(vector<GLuint> IBs);
    void set_numIndices(vector<GLuint> numIndices);

private:
    Texture m_texture;

    vector<GLuint> m_VBs;
    vector<GLuint> m_IBs;
    vector<unsigned int> m_numIndices;

	
    GLuint VB;
    GLuint IB;	
    //GLuint m_normal;

};
#endif //TUTORIAL_MODEL_H
