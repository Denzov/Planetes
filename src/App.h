#include <raylib.h>
#include <iostream>

#include "../Simulation/SpaceBackground/SpaceBackground.h"
#include "../AppControl/AppControl.h"
#include "../Simulation/Planet/PlanetHolder.h"
#include "../UI/GUIHandler.h"

class App {
public:
	void Run();

private:
	void init();
	void simulate();
	void compute();
	void draw();
	void close();

private:
	float _time = 0;
};

