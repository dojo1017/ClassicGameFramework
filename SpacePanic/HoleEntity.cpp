﻿#include "HoleEntity.h"
#include "GameConfig.h"
#include "Image.h"
#include "SpacePanicModel.h"

Image* HoleEntity::getImage()
{
	switch (state)
	{
	case STAGE3: return stage3;
	case STAGE2: return stage2;
	case STAGE1: case STAGE0: default: return stage1;
	}
}

bool HoleEntity::canGrow() const
{
	switch (state)
	{
	case STAGE1: return true;
	case STAGE2: return true;
	default: return false;
	}
}

bool HoleEntity::canShrink() const
{
	switch (state)
	{
	case STAGE1: return true;
	case STAGE2: return true;
	case STAGE3: return true;
	default: return false;
	}
}

HoleEntity::HoleState HoleEntity::getStage() const
{
	return state;
}

HoleEntity::HoleEntity(
	SpacePanicModel* model,
	Position position
):
	Entity(
		new Image*[0],
		0,
		true,
		new Boundaries(
			position.x,
			position.y,
			model->getConfig()->getRasterWidth() * 3,
			model->getConfig()->getRasterHeight(),
			model->getConfig()->applyFactor(6),
			model->getConfig()->applyFactor(0),
			model->getConfig()->applyFactor(6),
			model->getConfig()->applyFactor(0)
		),
		false,
		0
	),
	state(STAGE1),
	stage1(new Image("textures/hole1.bmp", this, 200, 80, 0)),
	stage2(new Image("textures/hole2.bmp", this, 200, 80, 0)),
	stage3(new Image("textures/hole3.bmp", this, 200, 80, 0))
{
}


bool HoleEntity::grow()
{
	switch (state)
	{
	case STAGE1:
		state = STAGE2;
		return true;
	case STAGE2:
		state = STAGE3;
		return true;
	default:
		return false;
	}
}

bool HoleEntity::shrink()
{
	switch (state)
	{
	case STAGE1:
		state = STAGE0;
		return true;
	case STAGE2:
		state = STAGE1;
		return true;
	case STAGE3:
		state = STAGE2;
	default:
		return false;
	}
}

HoleEntity::~HoleEntity()
{
	delete stage1;
	delete stage2;
	delete stage3;
}
