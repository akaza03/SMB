#include <DxLib.h>
#include "MapCtl.h"
#include "GameScene.h"
#include "Enemy.h"

Enemy::Enemy(const char(&_keyData)[256], const char(&_keyDataOld)[256], VECTOR2(chipOffset))
	:Obj(_keyData,_keyDataOld,chipOffset)
{
	skyflag = false;
	deathCnt = 0;
	Cnt = 0;
	Vy = 0;
	dirLR = DIR_L;
	SetAnim("歩く");
}


Enemy::~Enemy()
{
	lpCharHit.SetEpos(VECTOR2(0,0));
}

bool Enemy::Update()
{
	lpCharHit.SetEpos(pos);
	SetMove();
	return false;
}

void Enemy::Draw()
{
	Obj::Draw();
}

void Enemy::Gravity()
{
	CHIP_TYPE cpTypeCD = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE), GP_BG);					//	中心の下

	float g = -0.3f;
	Vy += g;

	if ((cpTypeCD != TYPE_GL) && (cpTypeCD != TYPE_BBL) && (cpTypeCD != TYPE_BL) && (cpTypeCD != TYPE_QBL)
		&& (cpTypeCD != TYPE_PIPE_LU) && (cpTypeCD != TYPE_PIPE_LD) && (cpTypeCD != TYPE_PIPE_RU) && (cpTypeCD != TYPE_PIPE_RD))
	{
		pos.y -= Vy;
		skyflag = true;
	}
	else
	{
		pos.y = ((pos.y % CHIP_SIZE) / (CHIP_SIZE / 2) == 0 ? (pos.y / CHIP_SIZE) : ((pos.y / CHIP_SIZE) + 1)) * CHIP_SIZE;
		Vy = 0;
		skyflag = false;
	}
}

bool Enemy::CheckCorrect()
{
	CHIP_TYPE cpTypeLT, cpTypeLB;		//	左上と左下
	CHIP_TYPE cpTypeRT, cpTypeRB;		//	右上と右下
	CHIP_TYPE cpTypeCB;					//	中心の足元
	CHIP_TYPE cpTypeCD;					//	中心の下

	const CHIP_TYPE cktype[] = { TYPE_GL,TYPE_BBL,TYPE_BL,TYPE_QBL,TYPE_PIPE_LU,TYPE_PIPE_LD,TYPE_PIPE_RU,TYPE_PIPE_RD };
	cpTypeLT = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 4, 0), GP_BG);
	cpTypeLB = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 4, CHIP_SIZE - 1), GP_BG);
	cpTypeRT = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE - CHIP_SIZE / 4, 0), GP_BG);
	cpTypeRB = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE - CHIP_SIZE / 4, CHIP_SIZE - 1), GP_BG);
	cpTypeCB = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE - 1), GP_BG);
	cpTypeCD = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE), GP_BG);

	for (int i = 0; i < sizeof(cktype) / sizeof(CHIP_TYPE); ++i)
	{
		if ((cpTypeLT == cktype[i]) || (cpTypeLB == cktype[i]) || (cpTypeRT == cktype[i])
			|| (cpTypeRB == cktype[i]) || (cpTypeCB == cktype[i]) || (cpTypeCD == cktype[i]))
		{
			return true;
		}
	}
	return false;
}

bool Enemy::Contact(DIR_LR dir)
{
	CHIP_TYPE cpTypeLC, cpTypeRC;
	
	//	左中心
	cpTypeLC = lpMapCtl.GetMapData(pos + VECTOR2(0, CHIP_SIZE / 2), GP_BG);
	//	右中心
	cpTypeRC = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE, CHIP_SIZE / 2), GP_BG);
	const CHIP_TYPE cktype[] = { TYPE_GL,TYPE_BBL,TYPE_BL,TYPE_QBL,TYPE_PIPE_LU,TYPE_PIPE_LD,TYPE_PIPE_RU,TYPE_PIPE_RD };

	for (int i = 0; i < sizeof(cktype) / sizeof(CHIP_TYPE); ++i)
	{
		if (dir == DIR_L)
		{
			if (cpTypeLC == cktype[i])
			{
				return true;
			}
		}
		else if (dir == DIR_R)
		{
			if (cpTypeRC == cktype[i])
			{
				return true;
			}
		}
	}
	return false;
}

void Enemy::SetMove()
{
	bool deathFlag = lpCharHit.EnemyDeath();

	//	重力
	Gravity();

	Cnt++;
	if ((Cnt % 2) == 0)
	{
		animCnt++;
	}

	if (moveLR)
	{
		SetAnim("歩く");
		if (!lpCharHit.PlayerDamage())
		{
			if (deathFlag)
			{
				SetAnim("潰れた");
				moveLR = false;
				//deathCnt++;
				//if (deathCnt == 30)
				{
					death = true;
				}
			}
			else
			{
				if (dirLR == DIR_L)
				{
					dirLR = DIR_L;
					if (!Contact(dirLR) && pos.x >= 0)
					{
						pos.x -= speed;
					}
					else
					{
						dirLR = DIR_R;
					}
					if (skyflag && !CheckCorrect())
					{
						pos.x -= speed;
					}
				}
				else if (dirLR == DIR_R)
				{
					dirLR = DIR_R;
					if (!Contact(dirLR) && pos.x <= (GAME_AREA_CNT_X - 1) * CHIP_SIZE)
					{
						pos.x += speed;
					}
					else
					{
						dirLR = DIR_L;
					}
					if (skyflag && !CheckCorrect())
					{
						pos.x += speed;
					}
				}
			}
		}
	}
}

bool Enemy::initAnim()
{
	AddAnim("歩く", 0, 1, 2, 4);
	AddAnim("潰れた", 2, 1, 1, 4);
	return true;
}
