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
	//	�G��ؽĂƐ�������Ȃ��ꍇ�͌�납���������
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
	//	posx�̋���
	int Xdistance = Epos.x - Ppos.x;
	//	��Βl�ɂ���
	if (Xdistance < 0)
	{
		Xdistance = -Xdistance;
	}
	//	posy�̋���
	int Ydistance = Epos.y - (Ppos.y + CHIP_SIZE);
	//	��Βl�ɂ���
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
		//	posx�̋���
		int Xdistance = Epos.x - Ppos.x;
		//	��Βl�ɂ���
		if (Xdistance < 0)
		{
			Xdistance = -Xdistance;
		}
		//	posy�̋���
		int Ydistance = Epos.y - Ppos.y;
		//	��Βl�ɂ���
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

