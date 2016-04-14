#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Shader.h"
#include <glm\gtx\transform.hpp>

enum Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw, GLfloat pitch);

	~Camera();

	glm::mat4 getViewMatrix();
	void setView(const glm::mat3 &v);
	void setView(glm::vec3 pos, glm::vec3 camDir, glm::vec3 camUp);

	void setPosition(glm::vec3 position);
	void rotate(GLfloat rotation, glm::vec3 axises);

	void update(float deltaTime);
	void setShader(Shader *shader);
	void setProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

	glm::mat4 getModel();
	glm::mat4 getView();
	glm::mat4 getProjection();

	glm::vec3 getPosition();
	glm::vec3 getUp();

	//void init();
	void mouseUpdate(const glm::vec2& newMousePosition);

	//void setPosition(glm::vec3 pos);
	//void setScale(GLfloat Scale);
	//void setRotation(GLfloat angle);
	//void setSize(glm::vec2 size);


private:
	//
	void updateCameraVectors();
	//camera attributes
	glm::vec3 position,
		right,
		up,
		viewDirection,
		lookAt,
		direction,
		worldUp;

	//Euler Angles
	GLfloat yaw;
	GLfloat pitch;

	//camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat Zoom;

	glm::mat4 view, projection, model;

	Shader *shader;
	//GLfloat x, y, z;
	//glm::mat4 modelLoc, viewLoc, projLoc; //, MVP;
	//GLfloat rotation, scale;
	//glm::vec2 size;

	//mouse

	glm::vec2 oldMousePosition;
	//
};

#endif