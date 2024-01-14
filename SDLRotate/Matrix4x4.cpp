#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(){
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			data[i][j] = 0.0f;
}

Matrix4x4::Matrix4x4(double initialValues[4][4]){
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			data[i][j] = initialValues[i][j];
}

double Matrix4x4::getValue(int row, int col) const{
	return data[row][col];
}

void Matrix4x4::setValue(int row, int col, double value){
	data[row][col] = value;
}

void Matrix4x4::printMatrix() const{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result.data[i][j] = data[i][j] + other.data[i][j];
	return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				result.data[i][j] += data[i][k] * other.data[k][j];
	return result;
}

vec3 Matrix4x4::operator*(const vec3& other) const{

	std::vector<double> preresult;
	preresult.resize(4);

	double w = 1;

	for (int i = 0; i < 4; i++) {
		preresult[i] = other.x * data[i][0] + other.y * data[i][1] + other.z * data[i][2] + w * data[i][3];
	}

	vec3 result(preresult[0], preresult[1], preresult[2]);

	//divide by z that 
	if (preresult[3] != 0.0) {
		result.x /= preresult[3];
		result.y /= preresult[3];
		result.z /= preresult[3];
	}
	return result;
}


//----------------------------Matrix3x3-----------------------//

Matrix3x3::Matrix3x3() {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = 0.0f;
}

Matrix3x3::Matrix3x3(double initialValues[3][3]) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = initialValues[i][j];
}

double Matrix3x3::getValue(int row, int col) const {
	if (row <= 3 && col <= 3) {
		return data[row][col];
	}
	return 0;
}

void Matrix3x3::setValue(int row, int col, double value) {
	if (row <= 3 && col <= 3) {
		data[row][col] = value;
	}
}

void Matrix3x3::printMatrix() const {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			result.data[i][j] = data[i][j] + other.data[i][j];
	return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
	Matrix3x3 result;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				result.data[i][j] += data[i][k] * other.data[k][j];
	return result;
}

vec3 Matrix3x3::operator*(const vec3& other) const{

	std::vector<double> preresult;
	preresult.resize(3);

	for (int i = 0; i < 3; i++) {
		preresult[i] = other.x * data[i][0] + other.y * data[i][1] + other.z * data[i][2];
	}

	return vec3(preresult[0], preresult[1], preresult[2]);
}

//vec2 Matrix3x3::operator*(const vec2& other) const {
//
//	std::vector<double> preresult;
//	preresult.resize(3);
//
//	double w = 1;
//
//	for (int i = 0; i < 3; i++) {
//		preresult[i] = other.x * data[i][0] + other.y * data[i][1] + w * data[i][3];
//	}
//
//	vec2 result(preresult[0], preresult[1]);
//
//	//divide by z that 
//	if (preresult[3] != 0.0) {
//		result.x /= preresult[2];
//		result.y /= preresult[2];
//	}
//	return result;
//}