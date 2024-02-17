#pragma once

#include "Matrix4x4.h"

class Mesh{

private:
	//clockwise point connections
	triangleV triangles;
	vec3 centerPoint;
	std::vector<vec3> normalVectors;
	
	void calculateNormals();

	Matrix3x3 calculateRotXMatrix(double alphaRad);
	Matrix3x3 calculateRotYMatrix(double alphaRad);
	Matrix3x3 calculateRotZMatrix(double alphaRad);

public:
	Mesh(triangleV inputFacets, vec3 center);

	triangle getTriangle(int index);

	int getMeshSize();

	void setTriangle(int index, triangle t);

	void removeTriangle(int index);

	vec3 getNormalOfTriangle(int index);

	//void printNormals();

	vec3 getCenter();

	void moveMesh(vec3 moveVector);

	void setMesh(vec3 newCenterPos);

	void rotateMesh(vec3 angleVec, vec3 rotCent);
};

