#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) :viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(glm::vec3 position) :viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->position = position;
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
	this->yaw = YAW;
	this->pitch = PITCH;
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : viewDirection(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->position = glm::vec3(posX, posY, posZ);
	this->worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera()
{
	this->position = glm::vec3(0.0f, 0.0f, -10.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = YAW;
	this->pitch = PITCH;
	this->updateCameraVectors();
}

Camera::~Camera()
{

}

void Camera::updateCameraVectors()
{
	//calculate new front vector
	glm::vec3 viewDirection;
	viewDirection.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	viewDirection.y = sin(glm::radians(this->pitch));
	viewDirection.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->viewDirection = glm::normalize(viewDirection);

	//Re-calculate the right and up vector
	this->right = glm::normalize(glm::cross(this->viewDirection, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->viewDirection));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->viewDirection, this->up);
}

void Camera::update(float deltaTime)
{
	// Get uniform locations
	GLint modelLoc = glGetUniformLocation(shader->getShaderProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader->getShaderProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader->getShaderProgram(), "projection");

	// Pass uniform locations to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//updateCameraVectors();
}

void Camera::setShader(Shader *shader)
{
	this->shader = shader;
}

void Camera::setView(const glm::mat3 &v)
{
	glm::vec3 xAxis = glm::vec3(v[0][0], v[0][1], v[0][2]);
	glm::vec3 yAxis = glm::vec3(v[1][0], v[1][1], v[1][2]);
	glm::vec3 zAxis = glm::vec3(v[2][0], v[2][1], v[2][2]);
	view = glm::lookAt(xAxis, yAxis, zAxis);
}

void Camera::setView(glm::vec3 position, glm::vec3 camDir, glm::vec3 camUp)
{
	view = glm::lookAt(position, camDir, camUp);
	updateCameraVectors();
}

void Camera::setPosition(glm::vec3 position)
{
	model = glm::translate(model, position);
	updateCameraVectors();
}

void Camera::rotate(GLfloat rotation, glm::vec3 axis)
{
	model = glm::rotate(model, rotation, axis);
	updateCameraVectors();
}

void Camera::setProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
{
	projection = glm::perspective(fov, aspect, near, far);
	updateCameraVectors();
}

void init()
{

}

glm::mat4 Camera::getModel()
{
	return model;
}

glm::mat4 Camera::getView()
{
	return view;
}

glm::mat4 Camera::getProjection()
{
	return projection;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getUp()
{
	return up;
}

void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	viewDirection = glm::mat3(glm::rotate(mouseDelta.x, up)) * viewDirection;
	oldMousePosition = newMousePosition;
	//std::cout << "mouseUpdate" << std::endl;
}



//void Camera::init()
//{
//
//}
//
//
//void Camera::setRotation()
//{
//
//}
//
//void Camera::setpositionition(glm::vec3 position)
//{
//	modelLoc = glm::translate(modelLoc, glm::vec3(position.x, -position.y, position.z));
//}
//
//void Camera::setScale(GLfloat scale)
//{
//	modelLoc = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
//}
//
//void Camera::setRotation(GLfloat angle)
//{
//	modelLoc = glm::rotate(modelLoc, angle, glm::vec3(0.0f, 0.0f, angle));
//}
//
//void Camera::setSize(glm::vec3 s)
//{
//	glm::vec3 size = s;
//	viewLoc = glm::ortho(size.x, size.y, size.z, 0.0f);
//}
//
//void Camera::init()
//{
//	//glm::vec3 Xaxis(camX, 0.0, 0.0);
//	//glm::vec3 Yaxis(0.0, camY, 0.0);
//	//glm::vec3 Zaxis(0.0, 0.0, camZ);
//
//	//position = glm::vec3(0.0f, 0.0f, 0.0f);
//	//up = yAxis;
//	//right = xAxis;
//	//front = -zAxis;
//
//	projLoc = lookAt(position, position + front, up);
//	viewLoc = glm::ortho(0.0f, size.x, size.y, 0.0f);
//}
//
//Camera::Camera(glm::vec2 s)
//{
//	x = 1.0f;
//	y = 1.0f;
//	z = 1.0f;
//	size = s;
//}
//
//Camera::Camera()
//{
//	x = 1.0f;
//	y = 1.0f;
//	z = 1.0f;
//	size = glm::vec2(1,1);
//	position = glm::vec3(0.0f, 0.0f, 3.0f);
//	targetNeg = glm::vec3(0.0f, 0.0f, 0.0f);
//	direction = glm::normalize(position - targetNeg);
//}
