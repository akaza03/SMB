#pragma once
#include <memory>
#include <list>
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "BaseScene.h"

typedef std::shared_ptr<Player> player_ptr;
typedef std::list<player_ptr> player_List;

typedef std::shared_ptr<Enemy> enemy_ptr;
typedef std::list<enemy_ptr> enemy_List;

typedef std::unique_ptr<Camera> camera_ptr;

class GameScene :
	public BaseScene
{
public:
	player_List::iterator player;
	player_List playerList;

	std::list<enemy_ptr>::iterator enemy;

	GameScene();
	~GameScene();

	void Init();

	void GetEListSize();

	void SetUpChar();								//	∑¨◊∏¿∞ÇÃê›íu

	void SetCam(player_ptr playerPtr);

	VECTOR2 GetPlayerPos();

	scene_ptr Update(scene_ptr scn);

	std::list<enemy_ptr>::iterator AddEnemyList(enemy_ptr && EnemyPtr);

private:
	enemy_List enemyList;
	camera_ptr camera;
};

