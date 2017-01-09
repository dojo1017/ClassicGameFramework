#pragma once

#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"


#include "SpacePanicModel.h"
#include "SpacePanicView.h"
#include "SpacePanicController.h"

int main()
{
	auto session = new Session();
	auto display = new Display();
	auto renderer = new Renderer();

	std::vector<Level*> levels;
	levels.push_back(new Level(15, 20, new std::string("menu.txt")));
	levels.push_back(new Level(15, 20, new std::string("level1.txt")));
	levels.push_back(new Level(15, 20, new std::string("level2.txt")));
	levels.push_back(new Level(15, 20, new std::string("level3.txt")));


	auto model = new SpacePanicModel(session);
	auto view = new SpacePanicView(model, display, renderer);
	auto controller = new SpacePanicController(view, model);



	controller->gameLoop();

	return 0;
}
