#include <iostream>
#include "Display.h"
#include "FrameHandler.h"
#include "Mesh.h"

#define RADCONV M_PI/180

using namespace std;

int main(int argc, char* args[]) {

	Screen screen(640, 640, 1);

	screen.clear();
	
	FrameHandler frameHandler(100);
	

	int w = screen.getScreenWidth();
	int h = screen.getScreenHeight();

	double sl = 3;

	triangleV cubeFacet = {
		//South
		{{sl,0,0}, {sl,sl,0}, {0,sl,0}},
		{{sl,0,0}, {0,sl,0}, {0,0,0}},
		//East
		{{sl,0,0}, {sl,0,sl}, {sl,sl,sl}},
		{{sl,0,0}, {sl,sl,sl}, {sl,sl,0}},
		//Nort
		{{0,0,sl}, {0,sl,sl}, {sl,sl,sl}},
		{{0,0,sl}, {sl,sl,sl}, {sl,0,sl}},
		//West
		{{0,sl,0}, {0,sl,sl}, {0,0,sl}},
		{{0,sl,0}, {0,0,sl}, {0,0,0}},
		//Top
		{{sl,sl,0}, {sl,sl,sl}, {0,sl,sl}},
		{{sl,sl,0}, {0,sl,sl}, {0,sl,0}},
		//Bottom
		{{0,0,0}, {0,0,sl}, {sl,0,sl}},
		{{0,0,0}, {sl,0,sl}, {sl,0,0}}
	};

	Mesh cube(cubeFacet, {sl/2,sl/2,sl/2});

	cube.moveMesh({ -sl/2,-sl/2+5,30 });

	frameHandler.restartTime();

	while (true) {
		
		if (frameHandler.drawNewFrame()) {
			screen.show();
			screen.clear();
			unsigned int fcount = frameHandler.getFrameCount();
			Uint64 timer = frameHandler.timeSinceStart();

			screen.line(w / 2, 0, w / 2, h);
			screen.line(0, h / 2, w, h / 2);
			
			screen.meshToScreen(cube);
			
			cube.rotateMesh({ 0, 0, M_PI / 300 }, {0,0,0});

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
	}

	return 0;
}