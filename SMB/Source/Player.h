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
	void Gravity();						//	�d��
	bool skyContact();					//	�󒆗p����
	bool CheckCorrect();				//	��Q���Əd�Ȃ��Ă��邩������
	bool Contact(DIR_LR dir);			//	�ǂɂԂ����Ă��邩������
	void GoldContact();					//	�R�C���Ƃ̓����蔻��
	bool EnemyContact();
	void SetMove();
	bool initAnim();
	bool skyflag;						//	�󒆂ɂ��邩�ǂ������׸�
	bool jumpNow = false;				//	�ެ��ߒ������׸�
	bool deathFlag;
	bool EnemyDeathFlag;				//	��а���j���̼ެ����׸�

	float Vy;

	int GoldCntX;						//	�擾��ݐ�10�̈�
	int GoldCntO;						//	�擾��ݐ�1�̈�
	int deathCnt;						//	���S���o�p
};
