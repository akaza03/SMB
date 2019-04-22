#include "DxLib.h"
#include "VECTOR2.h"
#include "MapCtl.h"
#include "CharHit.h"
#include "Player.h"
#include "Enemy.h"
#include "TitleScene.h"
#include "GameTask.h"
#include "GameScene.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

void GameScene::Init()
{
	enemyList.clear();
	camera = std::make_unique<Camera>();
	lpMapCtl.LoadMap("data/map.csv");
	SetUpChar();
}

void GameScene::GetEListSize()
{
}

scene_ptr GameScene::Update(scene_ptr scn)
{
	if (lpGameTask.keyData[KEY_INPUT_RETURN])
	{
		return scene_ptr(std::make_unique<TitleScene>());
	}

	ClsDrawScreen();

	lpMapCtl.SetCameraPos(camera->GetPos());

	lpMapCtl.MapDraw();

	//	çXêVèàóù
	auto itr = enemyList.begin();
	while (itr != enemyList.end())
	{
		(*itr)->Update();
		//	éÄñSÇµÇΩèÍçáÇÕëŒè€ÇçÌèúÇµÅAéüÇÃóvëfÇï‘Ç∑
		if ((*itr)->GetDeath())
		{
			itr = enemyList.erase(itr);
		}
		else
		{
			++itr;
		}
		lpCharHit.SetEListSize(enemyList.size());
	}

	(*player)->Update();

	if ((*player)->GetDeath())
	{
		return scene_ptr(std::make_unique<TitleScene>());
	}

	camera->Update();

	//	ï`âÊèàóù
	for (auto itr = enemyList.begin(); itr != enemyList.end(); ++itr)
	{
		(*itr)->Draw();
	}
	(*player)->Draw();

	ScreenFlip();
	return scn;
}

std::list<enemy_ptr>::iterator GameScene::AddEnemyList(enemy_ptr && EnemyPtr)
{
	enemyList.push_back(EnemyPtr);
	auto itr = enemyList.end();
	itr--;
	return itr;
}


void GameScene::SetUpChar(void)
{
	//	Ãﬂ⁄≤‘∞ÇÃçÏê¨
	auto makePlayer = [&]()
	{
		playerList.push_back(std::make_shared<Player>(lpGameTask.keyData, lpGameTask.keyDataOld, VECTOR2(0, 0)));
	};

	for (CHIP_GP gp = GP_BG; gp < GP_MAX; gp = (CHIP_GP)(gp + 1))
	{
		for (float y = 0; y < VIEW_AREA_CNT_Y; y++)
		{
			for (float x = 0; x < GAME_AREA_CNT_X; x++)
			{
				//	Ãﬂ⁄≤‘∞
				if (GET_MAP_ID2(x, y, gp) == TYPE_PLAYER)
				{
					makePlayer();
					player = playerList.begin();
					(*player)->init("image/Player.png", { 32, 32 }, { 24, 9 }, { 1,2 }, 3);
					(*player)->SetPos(VECTOR2(CHIP_SIZE * x, CHIP_SIZE * y));
					SetCam((*player));
				}
			}
		}
	}

	for (CHIP_GP gp = GP_BG; gp < GP_MAX; gp = (CHIP_GP)(gp + 1))
	{
		for (float y = 0; y < VIEW_AREA_CNT_Y; y++)
		{
			for (float x = 0; x < GAME_AREA_CNT_X; x++)
			{
				//	¥»–∞
				if (GET_MAP_ID2(x, y, gp) == TYPE_ENEMY)
				{
					enemy = AddEnemyList(std::make_shared<Enemy>(lpGameTask.keyData, lpGameTask.keyDataOld, VECTOR2(0, 0)));
					(*enemy)->init("image/Enemy.png", { 32, 32 }, { 50,8 }, { 1,1 }, 1);
					(*enemy)->SetPos(VECTOR2(CHIP_SIZE * x, CHIP_SIZE * y));
				}
			}
		}
	}
}

void GameScene::SetCam(player_ptr playerPtr)
{
	camera->SetTarget(playerPtr);
}

VECTOR2 GameScene::GetPlayerPos()
{
	return (*player)->GetPos();
}
