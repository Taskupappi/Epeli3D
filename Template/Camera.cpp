#include "Camera.h"
#include <glm\gtx\transform.hpp>

//Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//{
//	this->position = position;
//	this->up = up;
//	this->viewDirection()
//	//this->yaw = yaw;
//	//this->pitch = pitch;
//	//this->updateCameraVectors();
//}
//
//Camera::Camera(glm::vec3 position) :viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//{
//	this->position = position;
//	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
//	//this->lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
//	//this->yaw = YAW;
//	//this->pitch = PITCH;
//	//this->updateCameraVectors();
//}
//
//Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//{
//	this->position = glm::vec3(posX, posY, posZ);
//	this->up = glm::vec3(upX, upY, upZ);
//	//this->yaw = yaw;
//	//this->pitch = pitch;
//	//this->updateCameraVectors();
//}
//
//Camera::Camera()
//{
//	this->position = glm::vec3(0.0f, 0.0f, -1.0f);
//	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
//	//this->yaw = YAW;
//	//this->pitch = PITCH;
//	//this->updateCameraVectors();
//}


Camera::Camera()
	:viewDirection(glm::vec3(0.0f, 0.0f, 0.0f)),
	position(glm::vec3(0.0f, 0.0f, 10.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	nearPlane(0.0f),
	farPlane(0.0f),
	fov(95),
	movementSpeed(MOVEMENT_SPEED),
	mouseSensitivity(SENSITIVITY)
{
}

Camera::Camera(Shader* shader)
	:viewDirection(glm::vec3(0.0f, 0.0f, 0.0f)),
	position(glm::vec3(0.0f, 0.0f, 10.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	nearPlane(0.0f),
	farPlane(0.0f),
	fov(95),
	movementSpeed(MOVEMENT_SPEED),
	mouseSensitivity(SENSITIVITY),
	worldUp(up),
	yaw(YAW),
	pitch(PITCH),
	shader(shader)
{
}

Camera::Camera(Shader* shader, glm::vec3 position)
		:viewDirection(glm::vec3(0.0f, 0.0f, 0.0f)),
		position(position),
		up(glm::vec3(0.0f, 1.0f, 0.0f)),
		nearPlane(0.0f),
		farPlane(0.0f),
		fov(95),
		movementSpeed(MOVEMENT_SPEED),
		mouseSensitivity(SENSITIVITY),
		worldUp(up),
		yaw(YAW),
		pitch(PITCH),
		shader(shader)
{	
}

Camera::Camera(Shader* shader, glm::vec3 position, glm::vec3 viewDirection)
	:viewDirection(viewDirection),
	position(position),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	nearPlane(0.0f),
	farPlane(0.0f),
	fov(95),
	movementSpeed(MOVEMENT_SPEED),
	mouseSensitivity(SENSITIVITY),
	worldUp(up),
	yaw(YAW),
	pitch(PITCH),
	shader(shader)
{
}

Camera::~Camera()
{
	delete shader;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->viewDirection, this->up);
}

void Camera::setProjectionMat(GLfloat fov, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane)
{
	projectionMat = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::updateShader()
{
	shader->use();

	//these are for shader

	viewMat = getViewMatrix();
	projectionMat = glm::perspective(fov, (GLfloat)width / (GLfloat)height, nearPlane, farPlane);

	//Uniform locations
	viewLoc = glGetUniformLocation(shader->getShaderProgram(), "view");
	projLoc = glGetUniformLocation(shader->getShaderProgram(), "projection");

	//passing to shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

}

void Camera::updateView(glm::vec3 camPos, glm::vec3 targetDirection)
{
	position = camPos;
	viewDirection = targetDirection;
	viewMat = glm::lookAt(this->position, this->position + this->viewDirection, this->up);
}

void Camera::updateView(glm::vec3 targetDirection)
{
	viewDirection = targetDirection;
	viewMat = glm::lookAt(this->position, this->position + this->viewDirection, this->up);
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition, GLboolean constrainPitch)
{
	GLfloat offsetX = newMousePosition.x;
	GLfloat offsetY = newMousePosition.y;
	offsetX *= this->mouseSensitivity;
	offsetY *= this->mouseSensitivity;
	
	this->yaw += offsetX;
	this->pitch += offsetY;

	if (constrainPitch)
	{
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->yaw > 89.0f)
			this->yaw = 89.0f;
	}

	this->updateCameraVectors();

	////mouse rotation
	//glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	//if (glm::length(mouseDelta) > 50.0f)
	//{
	//	oldMousePosition = newMousePosition;
	//}
	//else
	//{
	//	glm::vec3 toRotateAround = glm::cross(viewDirection, up);
	//	glm::mat4 rotator = glm::mat4(glm::rotate(mouseDelta.x * SENSITIVITY, up) *
	//		glm::rotate(mouseDelta.y * SENSITIVITY, toRotateAround));
	//	
	//	viewDirection = glm::mat3(rotator) * viewDirection;
	//

	//	oldMousePosition = newMousePosition;
		//updateCameraVectors();
	//}
}

void Camera::updateCameraVectors()
{
	//calculate new front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);

	//Re-calculate the right and up vector
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

	//glm::lookAt(this->position, this->position + this->viewDirection, this->up);
}

void Camera::movementUpdate(const char* input , GLfloat deltaTime)
{
	//WASD movement with zoom in and out
	switch (*input)
	{
	case 'W':
	case 'w':
		moveForward(deltaTime);
		break;
	case 'S':
	case 's':
		moveBackward(deltaTime);
		break;
	case 'A':
	case 'a':
		strafeLeft(deltaTime);
		break;
	case 'D':
	case 'd':
		strafeRight(deltaTime);
		break;
	case 'Q':
	case'q':
		moveUp(deltaTime);
		break;
	case 'E':
	case 'e':
		moveDown(deltaTime);
		break;
	default:
		break;
	}
}

void Camera::moveForward(GLfloat deltaTime)
{
	position += movementSpeed * viewDirection * deltaTime;
}

void Camera::moveBackward(GLfloat deltaTime)
{
	position -= movementSpeed * viewDirection * deltaTime;
}

void Camera::strafeLeft(GLfloat deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, up);
	position += movementSpeed * strafeDirection * deltaTime;
}

void Camera::strafeRight(GLfloat deltaTime)
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, up);
	position -= movementSpeed * strafeDirection * deltaTime;
}

void Camera::moveUp(GLfloat deltaTime)
{
	position += movementSpeed * up * deltaTime;
}

void Camera::moveDown(GLfloat deltaTime)
{
	position -= movementSpeed * up * deltaTime;
}

glm::mat4 Camera::getViewMat()
{
	return viewMat;
}

glm::mat4 Camera::getProjectionMat()
{
	return projectionMat;
}

glm::vec3& Camera::getPosition()
{
<<<<<<< HEAD
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
	}
	else
	{
		view = glm::rotate(mouseDelta.x * 0.01f, up) * view;
		//view = glm::rotate(mouseDelta.y * 0.01f, glm::cross(up,))
		oldMousePosition = newMousePosition;
		updateCameraVectors();
	}

	//std::cout << "mouseUpdate" << std::endl;
=======
	return position;
>>>>>>> refs/remotes/origin/master
}


//void Camera::update(float deltaTime)
//{
//	// Get uniform locations
//	GLint modelLoc = glGetUniformLocation(shader->getShaderProgram(), "model");
//	GLint viewLoc = glGetUniformLocation(shader->getShaderProgram(), "view");
//	GLint projLoc = glGetUniformLocation(shader->getShaderProgram(), "projection");
//
//	// Pass uniform locations to the shaders
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//	//updateCameraVectors();
//}

//void Camera::setShader(Shader *shader)
//{
//	this->shader = shader;
//}
//
//void Camera::setView(const glm::mat3 &v)
//{
//	glm::vec3 xAxis = glm::vec3(v[0][0], v[0][1], v[0][2]);
//	glm::vec3 yAxis = glm::vec3(v[1][0], v[1][1], v[1][2]);
//	glm::vec3 zAxis = glm::vec3(v[2][0], v[2][1], v[2][2]);
//	view = glm::lookAt(xAxis, yAxis, zAxis);
//}
//
//void Camera::setView(glm::vec3 position, glm::vec3 camDir, glm::vec3 camUp)
//{
//	view = glm::lookAt(position, camDir, camUp);
//	updateCameraVectors();
//}
//
//void Camera::setPosition(glm::vec3 position)
//{
//	model = glm::translate(model, position);
//	updateCameraVectors();
//}
//
//void Camera::rotate(GLfloat rotation, glm::vec3 axis)
//{
//	model = glm::rotate(model, rotation, axis);
//	updateCameraVectors();
//}
//
//void Camera::setProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
//{
//	projection = glm::perspective(fov, aspect, near, far);
//	updateCameraVectors();
//}
//
//void Camera::move(glm::vec3 direction, float amount)
//{
//	position += direction * amount;
//}
//
//void init()
//{
//
//}

//glm::mat4 Camera::getModel()
//{
//	return model;
//}
//
//glm::mat4 Camera::getView()
//{
//	return view;
//}
//
//glm::mat4 Camera::getProjection()
//{
//	return projection;
//}
//
//glm::vec3 Camera::getPosition()
//{
//	return position;
//}
//
//glm::vec3 Camera::getUp()
//{
//	return up;
//}
