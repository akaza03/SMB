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
	void Gravity();						//	�d��
	bool CheckCorrect();				//	��Q���Əd�Ȃ��Ă��邩������
	bool Contact(DIR_LR dir);			//	�ǂɂԂ����Ă��邩������
	void SetMove();
	bool initAnim();
	bool skyflag;						//	�󒆂ɂ��邩�ǂ������׸�
	bool moveLR = true;					//	�ړ��ł��邩���׸�

	float Vy;
	int Cnt;
	int deathCnt;						//	���S���o�p
};

