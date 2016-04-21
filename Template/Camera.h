#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Shader.h"
#include <glm/glm.hpp>
#include <math.h>

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.01f;
const GLfloat ZOOM = 45.0f;
const GLfloat MOVEMENT_SPEED = 5000.10f;

namespace core
{
	class Engine;
}

class Camera
{
public:
	/*Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw, GLfloat pitch);*/

	Camera();
	Camera(Shader* shader);
	Camera(Shader* shader, glm::vec3 position);
	Camera(Shader* shader, glm::vec3 position, glm::vec3 viewDirection);

	~Camera();
	
	//not sure if necessary
	//void setView(const glm::mat3 &v);
	//void setView(glm::vec3 pos, glm::vec3 camDir, glm::vec3 camUp);

	//void setPosition(glm::vec3 position);
	//void rotate(GLfloat rotation, glm::vec3 axises);

	//void update(float deltaTime);
	//void setShader(Shader *shader);
	//void setProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

	//void move(glm::vec3 direction, float amount);
	//glm::mat4 getModel();
	//glm::mat4 getView();
	//glm::mat4 getProjection();
	//glm::vec3 getUp();
	////
		
	//setters and getters
	void setProjectionMat(GLfloat fov, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlanes);

	//call to update uniforms for view and projection matrixes
	void updateShader();

	//Camera Movement
	void updateView(glm::vec3 camPos, glm::vec3 targetDirection);
	void updateView(glm::vec3 targetDirection);
	void mouseUpdate(const glm::vec2& newMousePosition, GLboolean constrainPitch = true);

	void movementUpdate(const char* input, GLfloat deltaTime);
	void moveForward(GLfloat deltaTime);
	void moveBackward(GLfloat deltaTime);
	void strafeLeft(GLfloat deltaTime);
	void strafeRight(GLfloat deltaTime);
	void moveUp(GLfloat deltaTime);
	void moveDown(GLfloat deltaTime);

	//camera utils
	glm::mat4 getViewMatrix();
	glm::mat4 getViewMat();
	glm::mat4 getProjectionMat();

	glm::vec3& getPosition();

private:
	//
	void updateCameraVectors();
	//camera attributes
	glm::vec3 position,
		up,
		viewDirection,
		front,
		right,
		worldUp;
	//
	
	//Euler Angles
	//GLfloat yaw;
	//GLfloat pitch;

	//camera options
	GLfloat movementSpeed,
		mouseSensitivity,
		zoom,
		nearPlane,
		farPlane,
		fov,
		
		yaw,	//these are for euler angle rotations
		pitch, 

		width,	//get these from the graphic contex
		height;
	//

	//Shader
	Shader *shader;

	glm::mat4 viewMat, projectionMat;
	GLint viewLoc, projLoc;
	//

	//mouse 
	glm::vec2 oldMousePosition;
	//
};
#endif