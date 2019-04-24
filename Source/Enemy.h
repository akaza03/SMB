#pragma once
#include "Obj.h"
#include "CharHit.h"

class Enemy :
	public Obj
{
public:
	Enemy(const char(&_keyData)[256], const char(&_keyDataOld)[256], VECTOR2(chipOffset));
	~Enemy();
	bool Update();
	void Draw();
private:
	void Gravity();						//	重力
	bool CheckCorrect();				//	障害物と重なっているかのﾁｪｯｸ
	bool Contact(DIR_LR dir);			//	壁にぶつかっているかのﾁｪｯｸ
	void SetMove();
	bool initAnim();
	bool skyflag;						//	空中にいるかどうかのﾌﾗｸﾞ
	bool moveLR = true;					//	移動できるかのﾌﾗｸﾞ

	float Vy;
	int Cnt;
	int deathCnt;						//	死亡演出用
};

