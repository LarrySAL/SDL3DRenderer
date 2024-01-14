#include "Mesh.h"


Mesh::Mesh(triangleV inputFacets, vec3 center) {
	triangles.resize(inputFacets.size());
	triangles = inputFacets;
	centerPoint = center;

	normalVectors.resize(triangles.size());

	calculateNormals();

}

vec3 Mesh::getUnitVector(vec3 vec) {
	vec3 result;
	double length = vec.length();

	result.x = vec.x / length;
	result.y = vec.y / length;
	result.z = vec.z / length;
	
	return result;
}

void Mesh::calculateNormals() {
	//make normal vectors that face away from the centerPoint
	int i = 0;
	for (triangle f : triangles) {
		//normalised facet vectors
		vec3 v1 = f[1] - f[0];
		vec3 v2 = f[2] - f[0];
		//initial normal vector
		vec3 N = getUnitVector(v2 / v1);
		//vector from center to point on facet
		vec3 V = f[0] - centerPoint;

		if (N * V < 0) {
			//corrected normal vector to face away from center
			N = -N;
		}
		normalVectors[i] = N;
	}
}

Matrix3x3 Mesh::calculateRotXMatrix(double alphaRad){
	double values[3][3] = {
		{1,0,0},
		{0, std::cos(alphaRad), -std::sin(alphaRad)},
		{0, std::sin(alphaRad), std::cos(alphaRad)},
	};

	return Matrix3x3(values);
}

Matrix3x3 Mesh::calculateRotYMatrix(double alphaRad){
	double values[3][3] = {
		{std::cos(alphaRad), 0, std::sin(alphaRad)},
		{0, 1, 0},
		{-std::sin(alphaRad), 1, std::cos(alphaRad)},
	};

	return Matrix3x3(values);
}

Matrix3x3 Mesh::calculateRotZMatrix(double alphaRad) {
	double values[3][3] = {
		{std::cos(alphaRad), -std::sin(alphaRad), 0},
		{std::sin(alphaRad), std::cos(alphaRad), 0},
		{0, 0, 1}
	};

	return Matrix3x3(values);
}


triangle Mesh::getTriangle(int index) {
	return triangles[index];
}

int Mesh::getMeshSize() {
	return static_cast<int>(triangles.size());
}

void Mesh::setTriangle(int index, triangle t) {
	triangles[index] = t;
}

void Mesh::removeTriangle(int index) {
	triangles.erase(triangles.begin() + index);
}

vec3 Mesh::getNormalOfTriangle(int index) {
	return normalVectors[index];
}

void Mesh::moveMesh(vec3 moveVector) {
	for (int i = 0; i < triangles.size(); i++) {
		for (int j = 0; j < triangles[i].size(); j++) {
			triangles[i][j] = triangles[i][j] + moveVector;
		}
	}
	centerPoint = centerPoint + moveVector;
}

void Mesh::setMesh(vec3 newCenterPos) {
	vec3 moveVector = newCenterPos - centerPoint;
	moveMesh(moveVector);
}

void Mesh::rotateMesh(vec3 angleVec, vec3 rotCent) {

}