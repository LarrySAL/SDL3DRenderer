#include <iostream>
#include <cstdlib> // For system function

#ifdef _WIN32
const char* CLEAR_COMMAND = "cls";
#else
const char* CLEAR_COMMAND = "clear";
#endif

#include "Display.h"
#include "FrameHandler.h"
#include "Mesh.h"

#define RADCONV M_PI/180

using namespace std;

int main(int argc, char* args[]) {

	Screen screen(640, 640, 1);

	screen.clear();
	
	FrameHandler frameHandler(60);
	

	int w = screen.getScreenWidth();
	int h = screen.getScreenHeight();

	double sl = 3;

	//clockwise
	triangleV cubeFacet = {
		//South Red
		{{0,0,0}, {0,sl,0}, {sl,sl,0}},
		{{0,0,0}, {sl,sl,0}, {sl,0,0}},
		//East Pink
		{{sl,0,0}, {sl,sl,0}, {sl,sl,sl}},
		{{sl,0,0}, {sl,sl,sl}, {sl,0,sl}},
		//North Skin color
		{{sl,0,sl}, {sl,sl,sl}, {0,sl,sl}},
		{{sl,0,sl}, {0,sl,sl}, {0,0,sl}},
		//West Yellow
		{{0,0,sl}, {0,sl,sl}, {0,sl,0}},
		{{0,0,sl}, {0,sl,0}, {0,0,0}},
		//Top Light Blue
		{{0,sl,0}, {0,sl,sl}, {sl,sl,sl}},
		{{0,sl,0}, {sl,sl,sl}, {sl,sl,0}},
		//Bottom Green
		{{0,0,sl}, {0,0,0}, {sl,0,0}},
		{{0,0,sl}, {sl,0,0}, {sl,0,sl}}
	};

	Mesh cube(cubeFacet, {sl/2,sl/2,sl/2});

	cube.moveMesh({ -sl/2,-sl/2+5,30 });

	frameHandler.restartTime();

	//Uint64 timeSince

	while (true) {
		
		if (frameHandler.drawNewFrame()) {
			screen.show();
			screen.clear();
			system(CLEAR_COMMAND);

			unsigned int fcount = frameHandler.getFrameCount();
			Uint64 timer = frameHandler.timeSinceStart();


			screen.line(w / 2, 0, w / 2, h);
			screen.line(0, h / 2, w, h / 2);
			
			screen.surfaceToScreen(cube);
			//screen.meshToScreen(cube);
			//cube.printNormals();
			

			double frameTime = (timer/ fcount);
			double rot1 = (0.25 / 10) * RADCONV * frameTime; //frequency to radians
			double rot2 = (0.5 / 10) * RADCONV * frameTime;
			cube.rotateMesh({ 0, 0, rot1 }, {0,0,0});
			cube.rotateMesh({ 0, rot2, rot2 }, cube.getCenter());


			//double frequency = 0.25/10;
			//double diameter = 5;
			//double phase = -90.0 * RADCONV;
			//cube.setMesh({ 
			//	diameter * std::cos(timer * RADCONV * frequency + phase), 
			//	diameter * std::sin(timer * RADCONV * frequency + phase),
			//	30/*10 * std::cos(timer * RADCONV * 0.5)+ 30*/
			//});

		}

		//TODO put frame independent timer
		//when to reset timer? 
		//
		//TODO FPS counter

		//check if user clicks Exit
		screen.input();

		while (screen.stopLoop()) screen.input();;

	}

	return 0;
}