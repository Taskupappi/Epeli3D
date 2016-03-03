#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

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
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw, GLfloat pitch);
	
	~Camera();

	void init();
	void setPosition(glm::vec3 pos);
	void setScale(GLfloat Scale);
	void setRotation(GLfloat angle);
	void setSize(glm::vec2 size);
	glm::mat4 getViewMatrix();

private:
	//
	void updateCameraVectors();
	//camera attributes
	glm::vec3 pos,
		right, 
		up,
		front,
		targetNeg,
		direction,
		worldUp;

	//Euler Angles
	GLfloat yaw;
	GLfloat pitch;

	//camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat Zoom;

	//GLfloat x, y, z;
	//glm::mat4 modelLoc, viewLoc, projLoc; //, MVP;
	//GLfloat rotation, scale;
	//glm::vec2 size;
};

#endif