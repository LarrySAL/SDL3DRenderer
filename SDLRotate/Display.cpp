
#include "Display.h"

Screen::Screen(int w, int h, int scale){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDLRotateWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, w/scale, h/scale);

	screenWidth = w/scale;
	screenHeight = h/scale;

	CameraCoord = { 0,0,0 };

	lightDir = { 0,0,1 };
	lightDir = lightDir.unit();

	stop = false;

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

		switch (event.type) {
		
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		case SDL_KEYDOWN:
			stop = !stop;
		default:
			break;
		}

		if (event.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
	}
}

bool Screen::stopLoop() {
	return stop;
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

void Screen::pixel(double x, double y, SDL_Color color){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, int(x), int(y));
}

void Screen::pixel(int x, int y, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, x, y);
}

void Screen::line(double x1, double y1, double x2, double y2, SDL_Color color) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	double length = std::sqrt(dx * dx + dy * dy);
	double angle = std::atan2(dy, dx);

	for (float i = 0; i < length; i++) {

		pixel(
			x1 + std::cos(angle) * i,
			y1 + std::sin(angle) * i,
			color
		);
	}
}

void Screen::dotedLine(double x1, double y1, double x2, double y2, int spaceSize, SDL_Color color){
	double dx = x2 - x1;
	double dy = y2 - y1;
	double length = std::sqrt(dx * dx + dy * dy);
	double angle = std::atan2(dy, dx);

	double dotlen = 0;

	for (float i = 0; i < length; ) {
		pixel(
			x1 + std::cos(angle) * i,
			y1 + std::sin(angle) * i,
			color
		);

		dotlen++;
		i++;
		if (dotlen > spaceSize) {
			dotlen = 0;
			i += spaceSize;
		}
	}
}

void Screen::drawTriangle(triangProj t, SDL_Color color) {
	line(t[0].x, t[0].y, t[1].x, t[1].y, color);
	line(t[1].x, t[1].y, t[2].x, t[2].y, color);
	line(t[2].x, t[2].y, t[0].x, t[0].y, color);
}

void Screen::drawTriangleF(triangProj t, SDL_Color color){
	vec2 v1 = (t[1] - t[0]);
	vec2 v2 = (t[2] - t[1]);
	vec2 v3 = (t[0] - t[2]);

	std::vector<double> xes = { t[0].x, t[1].x, t[2].x};
	std::vector<double> yes = { t[0].y, t[1].y, t[2].y };
	
	//calculate bounding box for triangle
	int maxW = int(maxX2(xes));
	int maxH = int(maxY2(yes));
	int minW = int(minX2(xes));
	int minH = int(minY2(yes));

	//line(minW, maxH, maxW, maxH);
	//line(minW, maxH, minW, minH);
	//line(minW, minH, maxW, minH);
	//line(maxW, minH, maxW, maxH);

	//iterate through every pixel in bounding box
	for (int i = minH; i <= maxH; i++) {
		for (int j = minW; j <= maxW; j++) {
			
			vec2 pq = { double(j),double(i)};

			vec2 pq1 = pq - t[0];
			double a = v1.unit() / pq1.unit();
			pq1 = pq - t[1];
			double b = v2.unit() / pq1.unit();
			pq1 = pq - t[2];
			double c = v3.unit() / pq1.unit();

			//check if current pixel is inside triangle
			bool cond = (
				a >= 0 &&
				b >= 0 &&
				c >= 0
				);

			if (cond) {
				//double x = (i * screenWidth) + screenWidth / 2;
				//double y = (j * -screenHeight) + screenHeight / 2;
				
				pixel(j,i, color);
			}
		}
	}

}

void Screen::meshToScreen(Mesh mesh) {

	triangle t;
	vec3 n;			//normal vector
	vec3 pOT;		//point on Triangle
	vec3 cTP;		//camera to Point vector
	triangProj tP = { {}, {}, {} };

	float mult = float(255 / mesh.getMeshSize());

	SDL_Color currentColor = {0,0,0,0};

	for (int i = 0; i < mesh.getMeshSize(); i++) {
		n = mesh.getNormalOfTriangle(i);
		t = mesh.getTriangle(i);
		pOT = t[0];
		cTP = (pOT - CameraCoord).unit();

		double  check = n * cTP;

		if(check < 0) {
			t[0] = (projMatrix * t[0]);
			t[1] = (projMatrix * t[1]);
			t[2] = (projMatrix * t[2]);

			for (int j = 0; j < 3; j++) {
				tP[j].x = (int)(t[j].x * screenWidth) + screenWidth / 2;
				tP[j].y = (int)(t[j].y * -screenHeight) + screenHeight / 2;
			}

			if (i % 2 == 0) {
				currentColor = {
					{Uint8(-mult * i+255)},
					{Uint8(mult * i)},
					{Uint8(mult * i - i * 255 / 4)}
				};
			}

			currentColor = { 0xff, 0xff, 0xff, 0xff };

			drawTriangle(tP, currentColor);

		}
		//draw center point
		vec3 center3D = mesh.getCenter();
		vec3 normCenter;
		vec2 center;
		unsigned int centerCrossSize = screenWidth / 50;

		normCenter = projMatrix * mesh.getCenter();
		center.x = (int)(normCenter.x * screenWidth) + screenWidth / 2;
		center.y = (int)(normCenter.y * -screenHeight) + screenHeight / 2;
		line(center.x + centerCrossSize, center.y, center.x - centerCrossSize, center.y);
		line(center.x, center.y + centerCrossSize, center.x, center.y - centerCrossSize);

	}

}

void Screen::surfaceToScreen(Mesh mesh) {

	triangle t;
	vec3 n;			//normal vector
	vec3 pOT;		//point on Triangle
	vec3 cTP;		//camera to Point vector
	triangProj tP = { {}, {}, {} };

	float mult = float(255 / mesh.getMeshSize());

	SDL_Color currentColor = { 0,0,0,0 };

	double alpha;		//brigthness factor 0-1

	for (int i = 0; i < mesh.getMeshSize(); i++) {
		n = mesh.getNormalOfTriangle(i);
		t = mesh.getTriangle(i);
		pOT = t[0];
		cTP = (pOT - CameraCoord).unit();

		double  check = n * cTP;
		alpha = 0.1;


		if (check < 0) {
			//projection and transformation to screen coords
			t[0] = (projMatrix * t[0]);
			t[1] = (projMatrix * t[1]);
			t[2] = (projMatrix * t[2]);

			for (int j = 0; j < 3; j++) {
				tP[j].x = (int)(t[j].x * screenWidth) + screenWidth / 2;
				tP[j].y = (int)(t[j].y * -screenHeight) + screenHeight / 2;
			}

			if (i % 2 == 0) {
				//brightness calculation
				//alpha depending on the angle (45 degrees -> alpha = 0.5)

				//float angleT = std::acos(lightDir * n) * 180/M_PI;

				if (lightDir * n < -0.1) {
					alpha = std::acos(lightDir * n)/(90 * M_PI/180);

					if (alpha < 0.1) {
						alpha = 0.1; 
					}

				}
				
				currentColor = { Uint8(255 * alpha), Uint8(0 * alpha), Uint8(0 * alpha) };
				//currentColor = { 255,255,255 };

				//currentColor = {
				//	{Uint8(-mult * i + 255)},
				//	{Uint8(mult * i)},
				//	{Uint8(mult * i - i * 255 / 4)}
				//};
			}

			drawTriangleF(tP, currentColor);

		}
		//draw center point
		vec3 center3D = mesh.getCenter();
		vec3 normCenter;
		vec2 center;
		unsigned int centerCrossSize = screenWidth / 50;

		normCenter = projMatrix * mesh.getCenter();
		center.x = (int)(normCenter.x * screenWidth) + screenWidth / 2;
		center.y = (int)(normCenter.y * -screenHeight) + screenHeight / 2;
		line(center.x + centerCrossSize, center.y, center.x - centerCrossSize, center.y);
		line(center.x, center.y + centerCrossSize, center.x, center.y - centerCrossSize);

	}
}
