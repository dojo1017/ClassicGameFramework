#include "EngineController.h"
#include "EngineView.h"
#include "Renderer.h"
#include "EngineModel.h"

//EngineController* EngineController::instance = nullptr;
//EngineModel* EngineController::staticModel = nullptr;

//EngineController* EngineController::getInstance()
//{
//	return instance;
//}

void EngineController::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mode)
{
	if (EngineModel::getInstance() != nullptr)
	{
		EngineModel::getInstance()->key_callback(window, key, scancode, action, mode);
	}

	//if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	//{
	//	EngineModel::escPressed = true;
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

// Basic constructor
EngineController::EngineController(EngineView* view, EngineModel* model): view(view), model(model)
{
	//instance = this;
	//EngineController::staticModel = model;
	//TODO: window ist NULL bei erstem Aufruf?
	glfwSetKeyCallback(view->renderer->window, key_callback);
}

void EngineController::gameLoop()
{
	EngineController::lastTime = glfwGetTime(); // Set first timestamp
	while (glfwWindowShouldClose(view->renderer->window) == 0 && !model->shouldClose)
	{
		double now = glfwGetTime();
		EngineController::timeElapsed = now - EngineController::lastTime;
		EngineController::lastTime = now;

		model->key_down(view->renderer->window); // Deliver keys pressed to window
		model->nextIteration();					 // Have Model perform actions
		cycle();								 // Execute the game's basic action for each cycle
		view->update();							 // Update changes in view
		glfwPollEvents();						 // Have GLFW process received events
	}
}

//void EngineController::closeWindow() const
//{
	//glfwSetWindowShouldClose(view->renderer->window, 1);
//}

EngineController::~EngineController()
{
}
