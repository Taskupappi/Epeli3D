#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
//debug
#include <iostream>

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
	Camera(GLfloat ScreenWidth, GLfloat ScreenHeight);
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw, GLfloat pitch);

	~Camera();
	//movement mouse
	void mouseUpdate(const glm::vec2 newMousePosition);

	//initialize camera
	void initDefault(Shader* shader);

	//movement keyboard
	void move(const char* input, const GLfloat deltaTime);
	void moveForward(const GLfloat deltaTime);
	void moveBackward(const GLfloat deltaTime);
	void strafeLeft(const GLfloat deltaTime);
	void strafeRight(const GLfloat deltaTime);
	void moveUp(const GLfloat deltaTime);
	void moveDown(const GLfloat deltaTime);

	//screen dimensions for projection Matrix
	void setScreenDimension(GLfloat ScreenWidth, GLfloat ScreenHeight);

	void setViewUniformLocation(Shader *shader);
	void setProjectionUniformLocation(Shader *shader);
	void setModelUniformLocation(Shader *shader);

	glm::mat4 getModelMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setDefaultModelMatrix();


	glm::mat4 viewMatrix,
		projectionMatrix,
		modelMatrix;

private:

	void updateCameraVectors();

	//camera attributes
	glm::vec3 position,
		front,
		right,
		up,
		worldUp;

	//Euler Angles
	GLfloat yaw;
	GLfloat pitch;

	//camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat Zoom;

	GLfloat fov;

	//Screen Dimensions
	GLfloat ScreenWidth,
		ScreenHeight;

	glm::vec2 oldMousePosition;
	bool firstClick;

	GLint modelLocation,
		viewLocation,
		projectionLocation;
};








//#include <glm/glm.hpp>
//
//class Camera
//{
//	glm::vec3 position;
//	glm::vec3 viewDirection;
//	const glm::vec3 up;
//	glm::vec2 oldMousePosition;
//
//public:
//	Camera();
//	~Camera();
//
//	glm::mat4 getWorldToViewMat() const;
//	void mouseUpdate(const glm::vec2& newMousePosition);
//
//private:
//};

#endif


















//#ifndef CAMERA_H
//#define CAMERA_H
//
////#include <GL/glew.h>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/glm.hpp>
//#include <glm\gtc\type_ptr.hpp>
//#include "Shader.h"
//////#include <math.h>
//
//// Default camera values
//const GLfloat YAW = -90.0f;
//const GLfloat PITCH = 0.0f;
//const GLfloat SPEED = 3.0f;
//const GLfloat SENSITIVITY = 0.01f;
//const GLfloat ZOOM = 45.0f;
//const GLfloat MOVEMENT_SPEED = 5.10f;
//
//namespace core
//{
//	class Engine;
//}
//
//class Camera
//{
//public:
//	/*Camera();
//	Camera(glm::vec3 position);
//	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
//	Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
//		GLfloat upX, GLfloat upY, GLfloat upZ,
//		GLfloat yaw, GLfloat pitch);*/
//
//	Camera();
//	Camera(Shader* shader);
//	Camera(Shader* shader, glm::vec3 position);
//	Camera(Shader* shader, glm::vec3 position, glm::vec3 viewDirection);
//
//	~Camera();
//	
//	//not sure if necessary
//	//void setView(const glm::mat3 &v);
//	//void setView(glm::vec3 pos, glm::vec3 camDir, glm::vec3 camUp);
//
//	//void setPosition(glm::vec3 position);
//	//void rotate(GLfloat rotation, glm::vec3 axises);
//
//	//void update(float deltaTime);
//	//void setShader(Shader *shader);
//	//void setProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
//
//	//void move(glm::vec3 direction, float amount);
//	//glm::mat4 getModel();
//	//glm::mat4 getView();
//	//glm::mat4 getProjection();
//	//glm::vec3 getUp();
//	////
//		
//	//setters and getters
//	void setProjectionMat(GLfloat fov, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlanes);
//
//	//call to update uniforms for view and projection matrixes
//	void updateShader();
//
//	//Camera Movement
//	void updateView(glm::vec3 camPos, glm::vec3 targetDirection);
//	void updateView(glm::vec3 targetDirection);
//	void mouseUpdate(const glm::vec2& newMousePosition);
//
//	void movementUpdate(const char* input, GLfloat deltaTime);
//	void moveForward(GLfloat deltaTime);
//	void moveBackward(GLfloat deltaTime);
//	void strafeLeft(GLfloat deltaTime);
//	void strafeRight(GLfloat deltaTime);
//	void moveUp(GLfloat deltaTime);
//	void moveDown(GLfloat deltaTime);
//
//	//camera utils
//	glm::mat4 getViewMatrix() const;
//	glm::mat4 getViewMat();
//	glm::mat4 getProjectionMat();
//
//	glm::vec3 getPosition() const { return position; };
//
//private:
//	//
//	void updateCameraVectors();
//	//camera attributes
//	glm::vec3 position,
//		up,
//		viewDirection,
//		strafeDirection;
//		//front,
//		//right,
//		//worldUp;
//	//
//
//	//mouse 
//	glm::vec2 oldMousePosition;
//	//
//	
//	//Euler Angles
//	//GLfloat yaw;
//	//GLfloat pitch;
//
//	//camera options
//	GLfloat movementSpeed,
//	//	mouseSensitivity,
//	//	zoom,
//		nearPlane,
//		farPlane,
//		fov,
//	//	
//	//	yaw,	//these are for euler angle rotations
//	//	pitch, 
//
//		width,	//get these from the graphic contex
//		height;
//	//
//
//	//Shader
//	Shader *shader;
//
//	glm::mat4 viewMat, projectionMat;
//	GLint viewLoc, projLoc;
//	//
//
//
//};
//#endif