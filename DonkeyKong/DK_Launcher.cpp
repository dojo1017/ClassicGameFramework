#include <windows.h>
#include "Config.h"

#include "Level.h"
#include "Session.h"
#include "Renderer.h"
#include "Display.h"

#include "DK_Model.h"
#include "DK_View.h"
#include "DK_Controller.h"
#include "GameConfig.h"
#include "Level_25m.h"


//#include <iostream>

std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
}

int main()
{
	//Original Aufl�sung: 192x256; 8x8 Pixel Raster; 24x32 K�stchen
	//Skalierung x3
	auto config = new GameConfig(192, 256, 2, 8, 8);

	//std::string x = getexepath();

	auto session = new Session();
	auto display = new Display();
	auto renderer = new Renderer(config->getWidth(), config->getHeight(), "Donkey Kong");

	//std::vector<Level*> levels;
	//levels.push_back(new Level_25m(config));


	auto model = new DK_Model(session);
	auto view = new DK_View(model, display, renderer, config);
	auto controller = new DK_Controller(view, model);


	controller->gameLoop();

	return 0;
}
