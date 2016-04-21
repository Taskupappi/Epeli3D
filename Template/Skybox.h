#ifndef SKYBOX_H
#define SKYBOX_H
#include "Texture.h"
#include "Shader.h"
#include <string>
#include "Resources.h"
class Skybox
{
/*
	Creates and draws a skybox from 6 images 
	given as x, -x, y, -y, z, -z

	examples: http://ogldev.atspace.co.uk/www/tutorial25/tutorial25.html
	http://www.mbsoftworks.sk/index.php?page=tutorials&series=1&tutorial=13
*/
public:
	Skybox(Resources * res);
	~Skybox();
	void draw();
	bool createSkyBox();
	
private:
	void bindCubeMap(bool bind=true);
	std::string _sides[6];
	GLuint _tex;
	Resources * _res;
	
	GLenum types[]={ GL_TEXTURE_CUBE_MAP_POSITIVE_X,GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
					 GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
					 GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
	const GLchar * sb_fragment =
		"#version 330\n"
		"in vec3 TexCoord0;\n"
		"out vec4 FragColor;\n"
		"uniform samplerCube gCubemapTexture;\n"
		"void main()\n"
		"{\n"
		"FragColor = texture(gCubemapTexture, TexCoord0);\n"
		"}\n";
	const GLchar * sb_vertex =
		"#version 330\n"
		"layout(location = 0) in vec3 Position;\n"
		"uniform mat4 gWVP;\n"
		"out vec3 TexCoord0;\n"
		"void main()\n"
		"{\n"
		"	vec4 WVP_Pos = gWVP * vec4(Position, 1.0);\n"
		"	gl_Position = WVP_Pos.xyww;\n"
		"	TexCoord0 = Position;\n"
		"}\n";
};
void Skybox::draw()
{

}
Skybox::Skybox(Resources * res)
{
	_sides[0] = "xSide.png";
	_sides[1] = "nxSide.png";

	_sides[2] = "ySide.png";
	_sides[3] = "nySide.png";

	_sides[4] = "zSide.png";
	_sides[5] = "nzSide.png";
	_res = res;
}

Skybox::~Skybox()
{
}
bool Skybox::createSkyBox()
{
	glGenTextures(1, &_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);
	Texture * tex = nullptr;
	//_res->loadFile<Texture>("file")
	//Magick::Image* pImage = NULL;
	//Magick::Blob blob;
	//unsigned char * data;
	for(int i = 0; i < 6; i++) 
	{
		tex = _res->loadFile<Texture>(_sides[i]);
		//pImage = new Magick::Image(m_fileNames[i]);
		//glTexImage2D(types[i], 0, GL_RGB, tex->columns(), tex->rows(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex.data());
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return true;
}

void Skybox::bindCubeMap(bool b)
{
	if(b)
		glBindTexture(GL_TEXTURE_CUBE_MAP, _tex);
	else
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return;
}


void Skybox::draw()
{
	/*
	GLuint uiVAO;
	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	vboRenderData.createVBO();
	vboRenderData.bindVBO();
	
	glDepthMask(0);
	glBindVertexArray(uiVAO);
	for(int i = 0, i < 6;i++)
	{
		tTextures[i].bindTexture();
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	glDepthMask(1);
	*/
}
#endif