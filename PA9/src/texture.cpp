//
// Created by mari on 10/3/18.
//
#include "texture.h"

Texture::Texture()
{
	//m_image = new Magick::Image(filename);
}

Texture::~Texture()
{

}

bool Texture::LoadTexture(string filename)
{

	Magick::Image* image;
	GLuint TB;

	try
	{
		image = new Magick::Image(filename);
	}
	catch (Magick::Error& error)
	{
		cout << "ERROR: Could not load texture '" 
			 << filename << "': " << error.what()
			 << endl;
		return false;
	}

	//image->flip();
	image->write(&m_blob, "RGBA");

	glGenTextures(1, &TB);
	glBindTexture(GL_TEXTURE_2D, TB);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image->columns(),
		image->rows(),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		m_blob.data());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_TBs.push_back(TB);

	delete image;

	return true;
}

void Texture::Bind(GLenum TextureUnit, int BufferIndex)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_TBs[BufferIndex]);
}