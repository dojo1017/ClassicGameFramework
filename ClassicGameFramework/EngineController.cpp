#include "EngineController.h"
#include "EngineView.h"
#include "Renderer.h"
#include "EngineModel.h"

EngineModel* EngineController::staticModel = nullptr;

void EngineController::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode)
{
	if (EngineController::staticModel != nullptr)
	{
		EngineController::staticModel->key_callback(window, key, scancode, action, mode);
	}

	//if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	//{
	//	EngineModel::gameloopShouldEnd = true;
	//}
	/*
	if (action == GLFW_PRESS && keyPressedListeners.find(key) != keyPressedListeners.end())
	{
		keyPressedListeners.at(key)();
	}
	else if (action == GLFW_RELEASE && keyReleasedListeners.find(key) != keyReleasedListeners.end())
	{
		keyReleasedListeners.at(key)();
	}*/
}

EngineController::EngineController(EngineView* view, EngineModel* model): view(view), model(model)
{
	EngineController::staticModel = model;
	glfwSetKeyCallback(view->renderer->window, key_callback);
}

void EngineController::gameLoop()
{
	while (model->gameloopShouldEnd == false)
	{
		// TODO
		// model.nextIteration(); 
		view->update();
	}
}

EngineController::~EngineController()
{
}
