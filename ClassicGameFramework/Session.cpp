﻿#include "Session.h"

#include "Config.h"

int Session::getLifes()
{
	return lifes;
}

void Session::setLifes(int lifes)
{
	this->lifes = lifes;
}

unsigned long Session::getCreationTime()
{
	return creationTime;
}

unsigned long Session::getPassedTime()
{
	return currentTimeMillis() - creationTime;
}

int Session::getScore()
{
	return score;
}

void Session::setScore(int score)
{
	this->score = score;
}

Level * Session::getLevel()
{
	return level;
}

void Session::setLevel(Level * level)
{
	this->level = level;
}
