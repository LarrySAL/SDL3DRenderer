#pragma once
#include <iostream>
#include "vectorTypes.h"



class Matrix4x4 {
private:
    double data[4][4];

public:
    // Constructors
    Matrix4x4();

    Matrix4x4(double initialValues[4][4]);

    // Accessor method to get the value at a specific position
    double getValue(int row, int col) const;

    // Mutator method to set the value at a specific position
    void setValue(int row, int col, double value);

    void printMatrix() const;

    Matrix4x4 operator+(const Matrix4x4& other) const;

    Matrix4x4 operator*(const Matrix4x4& other) const;

    vec3 operator*(const vec3& other) const;

};

class Matrix3x3 {
private:
    double data[4][4];

public:
    // Constructors
    Matrix3x3();

    Matrix3x3(double initialValues[3][3]);

    // Accessor method to get the value at a specific position
    double getValue(int row, int col) const;

    // Mutator method to set the value at a specific position
    void setValue(int row, int col, double value);

    void printMatrix() const;

    Matrix3x3 operator+(const Matrix3x3& other) const;

    Matrix3x3 operator*(const Matrix3x3& other) const;

    vec3 operator*(const vec3& other) const;

    //vec2 operator*(const vec2& other) const;
};