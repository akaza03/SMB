#include <DxLib.h>
#include "MapCtl.h"
#include "Player.h"

Player::Player(const char(&_keyData)[256], const char(&_keyDataOld)[256], VECTOR2(chipOffset))
	:Obj(_keyData, _keyDataOld, chipOffset)
{
	skyflag = false;
	deathFlag = false;
	EnemyDeathFlag = false;
	Vy = 0;
	GoldCntX = 0;
	GoldCntO = 0;
	deathCnt = 0;
	dirLR = DIR_R;
	SetAnim("歩く");
}


Player::~Player()
{
}

void Player::SetEDFlag()
{
	EnemyDeathFlag = true;
}

bool Player::GetEDFlag()
{
	return EnemyDeathFlag;
}


void Player::Gravity()
{
	CHIP_TYPE cpTypeCD = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE), GP_BG);					//	中心の下

	float g = -0.3f;
	Vy += g;
	
	if (!deathFlag)
	{
		//	ｼﾞｬﾝﾌﾟ時
		if (skyContact())
		{
			//	重なった時用の位置補正
			pos.y = ((pos.y % CHIP_SIZE) / (CHIP_SIZE / 2) == 0 ? (pos.y / CHIP_SIZE) : ((pos.y / CHIP_SIZE) + 1)) * CHIP_SIZE;
			Vy = -Vy;
		}
		//	重力加算
		if ((cpTypeCD != TYPE_GL) && (cpTypeCD != TYPE_BBL) && (cpTypeCD != TYPE_BL) && (cpTypeCD != TYPE_QBL)
			&& (cpTypeCD != TYPE_PIPE_LU) && (cpTypeCD != TYPE_PIPE_LD) && (cpTypeCD != TYPE_PIPE_RU) && (cpTypeCD != TYPE_PIPE_RD))
		{
			pos.y -= Vy;
			skyflag = true;
			EnemyDeathFlag = false;
		}
		else
		{
			pos.y = ((pos.y % CHIP_SIZE) / (CHIP_SIZE / 2) == 0 ? (pos.y / CHIP_SIZE) : ((pos.y / CHIP_SIZE) + 1)) * CHIP_SIZE;
			Vy = 0;
			skyflag = false;
			jumpNow = false;
		}
	}
	else
	{
		pos.y -= Vy;
	}
}

bool Player::skyContact()
{
	CHIP_TYPE cpTypeCT;					//	中心の上

	const CHIP_TYPE cktype[] = {TYPE_GL,TYPE_BBL,TYPE_BL,TYPE_QBL,TYPE_PIPE_LU,TYPE_PIPE_LD,TYPE_PIPE_RU,TYPE_PIPE_RD};
	cpTypeCT = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, -1), GP_BG);

	for (int i = 0; i < sizeof(cktype) / sizeof(CHIP_TYPE); ++i)
	{
		if ((cpTypeCT == cktype[i]))
		{
			return true;
		}
	}
	return false;
}

bool Player::CheckCorrect(void)
{
	CHIP_TYPE cpTypeLT, cpTypeLB;		//	左上と左下
	CHIP_TYPE cpTypeRT, cpTypeRB;		//	右上と右下
	CHIP_TYPE cpTypeCB;					//	中心の足元
	CHIP_TYPE cpTypeCD;					//	中心の下

	const CHIP_TYPE cktype[] = {TYPE_GL,TYPE_BBL,TYPE_BL,TYPE_QBL,TYPE_PIPE_LU,TYPE_PIPE_LD,TYPE_PIPE_RU,TYPE_PIPE_RD};
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

bool Player::Contact(DIR_LR dir)
{
	CHIP_TYPE cpTypeLC, cpTypeRC;

	//	左中心
	cpTypeLC = lpMapCtl.GetMapData(pos + VECTOR2(0, CHIP_SIZE / 2), GP_BG);
	//	右中心
	cpTypeRC = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE, CHIP_SIZE / 2), GP_BG);
	const CHIP_TYPE cktype[] = {TYPE_GL,TYPE_BBL,TYPE_BL,TYPE_QBL,TYPE_PIPE_LU,TYPE_PIPE_LD,TYPE_PIPE_RU,TYPE_PIPE_RD};

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

void Player::GoldContact()
{
	CHIP_TYPE cpTypeC;				//	中心
	cpTypeC = lpMapCtl.GetMapData(pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE / 2), GP_BG);

	if(cpTypeC == TYPE_GOLD)
	{
		PlaySoundFile("sound/コイン音.mp3", DX_PLAYTYPE_BACK);
		lpMapCtl.SetMap(TYPE_BLANK, pos + VECTOR2(CHIP_SIZE / 2, CHIP_SIZE / 2));
		if (GoldCntO < 9)
		{
			GoldCntO++;
		}
		else
		{
			GoldCntO = 0;
			GoldCntX++;
		}
	}
}

bool Player::EnemyContact()
{
	return false;
}

bool Player::Update(void)
{
	lpCharHit.SetPpos(pos);
	SetMove();
	return false;
}

int Player::GetGoldX()
{
	return GoldCntX;
}

int Player::GetGoldO()
{
	return GoldCntO;
}


void Player::GetKeyData(void)
{

}

void Player::Draw(void)
{
	Obj::Draw();
}

void Player::SetMove(void)
{
	GetKeyData();

	//	重力
 	Gravity();

	if (!deathFlag)
	{
		GoldContact();

		//	死亡処理
		if (lpCharHit.PlayerDamage())
		{
			if (!deathCnt)
			{
				StopSoundFile();
				PlaySoundFile("sound/死亡音.wav", DX_PLAYTYPE_BACK);
			}
			SetAnim("死亡");
			deathCnt++;
			if (deathCnt == 30)
			{
				deathFlag = true;
				Vy = 15;
				pos.y -= Vy;
			}
		}
		else
		{
			//	敵を踏んだ時に軽くｼﾞｬﾝﾌﾟ
			if (EnemyDeathFlag)
			{
				PlaySoundFile("sound/踏んだ音.mp3", DX_PLAYTYPE_BACK);
				SetAnim("ジャンプ");
				Vy = 5;
				pos.y -= Vy;
				jumpNow = true;
			}

			//	ｼﾞｬﾝﾌﾟ開始
			if (!skyflag && !jumpNow && keyData[KEY_INPUT_UP] && !keyDataOld[KEY_INPUT_UP])
			{
				PlaySoundFile("sound/ジャンプ音.wav", DX_PLAYTYPE_BACK);
				SetAnim("ジャンプ");
				if (!skyContact())
				{
					Vy = 10;
					pos.y -= Vy;
				}
				jumpNow = true;
			}

			if (jumpNow)
			{
				SetAnim("ジャンプ");
				if (CheckCorrect())
				{
					jumpNow = false;
				}
			}
			if (pos.y < VIEW_AREA_CNT_Y * CHIP_SIZE)
			{
				//	左移動
				if (keyData[KEY_INPUT_LEFT])
				{
					if (!skyflag)
					{
						dirLR = DIR_L;
						SetAnim("歩く");
						animCnt++;
						if (!Contact(dirLR) && pos.x >= 0)
						{
							pos.x -= speed;
						}
					}
					if (skyflag && !CheckCorrect() && pos.x >= 0)
					{
						pos.x -= speed;
					}
				}
				//	右移動
				else if (keyData[KEY_INPUT_RIGHT])
				{
					if (!skyflag)
					{
						dirLR = DIR_R;
						SetAnim("歩く");
						animCnt++;
						if (!Contact(dirLR) && pos.x <= (GAME_AREA_CNT_X - 1) * CHIP_SIZE)
						{
							pos.x += speed;
						}
					}
					if (skyflag && !CheckCorrect() && pos.x <= (GAME_AREA_CNT_X - 1) * CHIP_SIZE)
					{
						pos.x += speed;
					}
				}
				else
				{
					if (!skyflag)
					{
						SetAnim("待機");
					}
				}
			}
		}
	}

	//	画面外に出ないように
	if (pos.y < 0)
	{
		pos.y = 0;
	}

	//	ﾌﾟﾚｲﾔｰの破棄
	if (pos.y > (VIEW_AREA_CNT_Y + 20) * CHIP_SIZE)
	{
		if (!deathFlag)
		{
			StopSoundFile();
			PlaySoundFile("sound/死亡音.wav", DX_PLAYTYPE_NORMAL);
		}
		death = true;
	}
}

bool Player::initAnim()
{
	AddAnim("待機", 1, 2, 1, 4);
	AddAnim("歩く", 2, 2, 3, 4);
	AddAnim("ジャンプ", 6, 2, 1, 4);
	AddAnim("死亡", 7, 2, 1, 4);

	return true;
}
