#include "App.h"

void App::init()
{
	AppControl::init();
    SpaceBackground::getInstance()->init();

    PlanetHolder::getInstance()->addPlanet({   
        .radius = 10.f,
        .mass = 10000.f,
        .position = {0.f, 0.f}, 
        .speed0 = {0.f, 0.f}
    });

    // PlanetHolder::getInstance()->addPlanet({   
    //     .radius = 10.f,
    //     .mass = 10000000.f,
    //     .position = {0.f, 100.f}, 
    //     .speed0 = {-300.f, 0.f}
    // });

    // PlanetHolder::getInstance()->addPlanet({   
    //     .radius = 10.f,
    //     .mass = 10000000.f,
    //     .position = {0.f, -100.f}, 
    //     .speed0 = {300.f, 0.f}
    // });

    PlanetHolder::getInstance()->addPlanet({   
        .radius = 10.f,
        .mass = 1000.f,
        .position = {0.f, -400.f}, 
        .speed0 = {150.f, 0.f}
    });
}

void App::simulate()
{
    while (!WindowShouldClose())
    {
        std::cout << RealTimeHandler::getInstance()->getTimeScale() << std::endl;

        compute();
        draw();
    }
    CloseWindow();
}

void App::compute() 
{
    _time = GetTime();

    AppControl::inputHandle();

    PlanetHolder::getInstance()->handle();
}

void App::draw()
{
    BeginDrawing();
    BeginMode2D(MCamera2DHandler::getInstance()->getData());
    SpaceBackground::getInstance()->draw(_time);

    PlanetHolder::getInstance()->draw();
    
    EndMode2D();
    GUIHandler::getInstance()->draw();
    
    EndDrawing();
}

void App::close() {
    CloseWindow();
}

void App::Run()
{
	init();
	simulate();
}
