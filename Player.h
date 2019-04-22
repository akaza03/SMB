#pragma once
#include "Obj.h"
#include "CharHit.h"

class Player:
	public Obj
{
public:
	Player(const char(&_keyData)[256],const char(&_keyDataOld)[256],VECTOR2(chipOffset));
	~Player();
	bool Update();
	virtual void GetKeyData();
	void Draw();
private:
	void Gravity();						//	�d��
	bool skyContact();					//	�󒆗p����
	bool CheckCorrect();				//	��Q���Əd�Ȃ��Ă��邩������
	bool Contact(DIR_LR dir);			//	�ǂɂԂ����Ă��邩������
	bool EnemyContact();
	void SetMove();
	bool initAnim();
	bool skyflag;						//	�󒆂ɂ��邩�ǂ������׸�
	bool jumpNow = false;				//	�ެ��ߒ������׸�
	bool deathFlag;

	float Vy;

	int deathCnt;						//	���S���o�p
};
