// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE

	// You will change this return call


	float radians = degrees * pi / 180;
	vec3 normAxis = glm::normalize(axis);

	float oneMinusCos = 1 - cos(radians);
	float mat11 = cos(radians) + (normAxis.x*normAxis.x)*oneMinusCos;
	float mat12 = (normAxis.x*normAxis.y)*oneMinusCos - normAxis.z*sin(radians);
	float mat13 = normAxis.x*normAxis.z*oneMinusCos + (normAxis.y*sin(radians));
	float mat21 = normAxis.y*normAxis.x*oneMinusCos + normAxis.z*sin(radians);
	float mat22 = cos(radians) + normAxis.y*normAxis.y*oneMinusCos;
	float mat23 = normAxis.y*normAxis.z*oneMinusCos - normAxis.x*sin(radians);
	float mat31 = normAxis.z*normAxis.x*oneMinusCos - normAxis.y*sin(radians);
	float mat32 = normAxis.z*normAxis.y*oneMinusCos + normAxis.x*sin(radians);
	float mat33 = cos(radians) + normAxis.z*normAxis.z*oneMinusCos;
	return glm::transpose(mat3(vec3(mat11, mat12, mat13),
		vec3(mat21, mat22, mat23),
		vec3(mat31, mat32, mat33)
	));
}

void Transform::left(float degrees, vec3& eye, vec3& up) {

	//float radians = degrees*pi/180;

	//test rotate around y
	//    mat3 rotMatxY = glm::transpose(mat3(vec3(cos(radians),0,sin(radians)),
	//                         vec3(0,1,0),
	//                         vec3(-sin(radians),0,cos(radians))));

	mat3 rotationMx = rotate(degrees, up);
	eye = rotationMx * eye; // == r^t * eye => T => eye^t * r = 1x3 * 3x3
	up = rotationMx * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 w = glm::cross(up, eye);
	mat3 rotationMx = rotate(-degrees, w);

	eye = rotationMx * eye;
	up = rotationMx * up;
}
mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 z = (normalize(eye - center));
	vec3 x = glm::normalize(glm::cross(up, z));
	vec3 y = glm::cross(z, x);

	mat4 Result;
	Result[0] = vec4(x, 0);
	Result[1] = vec4(y, 0);
	Result[2] = vec4(z, 0);
	Result[3] = vec4(eye, 1);

	Result = glm::inverse(Result);
	return Result;
}
// Project from 3D to 2D screen
mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	fovy = glm::radians(fovy);
	float a = 1 / tan(fovy / 2);
	float b = a / aspect;
	float c = -(zFar + zNear) / (zFar - zNear);
	float d = (-2 * zNear * zFar) / (zFar - zNear);
	ret[0] = vec4(b, 0, 0, 0);
	ret[1] = vec4(0, a, 0, 0);
	ret[2] = vec4(0, 0, c, d);
	ret[3] = vec4(0, 0, -1, 0);
	ret = glm::transpose(ret);
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement scaling 
	ret[0] = vec4(sx, 0, 0, 0);
	ret[1] = vec4(0, sy, 0, 0);
	ret[2] = vec4(0, 0, sz, 0);
	ret[3] = vec4(0, 0, 0, 1);
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	ret[0] = vec4(1, 0, 0, 0);
	ret[1] = vec4(0, 1, 0, 0);
	ret[2] = vec4(0, 0, 1, 0);
	ret[3] = vec4(tx, ty, tz, 1);
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
