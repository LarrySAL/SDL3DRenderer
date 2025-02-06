#pragma once

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
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

	vec3 lightDir;

	Matrix4x4 calculatePrjctMatrix(int screenW, int screenH, double zNear, double zFar, double fov);

	bool stop;

public:
	Matrix4x4 projMatrix;

	Screen(int w, int h, int scale=1);

	void clear();

	void show();

	void input();

	bool stopLoop();

	int getScreenWidth();

	int getScreenHeight();

	void pixel(double x, double y, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void pixel(int x, int y, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void line(double x1, double y1, double x2, double y2, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void dotedLine(double x1, double y1, double x2, double y2, int spaceSize, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void drawTriangle(triangProj t, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void drawTriangleF(triangProj t, SDL_Color color = { 0xff,0xff,0xff,0xff });

	void meshToScreen(Mesh mesh);

	void surfaceToScreen(Mesh mesh);

};

