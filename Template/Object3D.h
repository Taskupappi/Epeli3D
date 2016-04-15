#ifndef OBJECT3D_H
#define OBJECT3D_H


#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core.h"
#include "Vertex.h"
#include "ResourceBase.h"


//struct Vertex
//{
//	glm::vec3 Position;
//	glm::vec3 Normal;
//	//glm::vec2 TexCoords;
//};

//struct Texture
//{
//	GLuint id;
//	std::string type;
//	aiString path;
//};


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
	~Mesh(){};

	//Data parameters
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	//std::vector<Texture> textures;
};



class Object3D
	: public ResourceBase
{
public:
	Object3D(std::vector<Mesh> model) : ResourceBase(resourcefilepath, nullptr)
	{
		_model = model;
	}
	~Object3D()
	{};

	std::vector<Mesh>& getMeshVec()
	{
		return _model;
	}

	std::vector<Mesh>* loadModel(std::string resourcefilepath)
	{
		//Read file via assimp
		Assimp::Importer importer;
		aiScene const* scene = importer.ReadFile(resourcefilepath, aiProcess_Triangulate | aiProcess_FlipUVs);
		//Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) //if is not zero
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			//return;
		}
		//retrieve the  directory path of the file path
		this->directory = resourcefilepath.substr(0, resourcefilepath.find_last_of('/'));

		//process assimp's root node recursively
		this->processNode(scene->mRootNode, scene);

		std::vector<Mesh>* modelPointer = new std::vector<Mesh>(_model);
		return modelPointer;
	}

	//void Draw(Shader shader)
	//{
	//	for (GLuint i = 0; i < this->meshes.size(); i++)
	//	{
	//		this->meshes[i].Draw(shader);
	//	}
	//}

	std::vector<Mesh> _model;

private:
	
	std::string directory;



	void processNode(aiNode* node, const aiScene* scene)
	{
		//Process each mesh located
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			//The node object only contains indices to index the actual objects in the scene.
			//The scene contains all the data, node is just to keep stuff organized (like relations between nodes)
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->_model.push_back(this->processMesh(mesh, scene));
			//Model* model = (this->processMesh(mesh, scene));
			//return model;
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		//Data to fill
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		//std::vector<Texture> textures;

		//Walk through each of the mesh's vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			//Placeholder vector since assimp uses its own vector class that doesn't directly
			//convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			glm::vec3 vector;
			//Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			//Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			////Texture Coordinates
			//if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			//{
			//	glm::vec2 vec;
			//	//A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			//	//use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			//	vec.x = mesh->mTextureCoords[0][i].x;
			//	vec.y = mesh->mTextureCoords[0][i].y;
			//	vertex.TexCoords = vec;
			//}
			//else
			//{
			//	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			//}
			vertices.push_back(vertex);
		}
		//Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			//Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		//// Process materials
		//if (mesh->mMaterialIndex >= 0)
		//{
		//	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		//	// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		//	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		//	// Same applies to other texture as the following list summarizes:
		//	// Diffuse: texture_diffuseN
		//	// Specular: texture_specularN
		//	// Normal: texture_normalN

		//	// 1. Diffuse maps
		//	std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//	// 2. Specular maps
		//	std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		//	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//}

		// Return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices/*, textures*/);

	}

	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	//{
	//	std::vector<Texture> textures;
	//	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	//	{
	//		aiString str;
	//		mat->GetTexture(type, i, &str);
	//		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
	//		Texture texture;
	//		texture.id = TextureFromFile(str.C_Str(), this->directory);
	//		texture.type = typeName;
	//		texture.path = str;
	//		textures.push_back(texture);
	//	}
	//	return textures;
	//}

};

//ei tarvita
//GLint TextureFromFile(const char* path, std::string directory)
//{
//	//Generate texture ID and load texture data
//	std::string filename = std::string(path);
//	filename = directory + '/' + filename;
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	int width, height;
//	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	//Assign texture to ID
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	
//}


#endif