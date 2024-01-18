#pragma once
#include <cmath>
#include <vector>

//4D vector type for describing points in 3d space
typedef struct vec3{
	double x = 0, y = 0, z = 0;

	vec3() : x(0), y(0), z(0){}

	vec3(double ix, double iy, double iz){
		x = ix;
		y = iy;
		z = iz;
	}

	double length() {
		return std::sqrt(x * x + y * y + z * z);
	}

	vec3 unit() {
		vec3 result;
		double len = length();

		result.x = x / len;
		result.y = y / len;
		result.z = z / len;

		return result;
	}

	vec3 operator+(const vec3& other) const {
		vec3 result;
		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;
		return result;
	}

	vec3 operator-(const vec3& other) const {
		vec3 result;
		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;
		return result;
	}
	
	vec3 operator-() {
		vec3 result;

		result.x = x != 0 ? -x : x;
		result.y = y != 0 ? -y : y;
		result.z = z != 0 ? -z : z;

		return result;
	}

	double operator* (const vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	//cross product
	vec3 operator/ (const vec3& other) const {
		vec3 result;
		result.x = y * other.z - z * other.y;
		result.y = z * other.x - x * other.z;
		result.z = x * other.y - y * other.x;
		return result;
	}

	void operator+= (const vec3& other) {
		
		this->x += this->x + other.x;
		this->y += this->y + other.y;
		this->z += this->z + other.z;
		
	}

} vec3;

//3D Vector for 2D screen coordinates
typedef struct vec2{
	int x = 0, y = 0;

	vec2() : x(0), y(0){}

	vec2(int ix, int iy){
		x = ix;
		y = iy;
	}

	double length() {
		return std::sqrt(x * x + y * y);
	}

	vec2 operator+(const vec2& other) const {
		vec2 result;
		result.x = x + other.x;
		result.y = y + other.y;
		return result;
	}

	vec2 operator-(const vec2& other) const {
		vec2 result;
		result.x = x - other.x;
		result.y = y - other.y;
		return result;
	}

	vec2 operator-() {
		vec2 result;

		result.x = x != 0 ? -x : x;
		result.y = y != 0 ? -y : y;

		return result;
	}

	double operator* (const vec2& other) const {
		return x * other.x + y * other.y;
	}

}vec2;

//should have 3 vertecis inside
typedef std::vector<vec3> triangle;

typedef std::vector<vec2> triangProj;

typedef std::vector<triangle> triangleV;

typedef std::vector<triangProj> triangleProjV;



