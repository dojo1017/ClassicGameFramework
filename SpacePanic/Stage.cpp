﻿#include "Stage.h"
#include "WallEntity.h"
#include "LadderEntity.h"
#include "Session.h"
#include "UI.h"
#include "PlayerEntity.h"
#include "SpacePanicModel.h"
#include "EnemyEntity.h"
#include "FloorEntity.h"


void Stage::setPlayer(PlayerEntity* player)
{
	if (this->player != nullptr)
	{
		delete this->player;
	}
	this->player = player;
	//this->physicalObjects->push_back(player);
}

void Stage::addEnemy(EnemyEntity* enemy) const
{
	this->enemys->push_back(enemy);
	//this->physicalObjects->push_back(enemy);
}

void Stage::addBackgroundEntity(Entity* backgroundEntity) const
{
	backgroundEntities->push_back(backgroundEntity);
	//this->physicalObjects->push_back(backgroundEntity);
}


void Stage::generateSortedEntities() const
{
	//TODO: optimize (don't always throw everything away)
	entities->clear();

	//Hintergrund-Entities
	for (auto i = 0; i < backgroundEntities->size(); i++)
	{
		entities->push_back(backgroundEntities->at(i));
	}

	//Holes
	for (auto i = 0; i < holeEntities->size(); i++)
	{
		entities->push_back(holeEntities->at(i));
	}

	//Player
	entities->push_back(player);

	//Enemys
	for (auto i = 0; i < enemys->size(); i++)
	{
		if(enemys->at(i)->getState() != EnemyEntity::DEAD)
		{
			entities->push_back(enemys->at(i));
		}
		
	}

	//ui->update();
	//UI
	for (auto i = 0; i < ui->getEntities()->size(); i++)
	{
		entities->push_back(ui->getEntities()->at(i));
	}
}

Stage::Stage(SpacePanicModel* model, const char* stageFile):
	Level(
		model->getConfig()->getRasterColumnsCount(),
		model->getConfig()->getRasterRowsCount(),
		model->getConfig()->getRasterWidth(),
		model->getConfig()->getRasterHeight(),
		new Physics(model)
	),
	config(model->getConfig()),
	player(nullptr),
	enemys(new std::vector<EnemyEntity*>()),
	backgroundEntities(new std::vector<Entity*>()),
	ui(new UI(model)),
	stageFile(stageFile),
	//physicalObjects(new std::vector<PhysicalObject*>()),
	holeEntities(new std::vector<HoleEntity*>()),
	model(model)
{
	addBackgroundEntity(new FloorEntity(model));
	leveldata = this->getLeveldata(stageFile, 22, config->getRasterColumnsCount());
	//cells = new Cells(config, this->getLeveldata(stageMovementFile, 22, config->getRasterColumnsCount()), 22, config->getRasterColumnsCount());

	for (auto row = 0; row < 22; row++)
	{
		for (auto col = 0; col < config->getRasterColumnsCount(); col++)
		{
			switch (leveldata[row][col])
			{
			case 'q': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::LEFT_WALL_1));
				break;
			case 'Q': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::LEFT_WALL_2));
				break;
			case 'w': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::MIDDLE_WALL_1));
				break;
			case 'W': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::MIDDLE_WALL_2));
				break;
			case 'e': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::RIGHT_WALL_1));
				break;
			case 'E': addBackgroundEntity(new WallEntity(model, new Position(col, 25 - row), WallEntity::WallState::RIGHT_WALL_2));
				break;
			case 'P': setPlayer(new PlayerEntity(model, new Position(col, 25 - row)));
				break;
			case 'M': addEnemy(new EnemyEntity(model, new Position(col, 25 - row), 0.5));
				break;
			case 'H': addBackgroundEntity(new LadderEntity(model, new Position(col, 25 - row)));
				break;
			default: break;
			}
		}
	}

	//auto uiEntities = ui->getEntities();
	//for (auto i = 0; i < uiEntities->size(); i++)
	//{
	//	addBackgroundEntity(uiEntities->at(i));
	//}
}


const char* Stage::getFilePath() const
{
	return stageFile;
}

PlayerEntity* Stage::getPlayer() const
{
	return player;
}

std::vector<EnemyEntity*>* Stage::getEnemys() const
{
	return enemys;
}

std::vector<Entity*>* Stage::getBackgroundEntities() const
{
	return backgroundEntities;
}

Stage::~Stage()
{
	//delete backgroundEntities;
	//delete player;
	//delete holeEntities;
	//delete ui;
	//delete enemys;
	//delete cells;
	delete[] leveldata;
}

std::vector<Entity*>* Stage::getEntities() const
{
	generateSortedEntities();
	return entities;
}

//Stage::Cells* Stage::getCells() const
//{
//	return cells;
//}

std::vector<std::pair<PhysicalObject*, PhysicalObject*>>* Stage::getCollisions() const
{
	return getPhysics()->checkCollisions(getPhysicalObjects());
}

void Stage::addHole(HoleEntity* hole) const
{
	holeEntities->push_back(hole);
	//physicalObjects->insert(physicalObjects->begin(), hole);
}

void Stage::removeHole(HoleEntity* hole) const
{
	for (auto i = 0; i < holeEntities->size(); i++)
	{
		if (holeEntities->at(i) == hole)
		{
			holeEntities->erase(holeEntities->begin() + i);
			break;
		}
	}
	delete hole;
	generateSortedEntities();
}

UI* Stage::getUI() const
{
	return ui;
}

void Stage::reset()
{
	player->reset();
	
	for(auto i = 0; i < enemys->size(); i++)
	{
		enemys->at(i)->reset();
	}

	for(auto i = 0; i < holeEntities->size(); i++)
	{
		delete holeEntities->at(i);
	}
	holeEntities->clear();
	generateSortedEntities();
}

void Stage::gameOver()
{
	
}

