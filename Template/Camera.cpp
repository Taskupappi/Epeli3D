#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up , GLfloat yaw, GLfloat pitch) :front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->pos = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera() :front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->pos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->targetNeg = glm::vec3(0.0f, 0.0f, 0.0f);
	this->yaw = YAW;
	this->pitch = PITCH;
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	this->pos = glm::vec3(posX, posY, posZ);
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

//Camera::Camera(glm::vec2 s)
//{
//	x = 1.0f;
//	y = 1.0f;
//	z = 1.0f;
//	size = s;
//}

//Camera::Camera()
//{
//	x = 1.0f;
//	y = 1.0f;
//	z = 1.0f;
//	size = glm::vec2(1,1);
//	pos = glm::vec3(0.0f, 0.0f, 3.0f);
//	targetNeg = glm::vec3(0.0f, 0.0f, 0.0f);
//	direction = glm::normalize(pos - targetNeg);
//}

Camera::~Camera()
{

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
	//this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	//this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->pos, this->pos + this->front, this->up);
	/*MVP = modelLoc * viewLoc * projLoc;
	return MVP;*/
}

void Camera::setPosition(glm::vec3 pos)
{
	//modelLoc = glm::translate(modelLoc, glm::vec3(pos.x, -pos.y, pos.z));
}

void Camera::setScale(GLfloat scale)
{
	//modelLoc = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}

void Camera::setRotation(GLfloat angle)
{
	//modelLoc = glm::rotate(modelLoc, angle, glm::vec3(0.0f, 0.0f, angle));
}

void Camera::setSize(glm::vec2 s)
{
	//size = s;
	//viewLoc = glm::ortho(0.0f, size.x, size.y, 0.0f);
}

void Camera::init()
{
	//glm::vec3 xAxis(x, 0, 0);
	//glm::vec3 yAxis(0, y, 0);
	//glm::vec3 zAxis(0, 0, z);

	//pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//up = yAxis;
	//right = xAxis;
	//front = -zAxis;

	//projLoc = lookAt(pos, pos + front, up);
	//viewLoc = glm::ortho(0.0f, size.x, size.y, 0.0f);
}
