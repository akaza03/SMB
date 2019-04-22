#include "MapCtl.h"
#include "CharHit.h"

std::unique_ptr<CharHit, CharHit::CharHitDeleter> CharHit::s_Instance(new CharHit);

CharHit::CharHit()
{
	int EListSize = 0;
}


CharHit::~CharHit()
{
}

void CharHit::SetPpos(const VECTOR2 & Ppos)
{
	this->Ppos = Ppos;
}

void CharHit::SetEpos(const VECTOR2 & Epos)
{
	this->Epos = Epos;

	ePosList.push_front(Epos);
	//	敵のﾘｽﾄと数が合わない場合は後ろから消去する
	while (ePosList.size() > EListSize)
	{
		ePosList.pop_back();
	}
	int a = 9;
}

void CharHit::SetEListSize(int size)
{
	EListSize = size;
}

VECTOR2 CharHit::GetPpos()
{
	return Ppos;
}

bool CharHit::EnemyDeath()
{
	//	posxの距離
	int Xdistance = Epos.x - Ppos.x;
	//	絶対値にする
	if (Xdistance < 0)
	{
		Xdistance = -Xdistance;
	}
	//	posyの距離
	int Ydistance = Epos.y - (Ppos.y + CHIP_SIZE);
	//	絶対値にする
	if (Ydistance < 0)
	{
		Ydistance = -Ydistance;
	}

	if (Xdistance < 16)
	{
		if (Ydistance < 8)
		{
			return true;
		}
	}
	return false;
}

bool CharHit::PlayerDamage()
{
	for (auto itr = ePosList.begin(); itr != ePosList.end(); ++itr)
	{
		Epos = (*itr);
		//	posxの距離
		int Xdistance = Epos.x - Ppos.x;
		//	絶対値にする
		if (Xdistance < 0)
		{
			Xdistance = -Xdistance;
		}
		//	posyの距離
		int Ydistance = Epos.y - Ppos.y;
		//	絶対値にする
		if (Ydistance < 0)
		{
			Ydistance = -Ydistance;
		}

		if (Xdistance < 16)
		{
			if (Ydistance < 1)
			{
				return true;
			}
		}
	}
	return false;
}

