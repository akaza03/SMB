#pragma once
#include <list>
#include "VECTOR2.h"

#define lpCharHit CharHit::GetInstance()
typedef std::list<VECTOR2> EPos_List;

class CharHit
{
public:
	static CharHit &GetInstance()
	{
		return *s_Instance;
	}
	void SetPpos(const VECTOR2 & Ppos);
	void SetEpos(const VECTOR2 & Epos);
	void SetEListSize(int size);
	VECTOR2 GetPpos();

	bool EnemyDeath();						//	ｴﾈﾐｰのﾀﾞﾒｰｼﾞ用判定
	bool PlayerDamage();					//	ﾌﾟﾚｲﾔｰのﾀﾞﾒｰｼﾞ用判定
private:
	struct CharHitDeleter
	{
		void operator()(CharHit *charHit)const
		{
			delete charHit;
		}
	};

	static std::unique_ptr<CharHit, CharHitDeleter> s_Instance;
	CharHit();
	~CharHit();
	VECTOR2 Ppos = VECTOR2(0,0);
	VECTOR2 Epos = VECTOR2(0,0);

	EPos_List ePosList;					//	ｴﾈﾐｰの座標登録用
	int EListSize;
};

