#pragma once
#include "Obj.h"
#include "CharHit.h"

class Player:
	public Obj
{
public:
	Player(const char(&_keyData)[256],const char(&_keyDataOld)[256],VECTOR2(chipOffset));
	~Player();
	void SetEDFlag();
	bool GetEDFlag();
	bool Update();
	int GetGoldX();
	int GetGoldO();
	virtual void GetKeyData();
	void Draw();
private:
	void Gravity();						//	重力
	bool skyContact();					//	空中用判定
	bool CheckCorrect();				//	障害物と重なっているかのﾁｪｯｸ
	bool Contact(DIR_LR dir);			//	壁にぶつかっているかのﾁｪｯｸ
	void GoldContact();					//	コインとの当たり判定
	bool EnemyContact();
	void SetMove();
	bool initAnim();
	bool skyflag;						//	空中にいるかどうかのﾌﾗｸﾞ
	bool jumpNow = false;				//	ｼﾞｬﾝﾌﾟ中かのﾌﾗｸﾞ
	bool deathFlag;
	bool EnemyDeathFlag;				//	ｴﾈﾐｰ撃破時のｼﾞｬﾝﾌﾟﾌﾗｸﾞ

	float Vy;

	int GoldCntX;						//	取得ｺｲﾝ数10の位
	int GoldCntO;						//	取得ｺｲﾝ数1の位
	int deathCnt;						//	死亡演出用
};
