
#include "Display.h"

Screen::Screen(int w, int h, int scale){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDLRotateWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, w/scale, h/scale);

	screenWidth = w/scale;
	screenHeight = h/scale;

	CameraCoord = { 0,0,0 };

	//generate projection matrix
	projMatrix = calculatePrjctMatrix(screenWidth, screenHeight, 0.1, 1000, 75);

	SDL_PollEvent(&event); //idk it wanted me to initialize event...
}

void Screen::clear(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Screen::show(){
	SDL_RenderPresent(renderer);
}

void Screen::input(){
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
	}
}

int Screen::getScreenWidth() {
	return screenWidth;
}

int Screen::getScreenHeight()
{
	return screenHeight;
}


Matrix4x4 Screen::calculatePrjctMatrix(int screenW, int screenH, double zNear, double zFar, double fov) {

	Matrix4x4 result;

	double a = (static_cast<double>(screenH / screenW));
	double f = 1 / (std::tan((fov / 2)*(M_PI/180)));
	double lambda = zFar / (zFar - zNear);

	result.setValue(0, 0, a * f);
	result.setValue(1, 1, f);
	result.setValue(2, 2, lambda);
	result.setValue(2, 3, -lambda * zNear);
	result.setValue(3, 2, 1);

	return result;
}


void Screen::pixel(int x, int y){
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawPoint(renderer, x, y);
}

void Screen::line(int x1, int y1, int x2, int y2){
	double dx = x2 - x1;
	double dy = y2 - y1;
	double length = std::sqrt(dx * dx + dy * dy);
	double angle = std::atan2(dy, dx);

	for (float i = 0; i < length; i++) {

		pixel(
			static_cast<int>(x1 + std::cos(angle) * i),
			static_cast<int>(y1 + std::sin(angle) * i)
		);
	}
}

void Screen::dotedLine(int x1, int y1, int x2, int y2, int spaceSize) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double length = std::sqrt(dx * dx + dy * dy);
	double angle = std::atan2(dy, dx);

	int dotlen = 0;

	for (float i = 0; i < length; ) {
		pixel(
			static_cast<int>(x1 + std::cos(angle) * i),
			static_cast<int>(y1 + std::sin(angle) * i)
		);

		dotlen++;
		i++;
		if (dotlen > spaceSize) {
			dotlen = 0;
			i += spaceSize;
		}
	}
}

void Screen::drawTriangle(triangProj t) {
	line(t[0].x, t[0].y, t[1].x, t[1].y);
	line(t[1].x, t[1].y, t[2].x, t[2].y);
	line(t[2].x, t[2].y, t[0].x, t[0].y);
}

void Screen::meshToScreen(Mesh mesh) {

	triangle t;
	vec3 n;			//normal vector
	vec3 pOT;		//point on Triangle
	triangProj tP = { {}, {}, {} };
	for (int i = 0; i < mesh.getMeshSize(); i++) {
		n = mesh.getNormalOfTriangle(i);
		t = mesh.getTriangle(i);
		pOT = t[0];
		
		double  check = n * (pOT-CameraCoord).unit();

		if(check < 0) {
			t[0] = (projMatrix * t[0]);
			t[1] = (projMatrix * t[1]);
			t[2] = (projMatrix * t[2]);

			for (int j = 0; j < 3; j++) {
				tP[j].x = (int)(t[j].x * screenWidth) + screenWidth / 2;
				tP[j].y = (int)(t[j].y * -screenHeight) + screenHeight / 2;
			}
			drawTriangle(tP);
		}

	}

}
