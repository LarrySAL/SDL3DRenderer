#pragma once

#include <SDL.h>
#include <cmath>
#include "Matrix4x4.h"
#include "Mesh.h"


class Screen{
private:
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int screenWidth;
	int screenHeight;

	vec3 CameraCoord;

	Matrix4x4 calculatePrjctMatrix(int screenW, int screenH, double zNear, double zFar, double fov);

public:
	Matrix4x4 projMatrix;

	Screen(int w, int h, int scale=1);

	void clear();

	void show();

	void input();

	int getScreenWidth();

	int getScreenHeight();

	void pixel(int x, int y);

	void line(int x1, int y1, int x2, int y2);

	void dotedLine(int x1, int y1, int x2, int y2, int spaceSize);

	void drawTriangle(triangProj t);

	void meshToScreen(Mesh mesh);

};

