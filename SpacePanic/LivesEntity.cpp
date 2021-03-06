﻿#include "LivesEntity.h"
#include "GameConfig.h"
#include "Image.h"

LivesEntity::LivesEntity(SpacePanicModel* model):
	Entity(
		new Image*[0],
		0,
		false,
		new Boundaries(model->getConfig()->getRasterWidth() * 2,
		               model->getConfig()->getRasterHeight(),
		               model->getConfig()->getRasterWidth() * 4,
		               model->getConfig()->getRasterHeight()),

		false,
		0
	),
	model(model),
lives0(new Image("textures/0lives.bmp", this)),
lives1(new Image("textures/1lives.bmp", this)),
lives2(new Image("textures/2lives.bmp", this)),
lives3(new Image("textures/3lives.bmp", this))
{
}

Image* LivesEntity::getImage()
{
	auto lives = model->getSession()->getLifes();
	if (lives >= 3) return lives3;
	if (lives == 2) return lives2;
	if (lives == 1) return lives1;
	else return lives0;
}

LivesEntity::~LivesEntity()
{
	delete lives0;
	delete lives1;
	delete lives2;
	delete lives3;
}
