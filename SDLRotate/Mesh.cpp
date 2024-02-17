#include "Mesh.h"


Mesh::Mesh(triangleV inputFacets, vec3 center) {
	triangles.resize(inputFacets.size());
	triangles = inputFacets;
	centerPoint = center;

	normalVectors.resize(triangles.size());

	calculateNormals();

}

void Mesh::calculateNormals() {
	//make normal vectors that face away from the centerPoint
	int i = 0;
	for (triangle f : triangles) {
		//normalised facet vectors
		vec3 v1 = f[1] - f[0];
		vec3 v2 = f[2] - f[0];
		//initial normal vector
		vec3 N = (v2 / v1).unit();
		//vector from center to point on facet
		vec3 V = f[0] - centerPoint;

		if (N * V < 0) {
			//corrected normal vector to face away from center
			N = -N;
		}
		normalVectors[i] = N;
		i++;
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
		{-std::sin(alphaRad), 0, std::cos(alphaRad)},
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

//void Mesh::printNormals(){
//	for(const vec3 n : normalVectors){
//		std::cout << n.x << " " << n.y << " " << n.z << std::endl;
//	}
//}

vec3 Mesh::getCenter()
{
	return centerPoint;
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
	vec3 centerToVertex;
	//create vector from rotation center to the vertex that is to be moved, rotate vector, save vector + rotation center origin vector as our new vertex position
	for (int i = 0; i < triangles.size(); i++) {
		for (int j = 0; j < 3; j++) {
			centerToVertex = triangles[i][j] - rotCent;
			triangles[i][j] = rotCent + calculateRotXMatrix(angleVec.x) * centerToVertex;
			centerToVertex = triangles[i][j] - rotCent;
			triangles[i][j] = rotCent + calculateRotYMatrix(angleVec.y) * centerToVertex;
			centerToVertex = triangles[i][j] - rotCent;
			triangles[i][j] = rotCent + calculateRotZMatrix(angleVec.z) * centerToVertex;
		}
	}
	//rotation to centerpoint
	centerToVertex = centerPoint - rotCent;
	centerPoint = rotCent + calculateRotXMatrix(angleVec.x) * centerToVertex;
	centerToVertex = centerPoint - rotCent;
	centerPoint = rotCent + calculateRotYMatrix(angleVec.y) * centerToVertex;
	centerToVertex = centerPoint - rotCent;
	centerPoint = rotCent + calculateRotZMatrix(angleVec.z) * centerToVertex;
	calculateNormals();
}